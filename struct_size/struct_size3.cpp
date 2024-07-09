#include <iostream>

using namespace std;

typedef struct
{
    // 4 + 4 + 4 = 12
	short i; // 2字节
	char c; // 1字节 4字节对齐，与i一起补1字节
	int j; // 4字节
	int k; // 4字节
}A1;

/*
如果结构体中的成员又是另外一种结构体类型时应该怎么计算呢？只需把其展开即可。
但有一点需要注意，展开后的结构体的第一个成员的偏移量应当是被展开的结构体中最大的成员的整数倍。
结构体stu5的成员ss.c的偏移量应该是4，而不是2。

如下：
    在A内部按照4字节对齐，因此A为8字节
    展开后最大为int的4字节，因此按照4字节对齐，i补2字节到4字节
    因此大小为 4 + 8 + 4 = 16
*/
typedef struct
{
	short i; // 2 补2字节到4字节对齐
	struct
	{
		char c; // 1字节 在A内补3字节到4字节对齐
		int j; // 4字节
	}A;

	int k; // 4字节
}A2;

int main(void)
{
	cout << "A1: " << sizeof(A1) << endl; // A1: 12
	cout << "A2: " << sizeof(A2) << endl; // A2: 16

	return 0;
}
