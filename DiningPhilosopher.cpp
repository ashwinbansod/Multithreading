/******************************************************************************/
/*! File Name: DiningPhilosopher.cpp
 *  Description: This file implements the common muti-threading problem of
 *               Dining Philosophers.
 *
 *  Creation Date: 29-09-2016
 *  Author: Ashwin
 */
/******************************************************************************/

/******************************************************************************/
/*                   H.E.A.D.E.R  F.I.L.E.S                                   */
/******************************************************************************/
#include "DiningPhilosopher.h"


int main()
{
    std::thread *tt = new std::thread[philosopher_count];

    for (int i = 0; i < philosopher_count; ++i)
    {
        tt[i] = std::thread((Philosopher(i+1)));
    }

    for (int i = 0; i < philosopher_count; ++i)
    {
        tt[i].join();
    }

    std::this_thread::sleep_for(std::chrono::seconds(10));


    return 0;
}