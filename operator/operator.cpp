/**
 * 在c++中可以重定义或者重载大部分的内置运算符
 * 重载的运算符是带有特殊名称的函数，函数名是由关键字operator和其后要重载的运算符符号构成的
 * 与其他函数一样，重载运算符同样有一个返回类型和参数列表
 * 
 * 如下：重载加法运算符，用于把两个Box对象相加，最终返回Box对象。
 * Box operator+(const Box&);
 * 大多数的重载运算符都可以被定义为普通的非成员函数或者被定义为类成员函数。
 * 如果我们定义上面的函数为类的非成员函数，那么我们需要为每次的操作传递两个参数，如下：
 * Box operator+(const Box&, const Box&);
 * 
*/

#include <iostream>
#include <string>

class Box
{
private:
    int length;
public:
    Box();
    Box(int lenght_);
    Box operator+(const Box& b);
    int getLength() { return length; }
};

Box::Box()
{
    length = 1;
}

Box::Box(int lenght_)
{
    length = lenght_;
}

Box Box::operator+(const Box& b)
{
    Box c;
    c.length = this->length + b.length;
    return c;
}

int main()
{
    Box b1 = {1};
    Box b2 = {2};
    Box b3 = b1 + b2;
    std::cout << "b3.length = " << b3.getLength() << std::endl;
    return 0;
}