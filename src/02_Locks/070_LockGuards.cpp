#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;

// g++ 070_LockGuards.cpp -o 070_LockGuards.o -std=c++17 -Wall -lpthread

void work(int &count, mutex &mtx, const int &n) {
    for (int i = 0; i < n; ++i) {
        lock_guard<mutex> guard(mtx);
        ++count;
    }
}

int main() {

    int count = 0;
    mutex mtx;

    const int iterations = 1E6;

    thread t1(work, ref(count), ref(mtx), ref(iterations));
    thread t2(work, ref(count), ref(mtx), ref(iterations));

    t1.join();
    t2.join();

    cout << count << endl;

    return 0;
}