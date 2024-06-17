/**
 * 二进制文件读写
*/
#include <iostream>
#include <fstream>
using namespace std;

struct st_girl
{
    char name[31]; //名字
    int no; //编号
    char memo[300]; //备注
    double weight; //体重
};


int main()
{
    //创建文件输出流对象
    ofstream fout;
    //以二进制形式打开
    fout.open("test.bat", ios::app | ios::binary);
    //判断文件是否打开
    if (!fout.is_open())
    {
        cout << "文件打开失败" << endl;
        return 0;
    }

    st_girl girl = {"西施", 3, "中国历史第一美女", 45.8};
    //以字符串形式写入
    fout.write((const char*)&girl, sizeof(girl));
    cout << "二进制写入成功" << endl;
    //关闭文件
    fout.close();

    //创建文件输入流对象
    ifstream fin;
    //以二进制打开文件
    fin.open("test.bat", ios::in | ios::binary);
    //判断文件是否打开
    if (!fin.is_open())
    {
        cout << "文件打开失败" << endl;
        return 0;
    }

    st_girl outGirl;
    //对文件以字符串形式读取
    while (fin.read((char*)&outGirl, sizeof(outGirl)))
    {
        cout << "姓名：" << outGirl.name << endl;
        cout << "编号：" << outGirl.no << endl;
        cout << "备注：" << outGirl.memo << endl;
        cout << "体重：" << outGirl.weight << endl;
    }
    cout << "文件以二进制读取成功" << endl;
    //关闭文件
    fin.close();

    return 1;
}