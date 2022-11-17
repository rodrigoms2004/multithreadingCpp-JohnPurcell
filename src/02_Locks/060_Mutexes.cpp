#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;


// g++ 060_Mutexes.cpp -o 060_Mutexes.o -std=c++17 -lpthread -Wall

int main () {

    int count = 0;
    const int ITERATIONS = 1E6; // 1.000.000 
    mutex mtx;

    auto func = [&]() {         // or auto func = [&count](), count is captured by lambda function
        for (int i = 0; i < ITERATIONS; ++i) {
            mtx.lock();
            ++count;
            mtx.unlock();
        }
    };

    thread t1(func);
    thread t2(func);
    
    t1.join();
    t2.join();

    cout << count << endl;

    return 0;
}