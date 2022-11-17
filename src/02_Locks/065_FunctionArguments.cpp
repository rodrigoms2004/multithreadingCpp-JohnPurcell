#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;

// g++ 065_FunctionArguments.cpp -o 065_FunctionArguments.o -std=c++17 -Wall -lpthread

void work(int &count, mutex &mtx, const int &n) {
    for (int i = 0; i < n; ++i) {
        mtx.lock();
        ++count;
        mtx.unlock();
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