#include <iostream>
#include <memory>
#include <vector>

using namespace std;

void desc1()
{
    // 创建一个unique_ptr,使用裸指针初始化
    unique_ptr<int> ptr1(new int(10));
    //使用std::make_unique创建unique_ptr
    unique_ptr<int> ptr2 = make_unique<int>(20);

    //移动语义
    // std::unique_ptr 不允许复制，但可以移动，这意味着可以将所有权从一个unique_ptr转移给另一个
    std::unique_ptr<int> ptr3 = std::move(ptr1); // ptr1的所有权转移给ptr3

    // 释放内存
    ptr1.reset();
}

class MyClass 
{
public:
    MyClass(int value) : value(value) 
    {
        std::cout << "Constructor: " << value << std::endl;
    }
    ~MyClass() 
    {
        std::cout << "Destructor: " << value << std::endl;
    }
    void show() const 
    {
        std::cout << "Value: " << value << std::endl;
    }
private:
    int value;
};

int main() 
{
    // 使用std::unique_ptr管理动态分配的MyClass对象
    std::unique_ptr<MyClass> ptr1 = std::make_unique<MyClass>(1);
    ptr1->show();
    
    // 转移所有权
    std::unique_ptr<MyClass> ptr2 = std::move(ptr1);
    if (!ptr1) 
    {
        std::cout << "ptr1 is now null." << std::endl;
    }
    ptr2->show();
    
    // std::unique_ptr在容器中的使用
    std::vector<std::unique_ptr<MyClass>> vec;
    vec.push_back(std::make_unique<MyClass>(2));
    vec.push_back(std::make_unique<MyClass>(3));
    
    for (const auto& ptr : vec) 
    {
        ptr->show();
    }

    // 手动释放资源
    vec.clear();
    std::cout << "Vector cleared." << std::endl;

    return 0;
}