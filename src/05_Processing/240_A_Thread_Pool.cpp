#include <iostream>
#include <future>
#include <chrono>
#include <thread>
#include <vector>
#include <mutex>
#include <cmath>
#include <queue>


using namespace std;

// g++ 240_A_Thread_Pool.cpp -o 240_A_Thread_Pool.o -Wall -std=c++17 -lpthread

mutex g_mtx;


template<typename E>
class blocking_queue 
{
private:
    mutex _mtx;
    condition_variable _cond;
    // int _max_size;
    size_t _max_size;
    queue<E> _queue;

public:
    blocking_queue(int max_size): _max_size(max_size) 
    { 

    }

    void push(E e) 
    {
        unique_lock<mutex> lock(_mtx);

        _cond.wait(lock, [this]() { return _queue.size() < _max_size; }); // waits until queue has some space
        
        _queue.push(e);

        lock.unlock();
        _cond.notify_one();
    }

    E front() 
    {
        unique_lock<mutex> lock(_mtx);
        _cond.wait(lock, [this]() { return !_queue.empty(); }); // waits until queue is not empty 

        return _queue.front();
    }

    void pop() 
    {
        unique_lock<mutex> lock(_mtx);
        _cond.wait(lock, [this]() { return !_queue.empty(); }); // waits until queue is not empty 

        _queue.pop();

        lock.unlock();
        _cond.notify_one();
    }

    int size() 
    {
        lock_guard<mutex> lock(_mtx);
        return _queue.size();
    }
};

int work(int id) 
{
    unique_lock<mutex> lock(g_mtx);
    cout << "Starting " << id << endl;
    lock.unlock();

    int seconds = int((5.0 * rand()) / RAND_MAX + 3); // gest a number from 3 to 8
    this_thread::sleep_for(chrono::seconds(seconds));

    return id;
}


int main() 
{
    blocking_queue<shared_future<int>> futures(2); // run 3 threads simultaneously 0, 1, 2
    thread t([&](){
        for (unsigned int i = 0; i < 20; ++i) 
        {
            shared_future<int> f = async(launch::async, work, i);
            futures.push(f);
        }
    });

    for (unsigned int i = 0; i < 20; ++i)
    {
        shared_future<int> f = futures.front();
        int value = f.get();
        futures.pop();
        cout << "Returned " << value << endl;
    }

    t.join();

    return 0;
}