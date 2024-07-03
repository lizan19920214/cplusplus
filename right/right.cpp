#include <iostream>


void desc1()
{
    int i = 0;
    int &j = i;    // 左值引用
    int &&k = 11;  // 右值引用
}

// 对于字面量使用右值引用并没有什么具体的意义，我们看一个比较有意义的代码
// g++ -o right right.cpp -fno-elide-constructors
//编译加上-fno-elide-constructors，防止编译器直接给我们优化了
class X {
public:
    X() { std::cout << "X ctor" << std::endl; }
    X(const X&x) { std::cout << "X copy ctor" << std::endl; }
    ~X() { std::cout << "X dtor" << std::endl; }
    void show() { std::cout << "show X" << std::endl; }
};

X make_x() 
{
    X x1;
    return x1;
}

/**
 * 输出：
 * 
 * X ctor
 * X copy ctor
 * X dtor
 * show X
 * X dtor
 * 
 * 首先是在make_x()栈中生成了一个x对象，调用了一次构造函数，为了返回这个对象的临时副本使用了拷贝构造函数，
 * 销毁在make_x()栈中的对象使用析构函数，返回的右值(临时副本)给了右值引用，延长了这个右值的生命周期，最后销毁这个临时副本。
 * 如果不使用右值引用，使用 X x2 = make_x() 则是几次构造？应该是三次，x1会默认构造一次，然后return x1会使用复制构造产生临时对象，
 * 接着X x2 = make_x()会使用复制构造将临时对象复制到x2，最后临时对象被销毁。
 * main() 函数中并不需要手动释放 x2 或 make_x() 返回的临时对象，因为它们的生命周期由 C++ 的对象生命周期管理机制来管理。
 * 
 * ！！！！！！！！！延长临时对象生命周期并不是这里右值引用的最终目标，其真实目标应该是减少对象复制，提升程序性能。
 * 
 * 
*/

int main()
{
    X &&x2 = make_x();
    x2.show();
    return 0;
}