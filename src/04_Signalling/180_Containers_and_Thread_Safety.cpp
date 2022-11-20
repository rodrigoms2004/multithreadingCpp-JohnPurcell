#include <iostream>
#include <thread>
#include <queue>



using namespace std;

// g++ 180_Containers_and_Thread_Safety.cpp -o 180_Containers_and_Thread_Safety.o -Wall -std=c++17 -lpthread


template<typename E>
class blocking_queue 
{
private:
    int _max_size;
    queue<E> _queue;

public:
    blocking_queue(int max_size): _max_size(max_size) 
    { 

    }

    void push(E e) 
    {
        _queue.push(e);
    }

    E pop() 
    {
        E item = _queue.front();
        _queue.pop();
        return item;
    }

    int size() 
    {
        return _queue.size();
    }
};

int main() 
{
    blocking_queue<int> qu(5);

    thread t1([&]() {
        for (int i = 0; i < 10; ++i) {
            qu.push(i);
            cout << "produced " << i << " queue size " << qu.size() << endl; 
        }
    });

    thread t2([&]() {
        for (int i = 0; i < 10; ++i) {
            auto item = qu.pop();
            cout << "consumed " << item << endl;
        }
    });

    t1.join();
    t2.join();

    return 0;
}