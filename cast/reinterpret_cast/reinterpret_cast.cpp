/**
 * 
 * 使用场景：
 *      1、用在任意指针（或引用）类型之间的转换。
 *      2、能够将整型转换为指针，也可以把指针转换为整型或数组。
 * 
 * 使用特点：
 *      1、reinterpret_cast 是从底层对数据进行重新解释，依赖具体的平台，可移植性差。
 *      2、不到万不得已，不用使用这个转换符，高危操作。
 * 
*/

#include <iostream>

using namespace std;

int main()
{
	int value = 100;
	// 1. 用在任意指针（或引用）类型之间的转换
	double *pd = reinterpret_cast<double *>(&value);
	cout << "*pd = " << *pd << endl;

	// 2. reinterpret_cast能够将指针值转化为整形值
	int *pv = &value;
	int pvaddr = reinterpret_cast<int>(pv);
	cout << "pvaddr = " << hex << pvaddr << endl;
	cout << "pv = " << pv << endl;
}
