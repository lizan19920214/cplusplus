/**
 * c++11中using关键字的使用
*/

// 1、命名空间
// 这种用法估计使用最多的，为了防止定义变量名、函数名冲突，把它们定义在一个命名空间内，
//      使用的时候需要进行命名空间的申明：using namespace std；就不过多讲解。


#include <iostream>
#include <vector>
using namespace std;

// 2、指定别名
int mytest(int a, string str)
{
    cout << "a: " << a << " str: " << str << endl;
    return a;
}

//使用typedef定义函数指针和使用using定义函数指针
//可以看到，using的写法把别名的名字强制分离到了左边，而把别名指向的放在了右边，比较清晰

typedef int(*funcptr_d)(int, string);
using funcptr_u = int(*)(int, string);

void test1()
{
    funcptr_d func_d = mytest;
    funcptr_u func_u = mytest;

    func_d(111, "ddd");
    func_u(222, "uuu");
    (*func_d)(333, "ddd");
    (*func_u)(444, "uuu");
}

// typedef的限制无法定义模板别名，而using可以
template<typename T>
using vecT1 = std::vector<T>; //定义一个vector类型的模板传参
// typedef std::vector<T> vecT2; error

//模板别名
void test2()
{
    vecT1<int> v1; //使用int作为参数
    v1 = {1, 2, 3, 4, 5};
    for(auto i : v1)
        cout << i << " ";

    cout << endl;

}

// 3、子类引用基类成员
// 假如子类私有继承父类，子类无法使用父类的成员(变量，函数等)，但是使用using可以访问，code如下：
template<class _scale, int option>
class Person
{
public:
    _scale age;
    _scale height;
    _scale name[option];

	void myprint(void)
	{
		cout << "age" << age << endl;
	}
};


template<class _scale, int option>
class HeighPerson : private Person<_scale, option>
{
public:
    using Person<_scale, option>::age; // 使用using 之后变成public
    using Person<_scale, option>::myprint; // 使用using, ｍyprint之后变成public
    
protected:
	using Person<_scale, option>::height;  //在本来不可访问的，使用using 之后变成protected
    void test(void)
    {
	cout << "age" << age << endl;
    }
};


int main()
{
    test1();
    test2();
    return 0;
}