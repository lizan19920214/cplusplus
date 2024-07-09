/**
 * 类所占内存大小是由成员变量(静态变量除外)决定的，成员函数不计算在内
*/
#include <iostream>

class CBase1
{
};

class CBase2
{
    int i;
    char p;
};

class CBase3
{ 
public: 
	CBase3(void); 
	virtual ~CBase3(void); 
    
private: 
	int  a; 
	char *p; 
}; 

class CChild : public CBase3 
{ 
public: 
	CChild(void); 
	~CChild(void); 

virtual void test();
	private: 
	int b; 
}; 


class A {};

class B : public A
{
	virtual void fun() = 0;
};

// 共有继承，共用虚函数指针，没有虚基指针
class C : public B
{
};

class D : public A, public B
{
};

int main()
{
    //c++要求每一个实例在内存中都有一个独一无二的地址。空类也会被实例化，因此编译器会给空类隐含的添加一个字节
    std::cout << "CBase1 size:" <<  sizeof(CBase1) << std::endl;  // 1


    //成员变量的内存和，但要接的字节对齐的问题，和struct的字节对齐原则一致，int占4字节，char占1字节，因此4字节对齐，
    //char p会填充3个字节，因此CBase2的大小为8
    std::cout << "CBase2 size:" <<  sizeof(CBase2) << std::endl;  //  8

    //c++类中有虚函数的时候，有一个指向虚函数表的指针，在32位系统占4字节，64位系统占8字节，根据字节对齐，因此CBase3的大小为24
    //注意！！！！无论多少个虚函数，就只有一个虚函数表指针
    std::cout << "CBase3 size:" <<  sizeof(CBase3) << std::endl;  //  32位12  64位24


    //子类的大小是本身成员变量的大小加上父类的大小
    // 派生类的大小是基类和派生类的非静态数据成员的大小+一个vptr指针的大小
    // int  a; 
	// char *p; 
	// int b; 
    // vptr
    //字节对齐为 4*8
    std::cout << "CChild size:" <<  sizeof(CChild) << std::endl;  //  32位16  64位32


	std::cout << "sizeof(A)" << sizeof(A) << std::endl; //空类1
	std::cout << "sizeof(B)" << sizeof(B) << std::endl; // 虚函数指针 32位4  64位8
	std::cout << "sizeof(C)" << sizeof(C) << std::endl; // 与B共用虚函数指针 32位4  64位8
	std::cout << "sizeof(D)" << sizeof(D) << std::endl; // A(1) + 与B共用虚函数指针(4) 32位8  64位16



    return 0;
}