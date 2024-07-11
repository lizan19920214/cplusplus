/**
 * 继承构造
 * 
*/

#include <iostream>
using namespace std;

//在c++11之前，如果派生类要使用使用基类的构造函数，通常需要在构造函数中显式声明：
// B派生自A，B又在构造函数中调用A的构造函数，从而完成构造函数的传递。但是如果基类中有大量的构造函数时，可能需要这样写：
// 如果我们想要在构造B时拥有A这样多的构造方法的时候，就必须意义“透传”各个接口，这时候就很不方便了。
struct A{
 	A(int i){};
 	A(double d, int i){}
 	A(float f, int i, const char*c){}
};

struct B: A{
	B(int i): A(i) {}
	B(double d, int i) : A(d, i) {};
	B(float f, int i, const char*c) : A(f, i, c){}
	
	virtual void ExtraInterface(){};
};


// 此C++11利用关键字using引入了继承构造函数的概念
class Base
{
public:
    Base() { cout << "Base()" << endl; }
    Base(const Base& other) { cout << "Base(Base&)" << endl; }
    explicit Base(int i) : num(i) { cout << "Base(int)" << endl; }
    explicit Base(char c) : letter(c) { cout << "Base(char)" << endl; }

private:
    int num;
    char letter;
};

class Derived : Base
{
public:
    // Inherit all constructors from Base
    using Base::Base;

private:
    // Can't initialize newMember from Base constructors.
    int newMember{ 0 };
};

int main()
{
    cout << "Derived d1(5) calls: ";
    Derived d1(5);
    cout << "Derived d1('c') calls: ";
    Derived d2('c');
    cout << "Derived d3 = d2 calls: " ;
    Derived d3 = d2;
    cout << "Derived d4 calls: ";
    Derived d4;
}

/* Output:
Derived d1(5) calls: Base(int)
Derived d1('c') calls: Base(char)
Derived d3 = d2 calls: Base(Base&)
Derived d4 calls: Base()*/
