/*
std::future::wait()
    等待与当前std::future 对象相关联的共享状态的标志变为 ready.
    如果共享状态的标志不是 ready（此时 Provider 没有在共享状态上设置值（或者异常）），调用该函数会被阻塞当前线程，直到共享状态的标志变为 ready。
    一旦共享状态的标志变为 ready，wait() 函数返回，当前线程被解除阻塞，但是 wait() 并不读取共享状态的值或者异常。

std::future::wait_for()
    与 std::future::wait() 的功能类似，即等待与该 std::future 对象相关联的共享状态的标志变为 ready，
    该函数原型如下：
        template <class Rep, class Period>
            future_status wait_for (const chrono::duration<Rep,Period>& rel_time) const;

    而与 std::future::wait() 不同的是，wait_for() 可以设置一个时间段 rel_time，如果共享状态的标志在该时间段结束之前没有被 Provider 设置为 ready，
        则调用 wait_for 的线程被阻塞，在等待了 rel_time 的时间长度后 wait_until() 返回，返回值如下：

    返回值	描述
    future_status::ready	共享状态的标志已经变为 ready，即 Provider 在共享状态上设置了值或者异常。
    future_status::timeout	超时，即在规定的时间内共享状态的标志没有变为 ready。
    future_status::deferred	共享状态包含一个 deferred 函数。

*/
#include <iostream>
#include <future>
#include <chrono>
#include <thread>

bool do_check_prime(int x)
{
    std::cout << "enter wait prime...\n";
    std::this_thread::sleep_for(std::chrono::seconds(x));
    return true;
}

bool do_check_prime_time_out(int x)
{
    std::cout << "enter wait_for prime...\n";
    std::this_thread::sleep_for(std::chrono::seconds(x));
    return true;
}


int main()
{
    std::future <bool> fut = std::async(do_check_prime, 3);

    std::cout << "wait...\n";
    //阻塞等待
    fut.wait();

    if (fut.get()) // guaranteed to be ready (and not block) after wait returns
        std::cout << "is prime.\n";
    else
        std::cout << "is not prime.\n";


    std::future < bool > fut2 = std::async(do_check_prime_time_out, 5);
    std::cout << "wait_for...\n";
    std::chrono::seconds span(2); // 设置超时间隔.

    // 如果超时，则输出"."，继续等待
    while (fut2.wait_for(span) == std::future_status::timeout)
        std::cout << "wait_for is timeout.\n";

    if (fut2.get())
        std::cout << "wait_for is prime.\n";
    else
        std::cout << "wait_for is not prime.\n";



    return 0;
}