/*
 虚继承
 注意：C++编译系统在实例化C类时，只会将虚基类A的构造函数调用一次，忽略虚基类的其他派生类（class B1，class B2）对虚继承的构造函数的调用，
 从而保证了虚基类的数据成员不会被多次初始化。

在虚基类A中有一个虚指针指向一个虚表，虚表中记录了虚基类与本类的地址偏移，通过这个地址偏移可以找到虚基类的成员变量a的地址
*/

#include <iostream>
using namespace std;
 
class A{
public:
    int a;
};
 
class B1 : virtual public A{
public:
    int b1;
};
 
class B2 : virtual public A{
public:
    int b2;
};
 
class C : public B1, public B2{
public:
    int c1;
};
 
int main(){
    C  c1;
    c1.b1 = 100;
    c1.b2 = 200;
    c1.c1 = 300;

    c1.a = 500; //虚继承使得成员变量a只有一份拷贝，通过虚指针可以确定地址

    cout << "end..." << endl;
    return 0;
}