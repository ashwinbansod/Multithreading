/******************************************************************************/
/*! File Name: Odd_Even.cpp
 *  Description: This file defined two threads, out of which one thread prints
 *               only even numbers and other prints odd numbers
 *
 *  Creation Date: 17-07-2016
 *  Author: Ashwin
 */
/******************************************************************************/

/******************************************************************************/
/*                   H.E.A.D.E.R  F.I.L.E.S                                   */
/******************************************************************************/
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

/******************************************************************************/
/*                              M.A.C.R.O.S                                   */
/******************************************************************************/
#define SUCCESS           0
#define FAILURE           1

#define THREAD_1          1
#define THREAD_2          2


#define MAX_VALUE         100

/******************************************************************************/
/*                G.L.O.B.A.L V.A.R.I.A.B.L.E.S                               */
/******************************************************************************/
// Mutex variables
std::mutex _mu_cout;
std::mutex _mu_th;
std::condition_variable _cv_th;

bool thread_1 = false;
bool thread_2 = false;

/******************************************************************************/
/*                F.U.N.C.T.I.O.N  D.E.C.L.A.R.A.T.I.O.N                      */
/******************************************************************************/

void PrintNumber(int num)
{
    std::unique_lock<std::mutex> cout_lock (_mu_cout);
    std:: cout << num << " ";
    cout_lock.unlock();
}

void PrintNumber(int num, int thread_no)
{
    std::unique_lock<std::mutex> cout_lock (_mu_cout);
    std:: cout << "Thread " << thread_no << ": " << num << std::endl;
    cout_lock.unlock();
}

void PrintEvenSequence(int start)
{
    int num = start;

    while (num <= MAX_VALUE)
    {
        std::unique_lock<std::mutex> thred_1_lock (_mu_th);
        _cv_th.wait(thred_1_lock,[]{ return thread_1; });

//        PrintNumber( num) ;
        PrintNumber( num, start) ;

        num += 2;

        thread_2 = true;
        thread_1 = false;

        thred_1_lock.unlock();
        _cv_th.notify_one();

        std::this_thread::sleep_for(std:: chrono::milliseconds(10));
    }
}


void PrintOddSequence(int start)
{
    int num = start;

    while (num <= MAX_VALUE)
    {
        std::unique_lock<std::mutex> thred_2_lock (_mu_th);
        _cv_th.wait(thred_2_lock,[]{ return thread_2; });

//        PrintNumber( num) ;
        PrintNumber( num, start) ;

        num += 2;

        thread_1 = true;
        thread_2 = false;

        thred_2_lock.unlock();
        _cv_th.notify_one();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}


/******************************************************************************/
/*                M.A.I.N  F.U.N.C.T.I.O.N                                    */
/******************************************************************************/

int main(void)
{
    int iRetVal = SUCCESS;

    std::thread EvenSeq (PrintEvenSequence, 0);
    std::thread OddSeq (PrintOddSequence, 1);

    EvenSeq.detach();
    OddSeq.detach();

    thread_1 = true;

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    return iRetVal;
}
