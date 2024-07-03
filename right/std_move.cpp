/**
 * 
 * 左值与右值
 *      左值可以被取地址，具有名称的，持久性的
 *      右值是临时性的、瞬时的
 * 
 * 1、左值是可以放在赋值号左边可以被赋值的值；左值必须要在内存中有实体。
 * 2、右值是在赋值号右边取出值赋给其他变量的值；右值可以在内存也可以在CPU寄存器。
 * 3、一个对象被用作右值时，使用的是它的内容(值)，被当作左值时，使用的是它的地址。
 * 4、左值：指表达式结束后依然存在的持久对象，可以取地址，具名变量或对象 。
 * 5、右值：表达式结束后就不再存在的临时对象，不可以取地址，没有名字。
 * 
 * 
 * std::move是c++的一个函数模板，用于将一个左值(左值引用)转化为右值引用，从而实现移动语义。
 *      移动语义是一种可以将资源从一个对象转移到另一个对象的方式，而不是进行资源的复制。移动操作
 *      通常比复制操作更高效，对于大型的对象(结构体，类等)可以带来很大的性能提升。
 *      使用std::move是告诉编译器将对象视为一个右值，从而触发移动语义的操作。
 * 
 * 移动语义的优点：
 *      将对象从左值变为右值，避免拷贝构造，只是将对象状态或者所有权从一个对象转移到另一个对象
 *      没有涉及内存的搬迁或者内存拷贝，从而极大提高代码效率。
 *      ！！！！！需要注意的是，std::move后的原对象(下例中的obj6)的状态是未知的，因此不应该再对其
 *      进行操作，否则程序运行可能报错
*/

#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <vector>

using namespace std;

class MyClass
{
public:
    //构造函数
    MyClass(int value) : ptr(new int(value))
    {
        cout << "Default constructor called: MyClass(int value)" << endl;
    }

    //拷贝构造
    MyClass(const MyClass& other) : ptr(new int(*other.ptr))
    {
        cout << "Copy constructor called: MyClass(const MyClass& other)" << endl;
    }

    //移动构造函数，只是地址的复制，没有开辟内存、资源复制
    MyClass(MyClass&& other) : ptr(other.ptr)
    {
        other.ptr = nullptr;
        cout << "Move constructor called: MyClass(MyClass&& other)" << endl;
    }

    //复制构造函数，也存在开辟内存、复制资源
    MyClass& operator=(const MyClass& other)
    {
        //自我赋值
        if (&other == this)
        {
            return *this;
        }

        //释放原内存
        if (ptr)
        {
            delete ptr;
        }
        
        //赋值
        ptr = new int(*other.ptr);

        return *this;
    }

    ~MyClass()
    {
        if (ptr)
        {
            delete ptr;
        }
    }

    int GetValue(void) {return *ptr;}

    void PrintData() const 
    {
        cout << "Data:" << *ptr << endl;
    }

private:
    int* ptr;

};
int main()
{
    //默认构造
    MyClass obj1(10);
    //移动构造
    MyClass obj2 = std::move(obj1);

    // 调用默认构造函数
    MyClass obj3(30);                     
    // 调用移动构造函数
    MyClass obj4(std::move(obj3));   

    cout << endl;

    std::vector<MyClass> vec;
    //不适用移动语义，默认构造函数
    MyClass obj5(10);
    //复制构造函数
    vec.push_back(obj5);
    
    cout << endl;

    MyClass obj6(20);
    //拷贝构造+移动构造函数
    vec.push_back(std::move(obj6));

    cout << endl;

    for(auto& it: vec)
    {
        it.PrintData();
    }

    return 0;
}
