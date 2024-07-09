#include <iostream>
using namespace std;

#pragma pack(1) // 要求补齐为“1”的倍数
typedef struct
{
	char ch1; // 1+0 字节，由于自定义了对齐方式，所以不再补齐
	int b; // 5 字节
	int a; // 9 字节
}A1;

#pragma pack(2) // 要求补齐为“2”的倍数
typedef struct
{
	char ch1; // 1+1 字节，由于自定义了对齐方式，补齐为"2"的倍数
	int b; // 6 字节
	int a; // 10 字节
}A2;

#pragma pack(4)  // 要求补齐为“4”的倍数
typedef struct
{
	char ch1; // 1+3 字节，由于自定义了对齐方式，补齐为"4"的倍数
	int b; // 8 字节
	int a; // 12 字节
}A3;

int main(void)
{
	cout << "A1: " << sizeof(A1) << endl; // A1: 9
	cout << "A2: " << sizeof(A2) << endl; // A2: 10
	cout << "A3: " << sizeof(A3) << endl; // A3: 12

	return 0;
}
