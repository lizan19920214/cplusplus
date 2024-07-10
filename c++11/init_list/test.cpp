/**
 * 初始化列表
*/

#include <iostream>

//传统初始化方式
// 普通数组
int i_arr[3] = { 1, 2, 3 };

// POD类型：结构体
struct A
{
    int x;
    struct B
    {
        int i;
        int j;
    } b;
} a = { 1, { 2, 3 } };

// 拷贝初始化（copy-initialization）
int i = 0;
class Foo1
{
    public:
    Foo1(int) {}
    Foo1(const Foo1 &);
} foo1 = 123;  // 需要拷贝构造函数

// 直接初始化：使用 () 进行
int j(0);
Foo1 bar(123);

/**
 * C++11 首先把初始化列表的概念绑定到了类型上，并将其称之为 initializer_list，
 *      允许构造函数或其他函数像参数一样使用初始化列表，这就为类对象的初始化与普通数组和 POD 的初始化方法提供了统一的桥梁。
 *      可以拿个类模板 initializer_list 作为构造函数的参数，则初始化列表就智能用于构造该函数。值得注意的是列表中的元素必须是同一种类型或者可以转化为同一种类型。
 * 
*/

class Foo
{
public:
    Foo(int) {}
private:
    Foo(const Foo &);
};

int main(void)
{
    // 调用Foo(int)构造函数初始化（c++98编译通过 c++11编译通过）
    Foo a1(123);
    // 报错：Foo的拷贝构造函数声明为私有的，该处的初始化方式是隐式调用Foo(int)构造函数生成一个临时的匿名对象，再调用拷贝构造函数完成初始化
    Foo a2 = 123;
    
    // 列表初始化（c++98编译失败 c++11编译通过）
    Foo a3 = { 123 };
    // 列表初始化（c++98编译通过 c++11编译通过）
    Foo a4 { 123 };
    
    // 列表初始化（++98编译通过 c++11编译通过）
    int a5 = { 3 };
    // 列表初始化（++98编译失败 c++11编译通过）
    int a6 { 3 };

    // 在C++11中可以使用列表初始化方法对堆中分配的内存的数组进行初始化，而在C++98/03中是不能这样做的
    int* a = new int { 3 };
    double b = double{ 12.12 };
    int* arr = new int[3] {1, 2, 3};

    
    return 0;
}
