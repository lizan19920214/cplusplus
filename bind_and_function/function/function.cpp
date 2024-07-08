/**
 * #include <functional>
 * 
 * function保存函数的三个方式：保存普通函数、保存lambda表达式、保存成员函数；但是重载的成员函数需要配合bind才可以。
*/

#include <functional>
#include <iostream>
using namespace std;

void test1(int a)
{
    cout << "test1: " << a << endl;
}

class Foo
{
public:
    Foo(int _num) : num(_num) {};

    void print_add (int a) const
    {
        cout << "foo:" << num + a << endl;
    }

    //有函数重载则不能使用function来调用
    // void print_add (std::string str) const
    // {
    //     cout << "foo:" << str << endl;
    // }

    int num;
};

class CAdd
{
public:
    CAdd():m_nSum(0) { NULL; }
    
    int operator()(int i)
    {
        m_nSum += i;
        return m_nSum;
    }
    
    int Sum() const 
    {
        return m_nSum;
    }
 
private:
    int m_nSum;
};
 

int main()
{
    //普通函数
    std::function<void(int)> f1 = test1;
    f1(10);
    f1(20);

    //lambda表达式
    std::function<void(int)> f2 = [](int a) {cout << "lambda:" << a << endl;};
    f2(30);

    //成员函数
    std::function<void(const Foo&, int)> f3 = &Foo::print_add;
    Foo foo(10);
    f3(foo, 20);

    CAdd add;
    function<int (int)> f4 = add;
    function<int (int)> f5 = add;
    // 输出是：10,10,0。我们将同一个函数对象赋值给了两个function，然后分别调用了这两个function，
    // 但函数对象中m_nSum的状态并没有被保持，问题出在哪儿呢？
    // 这是因为function的缺省行为是拷贝一份传递给它的函数对象，
    // 于是f1和f2中保存的都是add对象的拷贝，调用f1和f2后，add对象中的值并没有被修改
    cout << f4(10) << "," << f5(10) << "," << add.Sum() << endl;

    // C++ 11中提供了ref和cref函数，来提供对象的引用和常引用的包装
    // 修改为引用，可以修改到add对象的值
    function<int(int)> f6 = ref(add);
    function<int(int)> f7 = ref(add);
    cout << f6(10) << "," << f7(10) << "," << add.Sum() << endl;


    return 0;
}