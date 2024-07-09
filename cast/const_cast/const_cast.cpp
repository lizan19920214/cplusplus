/**
 * 使用场景：
 *      常量指针(引用)与非常量指针(引用)之间的转换
 * 使用特点：
 *      const_cast是四种类型转换中唯一可以对常量进行操作的转换符
 *      去常量性是一个危险的操作，尽量避免使用
*/

#include <iostream>

using namespace std;

int main()
{
	int value = 100;
	const int *cpi = &value; // 定义一个常量指针
	//*cpi = 200;   // 不能通过常量指针修改值

	// 1. 将常量指针转换为非常量指针,然后可以修改常量指针指向变量的值
	int *pi = const_cast<int *>(cpi);
	*pi = 200;

	// 2. 将非常量指针转换为常量指针
	const int *cpi2 = const_cast<const int *>(pi); // *cpi2 = 300;  //已经是常量指针

	const int value1 = 500;
	const int &c_value1 = value1; // 定义一个常量引用

	// 3. 将常量引用转换为非常量引用
	int &r_value1 = const_cast<int &>(c_value1);

	// 4. 将非常量引用转换为常量引用
	const int &c_value2 = const_cast<const int &>(r_value1);
}
