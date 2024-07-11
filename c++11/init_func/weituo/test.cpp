/**
 * 委托构造函数在其成员初始化列表调用了本类其他构造函数来完成其部分或全部初始化工作。
 * 使用 委托构造函数 的目的是：避免写重复的代码。
 * 委托构造函数的特点：
 *      1、没有返回值，函数名为类名；
 *      2、成员初始化列表只允许调用一个本类的其他构造函数(可以是委托构造函数)，不允许初始化其他成员；
 *      3、函数体可能没有任何实现，只有一个{}，也可以实现一部分初始化工作。
 * 如果定义了委托构造函数，则gcc编译时必须指定-std=c++11以支持C++11标准
 * 
*/
#include <iostream>
using namespace std;

class CDate
{
public:
	CDate(int year, int mon, int day);	// 构造函数声明
	CDate(int year, int mon):CDate(year,mon,1)// 委托构造函数	
	{
		cout << "Calling Delegating Constructor(int, int)" << endl;
	}
	CDate(int year):CDate(year,1,1)		// 委托构造函数
	{
		cout << "Calling Delegating Constructor(int)" << endl;
	}
	CDate():CDate(2000,1,1)				// 委托构造函数
	{
		cout << "Calling Delegating Constructor()" << endl;
	}
	//CDate(){CDate(2000,1,1);}			// 报错，没初始化Max_Year
	
	void show()
	{
		cout << "Date: " << m_year << "." << m_mon << "." << m_day << ", this=" << this << endl;
	}
private:
	int m_year;
	int m_mon;
	int m_day;
	const int Max_Year;
};

// 构造函数定义
CDate::CDate(int year, int mon, int day):Max_Year(2039)
{
	m_year = year>Max_Year ? Max_Year : year;
	m_mon = mon;
	m_day = day;
	cout << "Calling Constructor(int,int,int)" << ", this=" << this <<endl;
}

int main()
{
	CDate date(2024,06,27);
	date.show();
	cout << endl;
	
	CDate date1(2024,06);
	date1.show();
	cout << endl;
	
	CDate date2(2024);
	date2.show();
	cout << endl;
	
	CDate date3;
	date3.show();
	cout << endl;
	
	return 0;
}
