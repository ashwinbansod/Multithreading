/******************************************************************************/
/*! File Name: StringParsing.h
 *  Description: This header file contains the
 *
 *  Creation Date: 15-07-2016
 *  Author: Ashwin
 */
/******************************************************************************/

#ifndef MULTITHREADING_STRINGPARSING_H
#define MULTITHREADING_STRINGPARSING_H

/******************************************************************************/
/*                   H.E.A.D.E.R  F.I.L.E.S                                   */
/******************************************************************************/
/* Standard C++ includes */
#include <iostream>
#include <mutex>
#include <thread>
#include <queue>
#include <sstream>

// Project header files


/******************************************************************************/
/*                              M.A.C.R.O.S                                   */
/******************************************************************************/
#define SUCCESS           0
#define FAILURE           1
#define INVALID_ARGS      2


/******************************************************************************/
/*                G.L.O.B.A.L V.A.R.I.A.B.L.E.S                               */
/******************************************************************************/
// Mutex variables
std::mutex _mu_cout;


/******************************************************************************/
/*                C.L.A.S.S  D.E.F.I.N.I.T.I.O.N                              */
/******************************************************************************/

class ThreadQueues
{
private:
    std::queue<std::string> queue;
//    std::queue<std::string> output_queue;

    std::mutex _mu_queue;
//    std::mutex _mu_out_queue;

public:
    ThreadQueues();

    std::string ReadFromQueue();

    std::string GetInputData(ThreadQueues input_obj);

    int WriteToQueue(std::string);

};
/******************************************************************************/
/*                F.U.N.C.T.I.O.N  D.E.F.I.N.I.T.I.O.N                        */
/******************************************************************************/

void PrintWord(std::string word);

#endif //MULTITHREADING_STRINGPARSING_H
