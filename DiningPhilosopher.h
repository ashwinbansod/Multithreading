/******************************************************************************/
/*! File Name: DiningPhilosopher.cpp
 *  Description: This file implements the common muti-threading problem of
 *               Dining Philosophers.
 *
 *  Creation Date: 29-09-2016
 *  Author: Ashwin
 */
/******************************************************************************/
#ifndef MULTITHREADING_DININGPHILOSOPHER_H
#define MULTITHREADING_DININGPHILOSOPHER_H

/******************************************************************************/
/*                   H.E.A.D.E.R  F.I.L.E.S                                   */
/******************************************************************************/
#include <iostream>
#include <mutex>
#include <vector>
#include <thread>

/************************************/
/*   DEFINES                        */
/************************************/
const int philosopher_count = 5;

/************************************/
/*   GLOBAL VARIABLES               */
/************************************/
std::vector<std::mutex> forks(philosopher_count);
//std::vector<std::unique_lock<std::mutex>> forks;
std::mutex cout_mu;


/************************************/
/*   CLASS DEFINITION               */
/************************************/
class Philosopher {
private:
    int ph_no;
    int leftfork;
    int rightfork;

public:
    Philosopher(int n): ph_no(n),leftfork((n)% (forks.size()-1)), rightfork(n-1){}

    void printThinking()
    {
        std::unique_lock<std::mutex> io_lock (cout_mu);
        io_lock.lock();
        std::cout << "Philosopher [" << ph_no << "] is thinking.\n";
        io_lock.unlock();
    }

    void printEating()
    {
        std::unique_lock<std::mutex> io_lock (cout_mu);
        io_lock.lock();
        std::cout << "Philosopher [" << ph_no << "] is eating.\n";
        io_lock.unlock();
    }

    void sleepThread(long sleeptime)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(sleeptime));
    }

    long getRandomSleepTime()
    {
        return rand()%500;
    }

    bool checkForksandEat()
    {
        bool retval = false;
        if (forks[leftfork].try_lock())
        {
            if (forks[rightfork].try_lock())
            {
                // Both forks available. Eating now.
                printEating();
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                forks[rightfork].unlock();
                retval = true;
            }
            forks[leftfork].unlock();
        }
        return retval;
    }

    void operator() ()
    {
        long i = 0;
        while (i < 1000)
        {
            sleepThread(getRandomSleepTime());

            //Check if Forks are available.
            if (checkForksandEat())
            {
                // Philosopher ate something
                // Now think for sometime then again try eating
                printThinking();
                sleepThread(500);
            }

            i++;
        }
    }
};




#endif //MULTITHREADING_DININGPHILOSOPHER_H
