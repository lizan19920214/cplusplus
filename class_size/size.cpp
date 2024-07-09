#include<iostream>

/*  虚继承与继承的区别：
	1.多了一个虚基指针
	2.虚基类位于派生类存储空间的最末尾
	3.不会共用虚函数指针
*/

class A
{
	char a[3];
public:
	virtual void fun1() {};
};

// 测试一：单个虚继承，不带虚函数
class B : public virtual A
{
	char b[3];
};

// 测试二：单个虚继承，带自己的虚函数
class C : public virtual A
{
	char c[3];
public:
	virtual void fun2() {};
};

// 测试三：双重继承
class D : public virtual C
{
	char d[3];
public:
	virtual void fun3() {};
};

int main()
{
	std::cout << sizeof(A) << std::endl; // 8
	std::cout << sizeof(B) << std::endl; // 8(A) + 8(B)【8 == (3+1)+虚基指针】
	std::cout << sizeof(C) << std::endl; // 8(A) + 12(C)【12 == (3+1)+自己的虚函数指针+虚基指针】
    //char a[3];
    // A vptr
    // char c[3];
    // C vptr
    // char d[3];
    // D vptr
    // 字节对齐 6 * 8 = 48
	std::cout << sizeof(D) << std::endl; // 8(A) + 12(C) + 12(D)
	return 0;
}

/*
32位输出：
8
16
20
32

64位输出：
16
32
32
48
*/
