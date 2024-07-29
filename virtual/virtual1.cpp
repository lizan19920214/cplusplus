/*
菱形继承的二义性问题
如下：
    B1和B2继承A，C继承 B1 B2
    这时C中包含了两个A中的a，我们在声明一个C的对象时，使用a时需要指明使用的是B1中的a还是B2中的a
    直接使用c.a会出现二义性问题，不知道使用的是B1的a还是B2的a
    当然如果我们在c中重载了对应的变量或者方法，就可以直接调用了c.a或者c.func()
*/
#include <iostream>
using namespace std;

class A
{
public:
    int a;
    void func()
    {
        cout << "A::func()" << endl;
    }
};

class B1 : public A
{
public:
    int b1;
    void func()
    {
        cout << "B1::func()" << endl;
    }
};

class B2 : public A
{
public:
    int b2;
    void func()
    {
        cout << "B2::func()" << endl;
    }
};

class C : public B1, public B2
{
public:
    int c;
    //如果重载了下面的变量或者方法，就可以直接调用c.a或者c.func()
    // int a;
    // void func(){};
};

int main()
{
    //需要注意成员函数不计算在类的大小内，所以下面类的大小不包含成员函数
    //因为成员函数在代码区，类的各个对象是共有的，但是成员变量是私有的，所以各个对象是独立的
    A a;
    cout << "a size = " << sizeof(a) << endl;  // 4  a
    B1 b1;
    cout << "b1 size = " << sizeof(b1) << endl; // 8 a + b1
    B2 b2;
    cout << "b2 size = " << sizeof(b2) << endl; // 8 a + b2
    C c1;
    cout << "c1 size = " << sizeof(c1) << endl; // 20 a + b1 + a + b2 + c 这里包含了两个a

    // c1.a = 100; //报错，意义不明，无法判断是哪个基类的a
    c1.B1::a = 100;
    cout << "c1.B1::a = " << c1.B1::a << endl;

    // c1.func(); 二义性
    c1.B1::func();
    c1.B2::func();
    return 0;
}