/**
 * 文本文件读写
 * g++ -o fstream fstream.cpp
*/
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
    //创建文件输出流对象
    ofstream fout;
    //打开文件，没有就创建
    fout.open("test.txt");
    //判断文件是否打开
    if (fout.is_open() == false)
    {
        cout << "打开文件失败" << endl;
        return 0;
    }

    //对文件进行写入
    string str = "hello world\n 11111\n 2222";
    fout << str;
    //关闭文件
    fout.close();
    cout << "文件写入成功" << endl;

    //创建文件输出流
    ifstream fin;
    string buff;
    //打开文件
    fin.open("test.txt");
    //判断文件是否存在
    if (fin.is_open() == false)
    {
        cout << "打开文件失败" << endl;
        return 0;
    }
    
    //读取文件内容并打印
    while (getline(fin, buff))
    {
        cout << buff << endl;
    }
    cout << "文件读取成功" << endl;

    //关闭文件
    fin.close();
    
    return 1;
}