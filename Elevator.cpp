#include <iostream>
#include <thread>
#include <mutex>
#include <time.h>

using namespace std;

/************************************/
/*   DEFINES                        */
/************************************/
const int floor_count = 10;

/************************************/
/*   GLOBAL VARIABLES               */
/************************************/
// Mutex variables
mutex _mu_floor_cap;
mutex _mu_cout;

// Floor capacity array
int floor_cap[floor_count];


void ElevatorRun(int capacity) {
    int max_cap = capacity;
    int curr_cap = 0;

    unsigned int time_ui = static_cast<unsigned int>( (time(NULL) ) * max_cap);


    std::unique_lock <std::mutex> cout_lock (_mu_cout);
    cout << "[" << max_cap << "] Time_ui [" << time_ui << "]" << endl;
    cout_lock.unlock();

    srand(time_ui);
    int floor = rand() % 10;

    std::unique_lock <std::mutex> floor_cap_lock (_mu_floor_cap);
    curr_cap = (max_cap < floor_cap[floor]) ? max_cap : floor_cap[floor];
    floor_cap[floor] -= curr_cap;
    floor_cap_lock.unlock();

    cout_lock.lock();
    cout << "Elevator with capacity [" << max_cap << "] has [" << curr_cap << "] passengers from floor [" << floor <<"]." << endl;
    cout_lock.unlock();
}


void ResetFloorCap()
{
    std::unique_lock <std::mutex> floor_cap_lock (_mu_floor_cap);

    for (int i = 0; i < floor_count; i++)
    {
        if (i % 2 == 0)
            floor_cap[i] = 20;
        else
            floor_cap[i] = 10;
    }

    floor_cap_lock.unlock();
}


void PrintFloorCap()
{
    std::unique_lock <std::mutex> cout_lock (_mu_cout);
    cout << "Floor capacities are :" << endl;
    cout_lock.unlock();

    int cap;

    std::unique_lock <std::mutex> floor_cap_lock (_mu_floor_cap);
    floor_cap_lock.unlock();

    for (int i = 0; i < floor_count; i++)
    {
        floor_cap_lock.lock();
        cap = floor_cap[i];
        floor_cap_lock.unlock();

        cout_lock.lock();
        cout << "Floor [" << i << "] : [" << cap << "]" << endl;
        cout_lock.unlock();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}


int main() {

    ResetFloorCap();

    std::thread elevator1(ElevatorRun, 10);
    std::thread elevator2(ElevatorRun, 15);
    std::thread elevator3(ElevatorRun, 20);

    elevator1.join();
    elevator2.join();
    elevator3.join();

    PrintFloorCap();

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    return 0;
}