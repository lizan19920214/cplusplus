/**
 * 
 * 语法：
 * [ captures ] ( params ) specifiers exception -> ret { body }
*/

#include <iostream>

void test1()
{
/**
 * captures 捕获列表，下例中捕获了变量 x
 * params 可选参数列表，下例中添加了参数 y
 * specifiers 可选限定符，C++11中可以用mutable，它允许我们在lambda表达式函数体内改变按值捕获的变量，或者调用非const的成员函数
 * exception 可选异常说明符，可以使用noexcept来指明lambda是否会抛出异常
 * ret 可选返回值类型
 * body lambda表达式的函数体
 * 
 * 最简单的lambda
 * [](){}
*/
    int x = 5;
    auto foo = [x](int y)->int {return x* y ;};
    std::cout << foo(2) << std::endl;

    auto func = [](){std::cout << "Hello World" << std::endl;};
    func();
}

/**
 * 作用域
 * 捕获列表中的变量存在于两个作用域——lambda表达式定义的函数作用域以及lambda表达式函数体的作用域。前者为了捕获变量，后者为了使用变量
 * 捕获的变量必须是一个自动存储类型（非静态局部变量）
 * 如果我们想要使用静态变量或者全局变量，直接使用就行，lambda本身就在这些变量的作用域内
*/
int value1 = 1;
void test2()
{
    int y = 2;
    static int z = 3;
    auto foo = [y] {return value1 + y + z;};
    std::cout << foo() << std::endl;
}

/**
 * 捕获引用
 * 如下:
 * 为什么foo1会出错,是因为lambda表达式捕获的是x的副本，而不是x本身，因此无法改变x的值
 * 为什么foo2可以改变x的值，是因为lambda表达式捕获的是x的引用，因此可以改变x的值
 * lambda表达式有个特性,捕获的变量默认是常量.
 * 
 * 
 * mutable说明符可以移除lambda表达式的常量性：
 * 
*/

void test3()
{
    int x = 5, y = 8;
    auto foo1 = [x, y]
    {
        // error 无法改变捕获变量的值
        // x += 10;
        // y += 20;
        std::cout << x << " " << y << std::endl;
    };
    // std::cout << foo1() << std::endl;

    auto foo2 = [&x, &y]{
        x += 1;
        y += 2;
        return x * y;
    };
    std::cout << foo2() << std::endl;

    //mutable说明符可以移除lambda表达式的常量性
    // 增加说明符mutable，还多了一对()，这是因为语法规定lambda表达式如果存在说明符，那么形参列表不能省略
    auto foo3 = [x, y]() mutable {
        x += 1;
        y += 2;
        return x * y;
    };

    std::cout << foo3() << std::endl;
}

/**
 * 
 * 捕获值和捕获引用还是存在着本质区别。当lambda表达式捕获值时，表达式内实际获得的是捕获变量的复制，
 *      我们可以任意地修改内部捕获变量，但不会影响外部变量。对于捕获值的lambda表达式还有一点需要注意，
 *      捕获值的变量在lambda表达式定义的时候已经固定下来了，无论函数在lambda表达式定义后如何修改外部变量的值，
 *      lambda表达式捕获的值都不会变化
*/
void test4()
{
    int x = 5, y = 8;
    auto foo = [x, &y]() mutable {
        x += 1;
        y += 2;
        std::cout << "lambda x = " << x << ", y = " << y << std::endl;
        return x * y;
    };
    x = 9;
    y = 20;
    foo();
}

// this 捕获当前对象
class Func{
    public:
        int x;
         Func(int val) : x(val) {}
 
    void doSomething()
    {
        auto lambda = [this]{ // 捕获this指针以访问成员变量x
            ++x;
            std::cout << "Inside lambda: x=" << x << std::endl;
        };
        lambda(); 
    }
         
};

void test5()
{
    Func func(10);
    func.doSomething();
}

// = 表示捕获外部变量的值,在lambda表示内只会改变其副本的值,不会影响到原始的外部变量
void test6()
{
    int a = 10;
    int b = 20;
    auto func =[=]{
        std::cout << "a = "<< a <<",b ="<< b << std::endl;
    };
    
    func();

}

// 捕获外部变量的引用,,在lambda内部对变量进行修改时,会影响到原始的外部变量
void test7()
{
    int a = 10;
    int b = 20;
    auto func =[&]{
        a ++;
        std::cout << "a = "<< a <<",b ="<< b << std::endl;
    };
    
    func();

}

int main()
{
    test1();
    std::cout << std::endl;
    test3();
    std::cout << std::endl;
    test4();
    std::cout << std::endl;
    test5();
    std::cout << std::endl;
    test6();
    std::cout << std::endl;
    test7();

    return 0;
}