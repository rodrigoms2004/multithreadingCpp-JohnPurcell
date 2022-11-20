#include <iostream>
#include <thread>
#include <chrono>
#include <condition_variable>



// g++ 140_Condition_Variables.cpp -o 140_Condition_Variables.o -Wall -std=c++17 -lpthread 

using namespace std;

int main() {

    condition_variable condition;
    mutex mtx;
    bool ready = false;

    thread t1([&]() {
        this_thread::sleep_for(chrono::milliseconds(2000));
        unique_lock<mutex> lock(mtx);
        ready = true;
        lock.unlock();
        condition.notify_one();
    });

    unique_lock<mutex> lock(mtx);

    // ready = false, !ready = true, keep the loop
    // ready = true,  !ready = false, exist the loop
    while(!ready) {     
        cout << "Wating for ready... " << ready << endl;
        condition.wait(lock);
    }

    cout << "ready " << ready << endl;

    t1.join();

    return 0;
}