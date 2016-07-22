/******************************************************************************/
/*! File Name: StringParsing.cpp
 *  Description: This header file includes the declarations for function
 *               defined in Sender.h
 *
 *  Creation Date: 15-07-2016
 *  Author: Ashwin
 */
/******************************************************************************/

/******************************************************************************/
/*                   H.E.A.D.E.R  F.I.L.E.S                                   */
/******************************************************************************/

// Project header files
#include "StringParsing.h"

/******************************************************************************/
/*                              M.A.C.R.O.S                                   */
/******************************************************************************/


/******************************************************************************/
/*                C.L.A.S.S  D.E.F.I.N.I.T.I.O.N                              */
/******************************************************************************/

ThreadQueues::ThreadQueues()
{
    // Do something
}

std::string ThreadQueues::ReadFromQueue()
{
    std::string input_string;

    std::unique_lock<std::mutex> ip_q_lock (_mu_queue);

    if (!queue.empty())
    {
        input_string = queue.front();
        queue.pop();
    }

    ip_q_lock.unlock();

    return  input_string;
}

std::string ThreadQueues::GetInputData(ThreadQueues input_obj)
{
    std::string input_str;

    input_str = input_obj.ReadFromQueue();

//    if (input_str.length() == 0)
//    {
//
//    }

    return input_str;
}


int ThreadQueues::WriteToQueue(std::string input_str)
{
    int iRetVal = SUCCESS;

    std::unique_lock<std::mutex> out_q_lock (_mu_queue);
    queue.push(input_str);
    out_q_lock.unlock();

}

/******************************************************************************/
/*                F.U.N.C.T.I.O.N  D.E.C.L.A.R.A.T.I.O.N                      */
/******************************************************************************/

void StringParserThread(ThreadQueues obj, ThreadQueues input_obj)
{
    // Read data from queue
    std::string input_str = input_obj.ReadFromQueue();


}



void PrintWord(std::string word)
{
    std::unique_lock<std::mutex> cout_lock (_mu_cout);
    std::cout << word;
    cout_lock.unlock();
}





int main()
{
    int iRetVal = SUCCESS;
    int total_threads = 5;
    std::string input_string = "This is example string for this program.";

    if (total_threads < 2)
    {
        std::cout << "Please enter two or more threads." << std::endl;
        return INVALID_ARGS;
    }

//    for (int i =0; i < total_threads; i++)
//    {
//
//    }


    std::istringstream iss(input_string);
    std::string word;
    while(iss >> word) {
        std::cout << word << " <--- " << iss.rdbuf() << std::endl;
        std::string new_str = iss.rdbuf()->str();
        std::cout << new_str << std::endl;
    }

    return iRetVal;
}

