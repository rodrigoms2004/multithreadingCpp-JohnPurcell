#include <iostream>
#include <thread>

using namespace std;

// g++ 220_Hardware_Concurrency.cpp -o 220_Hardware_Concurrency.o -Wall -std=c++17 -lpthread


int main()
{
    cout << thread::hardware_concurrency() << endl;
    return 0;
}