/**
 * 命名空间:
 * 
 * 语法：命名空间关键字（namespace）+命名空间的名字+{ 定义的东西 }
 * 命名空间中可以定义很多类型:变量、函数、结构体、类、其他命名空间等
 * 只要可以定义的东西都可以放到命名空间中定义
 * 
 * 定义位置：
 * 命名空间只能在全局或者另一个命名空间中定义，不能放在函数体内定义
 * 
 * 展开：命名空间展开并不是把命名空间拷贝过来了，命名空间的域与局部域和全局域还是不同的域
 * 此时队成员的访问可以不用在其前面假命名空间名+::了
 * 但是如果展开了多个命名空间，并且多个命名空间中定义的东西同名或者与全局域中定义的东西同名
 * 还是会出现类似重定义的问题
 * using +namespace +命名空间的名字
 * 
 * 展开命名空间中的某一个成员
 * using+命名空间名+：：+命名空间的成员
 * 
 * 命名空间重命名
 * namespace +别名=原命名空间名
*/
#include <stdio.h>
// #include <stdlib.h>

//这段代码不会报错，但是如果添加上rand函数的头文件
//则会出现重定义,原因是计算机会先在局部寻找变量，找不到再去全局找，但是在全局找的时候
// 找到了两个rand（一个全局变量，一个在头文件中的rand函数，发生冲突）
// #include <stdlib.h>
int rand = 10;

void test1()
{
    printf("%d\n", rand);
}


int main()
{
    test1();
    return 0;
}