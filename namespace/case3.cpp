/**
 * 如何定义命名空间
*/
#include <iostream>

using namespace std;//展开std命名空间

namespace A1 {//定义一个名为A1的命名空间
	int a = 0;
	int b = 20;//变量

	void Add()//函数
	{
		cout << "IsAddFunc1" << endl;
	}

	struct TestNode//结构体
	{
		int test1;
		double test2;
	};
}

namespace A2 {//定义一个名为A2的命名空间
	int a = 10;
	int b = 21;

	void Add()
	{
		cout << "IsAddFunc2" << endl;
	}

	struct TestNode
	{
		int test3;
		double test4;
	};
}
int main()
{
	cout << "A1::b = " << A1::b << endl;//打印A1中的b
	cout << "A2::b = " << A2::b << endl;//打印A2中的b

	A1::Add();//调用A1中的Add函数
	A2::Add();//调用A2中的Add函数

	struct A1::TestNode AT1;//声明结构体变量
	struct A2::TestNode AT2;

	cout << &AT1 << endl;//打印结构体变量地址
	cout << &AT2 << endl;

	return 0;
}
