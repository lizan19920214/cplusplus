/*
std::promise 构造函数
promise();
template <class Alloc> promise (allocator_arg_t aa, const Alloc& alloc);
promise (const promise&) = delete;
promise (promise&& x) noexcept;

    1、默认构造函数，初始化一个空的共享状态。
    2、带自定义内存分配器的构造函数，与默认构造函数类似，但是使用自定义分配器来分配共享状态。
    3、拷贝构造函数，被禁用。
    4、移动构造函数。

    另外，std::promise 的 operator= 没有拷贝语义，即 std::promise 普通的赋值操作被禁用，operator= 只有 move 语义，所以 std::promise 对象是禁止拷贝的。
*/

#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <future>         // std::promise, std::future

std::promise<int> prom;

void print_global_promise () 
{
    std::future<int> fut = prom.get_future();
    int x = fut.get();
    std::cout << "value: " << x << '\n';
}

int main ()
{
    std::thread th1(print_global_promise);
    prom.set_value(10);
    th1.join();

    prom = std::promise<int>();    // prom 被move赋值为一个新的 promise 对象.

    std::thread th2 (print_global_promise);
    prom.set_value (20);
    th2.join();

  return 0;
}

// value: 10
// value: 20