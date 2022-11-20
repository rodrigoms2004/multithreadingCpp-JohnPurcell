#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>


// g++ 130_Waiting_for_Threads.cpp -o 130_Waiting_for_Threads.o -Wall -std=c++17 -lpthread 

using namespace std;

int main() {

    atomic<bool> ready = false;
    // bool ready = false;

    thread t1([&]() {
        this_thread::sleep_for(chrono::milliseconds(2000));
        ready = true;
    });

    t1.join();

    while(!ready) {
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    cout << "ready " << ready << endl;


    return 0;
}