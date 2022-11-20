# Learn Multithreading in C++ - John Purcell



## Course and source code

https://www.udemy.com/course/cplusplus-multithreading/

https://github.com/caveofprogramming/Cpp-Multithreading



## Section 02 - Locks

### lock_guard vs lock/unlock

The lock_guard uses RAII, in case of an exception or return it calls unlock automatically.

## Section 03 - Returning Values from Threads

Promises and future


## Section 04 - Signalling


https://en.cppreference.com/w/cpp/thread/condition_variable


### Warning about interger type on Produce Consumer Section 4 item 21


While compiling src/04_Signalling/190_Producer_Consumer.cpp I got this warning:

```
$ g++ 190_Producer_Consumer.cpp -o 190_Producer_Consumer.o -Wall -std=c++17 -lpthread

190_Producer_Consumer.cpp: In instantiation of ‘void blocking_queue<E>::push(E) [with E = int]’:
190_Producer_Consumer.cpp:69:22:   required from here
190_Producer_Consumer.cpp:32:58: warning: comparison of integer expressions of different signedness: ‘std::queue<int, std::deque<int, std::allocator<int> > >::size_type’ {aka ‘long unsigned int’} and ‘int’ [-Wsign-compare]
   32 |         _cond.wait(lock, [this]() { return _queue.size() < _max_size; }); // waits until queue has some space

$ uname -a
Linux TherOverman2 5.15.0-53-generic #59~20.04.1-Ubuntu SMP Thu Oct 20 15:10:22 UTC 2022 x86_64 x86_64 x86_64 GNU/Linux
```

I've solved it changing *int _max_size;* for *size_t _max_size;*

```
private:
    mutex _mtx;
    condition_variable _cond;
    // int _max_size;
    size_t _max_size;
    queue<E> _queue;
```


## Section 05 - Processing Work Efficiently

https://en.cppreference.com/w/cpp/thread/async


https://en.cppreference.com/w/cpp/thread/future


https://en.cppreference.com/w/cpp/thread/shared_future


Use shared_future for asynchronous operations
