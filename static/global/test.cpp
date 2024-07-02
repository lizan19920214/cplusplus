/**
 * static修饰全局变量和函数
 * 全局或者命名空间范围内(在单个文件范围内声明变量或者函数时) static关键字指定变量或者函数为内部链接
 *      也就是外部文件无法引用该变量和函数
 * 
 * 1.首先说一下全局变量，全局变量的作用域十分的广，只要在一个源文件中定义后，这个程序中的所有源文件、对象以及函数都可以调用，
 *      生命周期更是贯穿整个程序。文件中的全局变量想要被另一个文件使用时就需要进行外部声明（以下用extern关键字进行声明）。
 *      -----也即是说全局变量既可以在源文件中使用，也可以在其他文件中使用（只需要使用extern外部链接以下即可）
 * 
 * 2. static修饰全局变量和函数时，会改变全局变量和函数的链接属性-------变为只能在内部链接，从而使得全局变量的作用域变小
 *      这里也可以看到static在修饰全局变量和函数时，有收敛其作用域的作用
*/
#include <iostream>
#include "hello.h"

extern char a; // 声明外部变量a
extern void PrintfHelloA(); // 声明外部函数PrintfHelloA


//因为b和PrintfHelloB为static类型的全局变量和函数，因此只能在hello.h中使用
//外部文件无法声明使用
// extern char b; // 声明外部变量a
// extern void PrintfHelloB(); // 声明外部函数PrintfHelloB


using namespace std;

int main()
{
    cout << a << endl;
    PrintfHelloA();

    // cout << b << endl;
    // PrintfHelloB();
    return 0;
}