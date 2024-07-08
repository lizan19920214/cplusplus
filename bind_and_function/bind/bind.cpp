/**
 * std::bind可以看作是一个通用的函数适配器，它可以接收一个可调用对象，生成一个新的可调用对象来适应原对象的参数列表
 * std::bind将可调用对象与其参数一起进行绑定，绑定后的结果可以使用std::function保存。std::bind主要有以下两个作用：
 *      1、将可调用对象和其参数绑定成一个仿函数；
 *      2、只绑定部分参数，减少可调用对象传入的参数。
 * 
 * 如果预绑定的参数是以值传递的形式，不预绑定的参数要用std::placeholders(占位符)的形式占位，从_1开始，依次递增，
 *      是以引用传递的形式；并且std::placeholders表示新的可调用对象的第几个参数，而且与原函数的该占位符所在位置的进行匹配，例如：
 *      
 *      auto f3 = std::bind(fun_1, std::placeholders::_2, std::placeholders::_1, 3); 
 *      f2(1, 2);
 * 
 * 这里调用fun_1时，传入的第一个参数是f2(1, 2)里面的2，第二个参数是f2(1, 2)里面的1，
 *      第三个是3，即和参数占位符中的_n是一一对应的。
 * 
 * bind绑定类成员函数时，第一个参数表示对象的成员函数的指针，第二个参数表示对象的地址，
 *      这是因为对象的成员函数需要有this指针。并且编译器不会将对象的成员函数隐式转换成函数指针，需要通过&手动转换；
 * 
 * std::bind的返回值是可调用实体，可以直接赋给std::function。
*/

#include <iostream>
#include <functional>

class A {
public:
    A()
    {
        //绑定本身的成员函数，需要传入this指针
        test = std::bind(&A::func_4, this);
    }

    void fun_3(int k,int m) 
    {
        std::cout << "print: k = "<< k << ", m = " << m << std::endl;
    }

    std::function<void()> test;

private:
    void func_4()
    {
        std::cout << "func_4" << std::endl;
    }
};

void fun_1(int x,int y,int z) 
{
    std::cout << "print: x = " << x << ", y = " << y << ", z = " << z << std::endl;
}

void fun_2(int &a,int &b) 
{
    ++a;
    ++b;
    std::cout << "print: a = " << a << ", b = " << b << std::endl;
}

int main(int argc, char * argv[]) 
{
    //f1的类型为 function<void(int, int, int)>
    auto f1 = std::bind(fun_1, 1, 2, 3); 					//表示绑定函数 fun 的第一，二，三个参数值为： 1 2 3
    f1(); 													//print: x=1,y=2,z=3

    auto f2 = std::bind(fun_1, std::placeholders::_1, std::placeholders::_2, 3);
    //表示绑定函数 fun 的第三个参数为 3，而fun 的第一，二个参数分别由调用 f2 的第一，二个参数指定
    f2(1, 2);												//print: x=1,y=2,z=3
 
    auto f3 = std::bind(fun_1, std::placeholders::_2, std::placeholders::_1, 3);
    //表示绑定函数 fun 的第三个参数为 3，而fun 的第一，二个参数分别由调用 f3 的第二，一个参数指定
    //注意： f2  和  f3 的区别。
    f3(1, 2);												//print: x=2,y=1,z=3

    int m = 2;
    int n = 3;
    auto f4 = std::bind(fun_2, std::placeholders::_1, n); //表示绑定fun_2的第一个参数为n, fun_2的第二个参数由调用f4的第一个参数（_1）指定。
    f4(m); 													//print: a=3,b=4
    std::cout << "m = " << m << std::endl;					//m=3  说明：bind对于不事先绑定的参数，通过std::placeholders传递的参数是通过引用传递的,如m
    std::cout << "n = " << n << std::endl;					//n=3  说明：bind对于预先绑定的函数参数是通过值传递的，如n
    
    A a;
    //f5的类型为 function<void(int, int)>
    auto f5 = std::bind(&A::fun_3, &a, std::placeholders::_1, std::placeholders::_2); //使用auto关键字
    f5(10, 20);												//调用a.fun_3(10,20),print: k=10,m=20

    std::function<void(int,int)> fc = std::bind(&A::fun_3, a,std::placeholders::_1,std::placeholders::_2);
    fc(10, 20);   											//调用a.fun_3(10,20) print: k=10,m=20 

    auto f6 = std::bind(&A::test, a);
    f6()();

    return 0; 
}
