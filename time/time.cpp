/**
 * g++ -o time time.cpp
 * 
 * 有四个与时间相关的类型：clock_t、time_t、size_t 和 tm。类型 clock_t、size_t 和 time_t 能够把系统时间和日期表示为某种整数。
 * time_t是系统定义的长整形，也就是long int，他的单位一般是秒
 * clock_t也是长整形，但是一般他的单位是毫秒
 * size_t 是一些C/C++标准中定义的，size_t 类型表示C中任何对象所能达到的最大长度，它是无符号整数。
 * 结构类型 tm 把日期和时间以 C 结构的形式保存，tm 结构的定义如下：
 * struct tm {
 *   int tm_sec;   // 秒，正常范围从 0 到 59，但允许至 61
 *   int tm_min;   // 分，范围从 0 到 59
 *   int tm_hour;  // 小时，范围从 0 到 23
 *   int tm_mday;  // 一月中的第几天，范围从 1 到 31
 *   int tm_mon;   // 月，范围从 0 到 11
 *   int tm_year;  // 自 1900 年起的年数
 *   int tm_wday;  // 一周中的第几天，范围从 0 到 6，从星期日算起
 *   int tm_yday;  // 一年中的第几天，范围从 0 到 365，从 1 月 1 日算起
 *   int tm_isdst; // 夏令时
 * };
 * 
*/

#include <iostream>
#include <ctime>

using namespace std;

int main() 
{
    time_t curtime = 0;
    
    //time_t time(time_t* time);
    //该函数返回系统的当前日历时间，自1970年1月1日以来经过的秒数
    //既常说的时间戳
    //时间戳没有时区概念，是一个固定时间，但是时间戳所转换显示的时间是和时区有关的
    //比如2021-01-12 03:00:00，获取到对应的时间戳是：1610391600
    //但是他对应的莫斯科时间为2021-01-11 22:00:00，这显然和东八区与东三区的时差（五个小时）是对得上的。

    time_t time_now_0 = time(&curtime);
    cout << "time:" << time_now_0 << endl;

    //char* ctime(const time_t* time);
    //该函数返回一个表示当地时间的字符串，其形式为"Fri Feb 28 22:23:08 2020\n\0"
    char* time_now_1 = ctime(&curtime);
    cout << "ctime:" << time_now_1 <<endl;

    //struct tm* localtime(const time_t* time);
    //该函数返回一个表示当地时间的tm结构的指针
    struct tm* tm1 = NULL;
    tm1 = localtime(&curtime);
    cout << "localtime:" << tm1->tm_year << endl;
    cout << "localtime:" <<  tm1->tm_mon << endl;
    cout << "localtime:" <<  tm1->tm_mday << endl;
    cout << "localtime:" <<  tm1->tm_hour << endl;
    cout << "localtime:" <<  tm1->tm_min << endl;
    cout << "localtime:" <<  tm1->tm_sec << endl;

    //clock_t clock(void);
    //该函数返回程序执行起（一般为程序运行时），处理器时钟所使用的时间。如果时间不可用，则返回-1
    clock_t start, end;
    start = clock();
    for (long i = 0; i < 1000000000; i++)
    {
    }

    end = clock();
    cout << "clock:" << (double)(end - start) / CLOCKS_PER_SEC << endl;
    
    //struct tm* gmtime(const time_t* time);
    //该函数返回一个指向time的指针，time为tm结构，用协调世界时（UTC）也被称为格林尼治标准时间（GMT）表示。
    struct tm* tm2 = NULL;
    tm2 = gmtime(&curtime);
    cout << "gmtime:" << tm2->tm_year << endl;
    cout << "gmtime:" << tm2->tm_mon << endl;
    cout << "gmtime:" << tm2->tm_mday << endl;
    cout << "gmtime:" << tm2->tm_hour << endl;

    //double difftime(time_t time1, time_t time2);
    //该函数返回time1和time2之间相差的秒数，time1是开始时间 time2是结束时间
    start = time(0);
    for (long i = 0; i < 1000000000; i++)
    {
    }
    end = time(0);
    cout << "difftime:" << difftime(end, start) << endl;


    // size_t strftime(char *str, size_t maxsize, const char *format, const struct tm *timeptr)
    // 该函数可用于格式化日期和时间为指定的格式。如果产生的 C 字符串小于 size 个字符（包括空结束字符），则会返回复制到 str 中的字符总数（不包括空结束字符），否则返回零
    char buffer[80];
    struct tm *info = localtime(&curtime);
    strftime(buffer,80,"%Y-%m-%d %H:%M:%S",info);
    cout << "buffer:" << buffer << endl;


    return 0;
}