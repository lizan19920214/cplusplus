/*
头文件
#include <future>               // std::async, std::future

介绍：
    std::future 可以用来获取异步任务的结果，因此可以把它当成一种简单的线程间同步的手段。
    std::future 通常由某个 Provider 创建，你可以把 Provider 想象成一个异步任务的提供者，
    Provider 在某个线程中设置共享状态的值，与该共享状态相关联的 std::future 对象调用 get（通常在另外一个线程中） 获取该值，
    如果共享状态的标志不为 ready，则调用 std::future::get 会阻塞当前的调用者，
    直到 Provider 设置了共享状态的值（此时共享状态的标志变为 ready），std::future::get 返回异步任务的值或异常（如果发生了异常）。

    一个有效(valid)的 std::future 对象通常由以下三种 Provider 创建，并和某个共享状态相关联。Provider 可以是函数或者类，其实我们前面都已经提到了，他们分别是：
        std::async 函数
        std::promise::get_future，get_future 为 promise 类的成员函数
        std::packaged_task::get_future，此时 get_future为 packaged_task 的成员函数
    
    一个 std::future 对象只有在有效(valid)的情况下才有用(useful)，由 std::future 默认构造函数创建的 future 
    对象不是有效的（除非当前非有效的 future 对象被 move 赋值另一个有效的 future 对象）。

    在一个有效的 future 对象上调用 get 会阻塞当前的调用者，直到 Provider 设置了共享状态的值或异常（此时共享状态的标志变为 ready），
    std::future::get 将返回异步任务的值或异常（如果发生了异常）。

*/
// future example
#include <iostream>             // std::cout
#include <future>               // std::async, std::future
#include <chrono>               // std::chrono::milliseconds

void get_int(std::promise<int>& prom)
{
    int x;
    std::cout << "Please, enter an integer value: " <<std::endl;

    std::cin >> x; // read from cin
    prom.set_value(x);
}

void print_int(std::future<int>& fut)
{
    int x = fut.get(); // read from fut 阻塞
    std::cout << "Value: " << x << std::endl;
}


int main()
{
    std::promise<int> prom;
    //通过promise获得future
    std::future<int> fut = prom.get_future();

    //使用std::ref，可以修改传入引用的值
    std::thread th1(get_int, std::ref(prom));
    std::thread th2(print_int, std::ref(fut));

    th1.join();
    th2.join();

    std::cout << "Done" << std::endl;

    return 0;
}