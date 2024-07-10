// C++11 引入了基于范围的迭代写法，我们拥有了能够写出像 Python 一样简洁的循环语句。
// 最常用的 std::vector 遍历将从原来的样子：

#include <vector>
#include <iostream>
#include <set>

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

//需要注意的细节
void test3()
{
    // 1、使用for范围循环同样要注意容器本身的约束，比如set容器为只读，如下就会报错
    std::set<int> set = {1, 2, 3, 4, 5};
    for(auto& n : set) 
    {    
        // n++; error
    }

    // 2、循环的vector插入数据同样出现迭代器失效
    std::vector<int> arr(5, 100);
    for(auto& i : arr) 
    {    
        i = 0;
        // arr.push_back(3); 迭代器失效
    }
}

int main()
{
    test1();
    test2();
    test3();
    return 0;
}