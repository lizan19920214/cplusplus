// C++11 引入了基于范围的迭代写法，我们拥有了能够写出像 Python 一样简洁的循环语句。
// 最常用的 std::vector 遍历将从原来的样子：

#include <vector>
#include <iostream>

void test1()
{
    std::vector<int> arr(5, 100);
    for(std::vector<int>::iterator i = arr.begin(); i != arr.end(); ++i) 
    {
        std::cout << *i << std::endl;
    }
}

// 变得非常的简单：

void test2()
{
    std::vector<int> arr(5, 100);
    for(auto i : arr) 
    {    
        std::cout << i << std::endl;
    }
}

int main()
{
    test1();
    test2();
    return 0;
}