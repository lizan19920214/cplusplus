/**
 * 结构体所占空间：
 *      一般而言，struct 的 sizeof 是所有成员字节对齐后长度相加，而 union 的 sizeof 是取最大的成员长度。
 * 
 * 在默认情况下，编译器为每一个变量或数据单元按其自然对界条件分配空间。一般地，可以通过下面的方法来改变默认的对界条件：
 *      (1) 使用伪指令#pragma pack(n)，C编译器将按照n个字节对齐。
 *      (2) 使用伪指令#pragma pack()，取消自定义字节对齐方式。
 * 
 * 
 * 字节对齐的细节和编译器实现相关，但一般而言，满足以下3个准则：
 *      (1) 结构体变量的首地址能够被其最宽基本类型成员的大小所整除。
 *      (2) 结构体每个成员相对于结构体首地址的偏移量（offset）都是成员大小的整数倍，如有需要编译器会在成员之间加上填充字节。
 *      (3) 结构体的总大小为结构体最宽基本类型成员大小的整数倍，如有需要编译器会在最末一个成员之后加上填充字节。
 *      
 * ！！！！需要注意的是，基本类型是指前面提到的像 char、short、int、float、double 这样的内置数据类型。
 *      如果一个结构体中包含另外一个结构体成员，那么此时最宽基本类型成员不是该结构体成员，而是取基本类型的最宽值。
 * 
*/

#include <iostream>

using namespace std;

typedef struct
{
	char ch1;   // 1个字节，成员的大小为1，所以不用补齐，结构体大小就是1的整数倍，为3
	char ch2;
	char ch3;
}A1;

typedef struct
{
	int num;   // 4个字节
	char ch;    // 1字节，补齐4字节，总和8字节
}A2;

typedef struct
{
	char a; // 1字节+补齐
	int b; // 4字节  和前面的a组合成8字节
	long long  c;  // 8字节，不需要补齐
	char d; // 1字节，需要对齐8字节 因此总和为 8 + 8 + 8 = 24
}A3;

typedef struct
{
    //最大8字节，按照8字节补齐 8 + 8 + 8 = 24
	long num;       // 4字节  + 4
	char * name;    // 8字节  + 0
	short int data; // 2字节  data与ha合起来 补5字节
	char ha;        // 1字节
}A4;

int main(void)
{
	cout << "A1: " << sizeof(A1) << endl; // A1: 3
	cout << "A2: " << sizeof(A2) << endl; // A2: 8
	cout << "A3: " << sizeof(A3) << endl; // A3: 24
	cout << "A4: " << sizeof(A4) << endl; // A4: 24

	return 0;
}
