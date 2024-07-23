/*
头文件
    #include <future>         // std::promise, std::future
    
介绍：
    promise对象可以保存某一类型T的值，该值可以被future对象读取(可能在另一个线程中)，因此promise也提供了一种线程同步的手段。
    在promise对象构造时，可以和一个共享状态(通常为std::future)相关联，并可以在相关联的共享状态(std::future)上保存一个类型为T的值。
    可以通过 get_future 来获取与该 promise 对象相关联的 future 对象，调用该函数之后，两个对象共享相同的共享状态(shared state)
        1、promise 对象是异步 Provider，它可以在某一时刻设置共享状态的值。
        2、future 对象可以异步返回共享状态的值，或者在必要的情况下阻塞调用者并等待共享状态标志变为 ready，然后才能获取共享状态的值。

std::promise::get_future 介绍
    该函数返回一个与 promise 共享状态相关联的 future 。返回的 future 对象可以访问由 promise 对象设置在共享状态上的值或者某个异常对象。
    只能从 promise 共享状态获取一个 future 对象。在调用该函数之后，promise 对象通常会在某个时间点准备好(设置一个值或者一个异常对象)，
    如果不设置值或者异常，promise 对象在析构时会自动地设置一个 future_error 异常(broken_promise)来设置其自身的准备状态。
    下面的例子中已经提到了 get_future，此处不再重复。

编译：
g++ -o promise promise.cpp -lpthread
*/

#include <iostream>       // std::cout
#include <functional>     // std::ref
#include <thread>         // std::thread
#include <future>         // std::promise, std::future
#include <chrono>

void print_int(std::future<int>& fut) 
{
    std::cout << "enter thread" << std::endl;
    int x = fut.get(); // 获取共享状态的值. 这里会阻塞等待设置共享状态的值
    std::cout << "value: " << x << '\n'; // 打印 value: 10.
}

int main ()
{
    std::promise<int> prom; // 生成一个 std::promise<int> 对象.
    std::future<int> fut = prom.get_future(); // 和 future 关联.
    std::thread t(print_int, std::ref(fut)); // 将 future 交给另外一个线程t.
    std::cout << "waiting....." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    prom.set_value(10); // 设置共享状态的值, 此处和线程t保持同步.
    t.join();
    return 0;
}

// waiting.....
// enter thread
// 这里等待了3秒，promise对象设置共享状态的值为10，线程t获取共享状态的值并打印。
// value: 10