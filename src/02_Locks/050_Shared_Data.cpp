#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

using namespace std;


// g++ 050_Shared_Data.cpp -o 050_Shared_Data.o -std=c++17 -lpthread -Wall

int main () {

    atomic<int> count = 0;
    // int count = 0;
    const int ITERATIONS = 1E6; // 1.000.000 

    // thread t1([]() { } ); // anonymous function, lambda expression

    
    thread t1([&count]() {
        for (int i = 0; i < ITERATIONS; i++) {
            ++count;
        }
    });

    thread t2([&count]() {
        for (int i = 0; i < ITERATIONS; i++) {
            ++count;
        }
    });

    t1.join();
    t2.join();

    cout << count << endl;

    return 0;
}