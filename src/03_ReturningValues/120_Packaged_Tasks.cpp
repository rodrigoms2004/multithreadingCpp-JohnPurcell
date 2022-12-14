#include <iostream>
#include <cmath>
#include <iomanip>
#include <thread>
#include <future>
#include <exception>

using namespace std;

// g++ 120_Packaged_Tasks.cpp -o 120_Packaged_Tasks.o -Wall -std=c++17 -lpthread


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

    // <double(int)> returns double and receives an int as parameter
    packaged_task<double(int)> task1(calculate_pi);

    // thread t1(ref(task1), 1E8);

    future<double> future1 = task1.get_future();

    thread t1(move(task1), 1E8);

    try {
        double result = future1.get();
        cout << setprecision(15) << result << endl;
    } catch (exception &e) {
        cout << "ERROR! " << e.what() << endl;
    }

    t1.join();

    return 0;
}