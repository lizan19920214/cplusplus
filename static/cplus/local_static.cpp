/**
 * g++ -o local_static local_static.cpp
 * 1️⃣：静态成员为所有类对象所共享，不属于某个具体的实例
 * 2️⃣：静态成员变量必须在类外定义，定义时不添加static关键字
 * 3️⃣：静态成员函数没有隐藏的this指针，不能访问任何非静态成员
 * 4️⃣：访问静态成员变量的特殊方式
 * 5️⃣：静态成员和类的普通成员一样，也有public、protected、private3种访问级别，也可以具有返回值
 * 
 * 
 * 1、静态成员函数可以调用非静态成员函数吗？
 * 答案：不可以，因为静态成员函数是没有this指针的，无法调用非静态成员函数。
 * 2、非静态成员函数可以调用类的静态成员函数吗？
 * 答案：可以，因为静态成员为所有类对象所共享，不受访问限制
 * 
 * 
*/
#include <iostream>

class A
{
public:
    void setN(int a) { n = a; }
    void setK(int b) { k = b; }
    void setM(int c) { m = c; }
    int getN() { return n; }
    int getK() { return k; }
    int getM() { return m; }

    static void func()
    {
        std::cout << n << std::endl;
        // std::cout << k << std::endl; //error 静态成员函数没有隐藏的this指针，不能访问任何非静态成员
    }

    static int getStaticM()
    {
        return m;
    }

    //类内定义
    static int m;

private:
    static int n;
    int k;
};

//类外初始化
int A::n = 0;
int A::m = 0;

int main()
{
    A a1;
    a1.setN(100);
    a1.setK(200);
    a1.setM(300);
    std::cout << a1.getN() << std::endl; //100
    std::cout << a1.getK() << std::endl;
    std::cout << std::endl;

    A a2;
    std::cout << a2.getN() << std::endl; //静态成员n为所有类对象共享，因此上面设置了N为100，这里获取直接就是100
    std::cout << a2.getK() << std::endl;
    std::cout << std::endl;

    //三种访问public类型的static成员函数的方式
    std::cout << a2.m << std::endl;
    std::cout << A::m << std::endl;
    std::cout << A().m << std::endl;
    std::cout << std::endl;
    //三种访问private类型的static成员函数的方式
    std::cout << a2.getM() << std::endl;
    std::cout << A::getStaticM() << std::endl;
    std::cout << A().getM() << std::endl; //通过匿名对象调用成员函数进行访问

    
    
    return 0;
}