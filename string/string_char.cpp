/**
 * string和char的互相转换
*/
#include <iostream>
#include <cstring>
#include <bitset>
#include <netinet/in.h>
using namespace std;

//char数组转string，直接赋值
void char2String()
{
    char a[] = "hello world";
    string b = a;
    cout << b << endl;
}

//string转char数组,使用strcpy函数和string的data函数
// **1、strcpy不能赋值给char指针 ，只能赋值给char数组 
// **2、char数组长度，必须大于等于string长度 

void string2Char()
{
    string str = "hello world";
    char b[str.length() + 1];

    strcpy(b, str.data());

    cout << b << endl;
}

//string转char指针，使用string的data函数或者c_str
// 只能赋值给const char指针，不能赋值给char指针
//需要注意的是const char指针只说明它指向的东西不能被修改，不是说它不能改变指向
void string2CharPoint()
{
    string str = "hello world";
    const char* b = str.data();
    // const char* b = str.c_str();
    cout << b << endl;

    char a[] = "Nice";
    b = a;
    cout << b << endl;
}

void string2Mask()
{
    string str = "c1";
    const char* msg = str.c_str();
    int pos = 0;

    //取c的ASCII码转为整数->99
    cout << msg[pos] << " toint:" << uint64_t(msg[pos]) << endl;

    //转为二进制->0110 0011
    bitset<8> binary(msg[pos]);
    string strBinary = binary.to_string();
    cout << "orBinary: " << strBinary << endl;

    //依次右移
    for (int i = 0; i < 8; i++)
    {
        uint64_t payload_length_ = msg[pos] >> i;
        bitset<8> binary(payload_length_);
        string strBinary = binary.to_string();
        cout <<"to_binary: "<< strBinary << " to_ten: " << payload_length_ << " right:" << i  << endl;
    }
    
    uint16_t length = 0;
    memcpy(&length, msg + pos, 2);
    uint64_t payload_length_ = ntohs(length);
    cout << payload_length_ << endl;
}

int main()
{
    char2String();
    string2Char();
    string2CharPoint();
    string2Mask();
    return 0;
}