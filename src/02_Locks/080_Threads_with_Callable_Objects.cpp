#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;

// g++ 080_Threads_with_Callable_Objects.cpp -o 080_Threads_with_Callable_Objects.o -std=c++17 -Wall -lpthread

class App {

private:
    int count = 0;
    mutex mtx;

public:
    void operator()(const int &n) {        // You can overload the () operator to call your object as if it was a function
        for (int i = 0; i < n; ++i) {
            const lock_guard<mutex> guard(mtx);
            ++count;
        }
    }

    int getCount() {
        return count;
    }
};

int main() {

    App app;
    const int iterations = 1E6;

    thread t1(ref(app), ref(iterations));
    thread t2(ref(app), ref(iterations));

    t1.join();
    t2.join();

    cout << app.getCount() << endl;

    return 0;
}
