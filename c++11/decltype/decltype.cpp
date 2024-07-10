/**
 * decltype关键字是为了解决auto关键字只能对变量进行类型推导的缺陷而出现的
 *      它可以是编译器自动分析表达式的类型并得到它的类型，最关键是它不会取计算表达式的值，
 *      它的用法和sizeof很相似：
 * 原型：
 *      decltype（表达式）
 * 
 * decltype推导四规则
 *      1、如果e是一个没有带括号的标记符表达式或者类成员访问表达式，那么的decltype（e）就是e所命名的实体的类型。此外，如果e是一个被重载的函数，则会导致编译错误。
 *      2、否则 ，假设e的类型是T，如果e是一个将亡值，那么decltype（e）为T&&
 *      3、否则，假设e的类型是T，如果e是一个左值，那么decltype（e）为T&。
 *      4、否则，假设e的类型是T，则decltype（e）为T。
*/

#include <iostream>

int main()
{
    int i = 4;
    int arr[5] = { 0 };
    int *ptr = arr;
    struct S{ double d; }s ;
    void Overloaded(int);
    void Overloaded(char);//重载的函数
    int && RvalRef();
    const bool Func(int);
 
    //规则一：推导为其类型
    decltype (arr) var1; //int 标记符表达式
 
    decltype (ptr) var2;//int *  标记符表达式
 
    decltype(s.d) var3;//double 成员访问表达式
 
    //decltype(Overloaded) var4;//重载函数。编译错误。
 
    //规则二：将亡值。推导为类型的右值引用。
 
    decltype (RvalRef()) var5 = 1;
 
    //规则三：左值，推导为类型的引用。
 
    decltype ((i))var6 = i;     //int&
 
    decltype (true ? i : i) var7 = i; //int&  条件表达式返回左值。
 
    decltype (++i) var8 = i; //int&  ++i返回i的左值。
 
    decltype(arr[5]) var9 = i;//int&. []操作返回左值
 
    decltype(*ptr)var10 = i;//int& *操作返回左值
 
    decltype("hello")var11 = "hello"; //const char(&)[9]  字符串字面常量为左值，且为const左值。

 
    //规则四：以上都不是，则推导为本类型
 
    decltype(1) var12;//const int
 
    decltype(Func(1)) var13=true;//const bool
 
    decltype(i++) var14 = i;//int i++返回右值

    return 0;
}