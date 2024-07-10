/**
 * auto类型推导
 * 
 * 
*/

#include <iostream>
#include <vector>
#include <string>
#include <memory>

//注意！！！！auto不能用于函数传参
// void add(auto x, auto y)
// {
//     std::cout << x + y << std::endl;
// }

int main()
{
    //推导迭代器
    std::vector<int> vec = {1, 2, 3, 4, 5};
    for (auto it = vec.begin(); it != vec.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    //其他常见用法：
    auto a = 5;
    auto p_int = new auto(10); //arr 推导为int*
    auto b = std::make_shared<std::string>("hello world"); //b 推导为std::shared_ptr<std::string>

    //此外auto不能用于推导数组类型
    int arr[10] = {0};
    auto arr2 = arr; //arr2 推导为int*
    // auto auto_arr2[10] = arr; // 报错

    return 0;
}