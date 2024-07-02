/**
 * 
 * 多个指针指向同一个对象，当最后一个share_ptr离开作用域的时候，内存才会自动释放
 *      与vector等类似，智能指针也是模板，当我们创建一个智能指针时，必须提供指针可以指向的类型，
 *      在<>中给出类型
 * 
 * 默认初始化的智能指针中保存着一个空指针
 *      调用make_share库函数在动态内存中分配一个对象初始化智能指针
 * 
 * 当进行拷贝或者赋值操作时，每个shared_ptr都会记录有多少个其他shared_ptr指向相同的对象。每个shared_ptr都有一个关联的计数器，称为引用计数。
 * 无论何时拷贝一个shared_ptr，计数器都会递增
 * 给shared_ptr赋予一个新值或者shared_ptr被销毁，计数器就会递减
 * 一旦一个shared_ptr的计数器变为0，它就会自动释放自己所管理的对象
 * 
 * 
*/

#include <iostream>
#include <memory>
#include <list>

using namespace std;

void desc1()
{
    // 保存着一个空指针，可以指向string
    shared_ptr<string>  p1;
    // 保存着一个控指针，可以指向int的list
    shared_ptr<list<int>> p2;
    //使用make_shared在动态内存中分配一个对象并初始化它
    shared_ptr<int> p3 = make_shared<int>(100);
    //初始化一个默认值为0的int智能指针
    shared_ptr<int> p4 = make_shared<int>();
    //使用auto保存智能指针结果
    auto p5 = make_shared<int>(100);
}

//shared_ptr与new结合
//使用new返回的指针来初始化智能指针
//接收指针参数的智能指针构造函数是explicit(抑制隐式转换),因此不能将一个内置指针隐式转换为一个智能指针
//必须使用直接初始化的形式来初始化一个智能指针
void desc2()
{
    //error 必须使用直接初始化形式
    // shared_ptr<int> p1 = new int(1024);
    //正确，使用了直接初始化形式，p指向一个值为1024的int
    shared_ptr<int> p2(new int(1024));
}

//使用reset来将一个新的指针赋予一个shared_ptr
void desc3()
{
    shared_ptr<int> p1;
    //error 不能将一个指针直接赋予shared_ptr
    // p1 = new int(1024);
    p1.reset(new int(1024));

    int* p = new int (10);
    std::shared_ptr<int> a (p);
    if (a.get()==p)
    {
        cout << "a and p point to the same location" << endl;
    }
    //以下三种形式访问同一块地址
    std::cout << *a.get() << "\n";//输出10
    std::cout << *a << "\n";//输出10
    std::cout << *p << "\n";//输出10

}

//循环引用的问题
class B;
class A
{
public:
    A() : m_sptrB(nullptr) {};

    ~A()
    {
        cout << " A is destory" << endl;
    }

    shared_ptr<B> m_sptrB;
};

class B
{
public:
    B() : m_sptrA(nullptr) {};
    ~B()
    {
        cout << " B is destory" << endl;
    }

    shared_ptr<A> m_sptrA;
};

int main()
{
    shared_ptr<B> sptrB(new B());
    shared_ptr<A> sptrA(new A());

    //下述代码产生了一个循环引用A对B有一个shared_ptr，B对A也有一个shared_ptr，与sptrA和sptrB关联的资源都没有被释放
    //当sptrA和sptrB离开作用域时，它们的引用计数都只减少到1，所以它们指向的资源并没有释放
    sptrB->m_sptrA = sptrA;
    sptrA->m_sptrB = sptrB;


    return 0;
}
