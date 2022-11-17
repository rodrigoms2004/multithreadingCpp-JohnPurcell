#include <iostream>
#include <cmath>
#include <iomanip>
#include <thread>
#include <future>
#include <exception>

using namespace std;

// g++ 110_Promises_and_Exceptions.cpp -o 110_Promises_and_Exceptions.o -Wall -std=c++17 -lpthread


double calculate_pi(int terms) {

    double sum = 0.0;

    if (terms < 1) {
        throw runtime_error("Terms cannot be less than 1");
    }

    for (int i = 0; i < terms; ++i) {
        int sign = pow(-1, i);
        double term = 1.0/(i * 2 + 1);
        sum += sign * term;
    }

    return sum * 4;
}

int main() {

    promise<double> promise;
    
    auto do_calculation = [&](int terms) {   // or [&promise](int terms) , captures promise
        try {
            auto result = calculate_pi(terms);
            promise.set_value(result);
        } catch (...) {
            promise.set_exception(current_exception()); // get exception pointer
        }
    };

    thread t1(do_calculation, 1E8);
    // thread t1(do_calculation, 0); // test exception

    future<double> future = promise.get_future();

    try {
        cout << setprecision(15) << future.get() << endl;
    } catch (const exception &e) {
        cout << e.what() << endl;
    }
    
    t1.join();

    return 0;
}