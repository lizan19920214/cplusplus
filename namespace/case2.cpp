#include <iostream>
using namespace std;

namespace Sweet
{
    int rand = 10;
}

//加上这句就会有重命名的报错，是因为在命名空间被全部展开，那么程序就在全局范围找到了两个rand，出现命名冲突
// using namespace Sweet;

//部分展开
// using std::cout;
// using std::endl;

int main()
{
    //这里我们可以看到并没有发生命名冲突，
    //因为rand是Sweet中的变量，而不是std中的变量，我们使用rand相当于不同年级的重名的同学
    cout << rand << endl; // 打印rand随机函数
    cout << Sweet::rand << endl; // 打印Sweet中的rand
    return 0;
}