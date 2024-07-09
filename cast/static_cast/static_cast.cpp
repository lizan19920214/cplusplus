/**
 * static_cast 静态转换
 * 1. 基本数据类型转换 ：如int转char这种，安全性由使用者自行保证
 * 2. 基类和派生类之间的转换
 *      上行转换(派生类——>基类)安全
 *      下行转换(基类——>派生类)没有动态类型检查，不安全，需要dynamic_cast
 * 3. void* 和 指针类型之间的转换
 * 
 * 特点：
 * 1、主要执行非多态的转换操作，用于替代C中通常的转换操作
 * 2、隐式转换都建议使用 static_cast 进行标明和替换。
 * 3、不能使用 static_cast 在有类型指针内转换。
*/

#include <iostream>

using namespace std;

class CBase // 基类(父类)
{
    
};

class CDerived : public CBase  // 派生类(子类)
{

};

int main()
{
	// 1. 使用static_cast在基本数据类型之间转换
	float fval = 10.12;
	int ival = static_cast<int>(fval);  // float --> int
	cout << ival << endl;  // out: 10

	// 2. 使用static_cast在有类型指针与void *之间转换
	int *intp = &ival;
	void *voidp = static_cast<void *>(intp); // int* --> void*
	// cout << *voidp << endl; // error,voidp的大小未知
	long *longp = static_cast<long *>(voidp);
	cout << *longp << endl; // out: 10

	// 3. 用于类层次结构中基类和派生类之间指针或引用的转换
	// 上行转换（派生类---->基类）是安全的
	CDerived *tCDerived1 = nullptr;
	CBase *tCBase1 = static_cast<CBase*>(tCDerived1);
	// 下行转换（基类---- > 派生类）由于没有动态类型检查，所以是不安全的
	CBase *tCBase2 = nullptr;
	CDerived *tCDerived2 = static_cast<CDerived*>(tCBase2); //不会报错，但是不安全

	// 不能使用static_cast在有类型指针内转换
	float *floatp = &fval;  //10.12的addr
	//int *intp1 = static_cast<int *>(floatp); // error,不能使用static_cast在有类型指针内转换
	cout << *floatp << endl;    // out: 10.12
}
