#include <iostream>
#include <thread>
#include <chrono>
#include <condition_variable>



// g++ 150_Checking_Condition_Shared_Resources.cpp -o 150_Checking_Condition_Shared_Resources.o -Wall -std=c++17 -lpthread 

using namespace std;

int main() {

    condition_variable condition;
    mutex mtx;
    bool ready = false;
    int value = 10;

    thread t1([&]() {
        this_thread::sleep_for(chrono::milliseconds(2000));
        cout << "t1 acquiring lock" << endl;
        unique_lock<mutex> lock(mtx);
        cout << "t1 acquired lock" << endl;
        ready = true;
        value += 10;
        cout << "value = " << value << endl;
        lock.unlock();
        cout << "t1 released lock; notifying" << endl;
        condition.notify_one();
    });

    cout << "main thread acquiring lock" << endl;
    unique_lock<mutex> lock(mtx);

    cout << "main thread acquired lock; waiting" << endl;
    condition.wait(lock, [&](){ return ready; });

    cout << "main thread finished waiting" << endl;
    cout << "ready " << ready << " value " << value << endl;
    
    cout << "main thread unlock" << endl;

    t1.join();
    

    return 0;
}

/*
    main thread acquiring lock
    main thread acquired lock; waiting
    t1 acquiring lock
    t1 acquired lock
    t1 released lock; notifying
    main thread finished wating
    ready 1
*/