#ifndef _HELLO_H_
#define _HELLO_H_

#include <iostream>
using namespace std;

char a = 'A';
void PrintfHelloA()
{
    cout << "hello static a" << endl;
};


static int b = 'B';
static void PrintfHelloB()
{
    cout << "hello static b" << endl;
};

#endif // !_HELLO_H_
