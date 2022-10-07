#include <iostream>
using namespace std;

/*
闰年
1. 年份为 100 的倍数，是 400 的倍数的年份是闰年
2. 年份不为 100 的倍数，是 4 的倍数的年份是闰年
*/

bool isLeapYear(unsigned int year)
{
    if (year % 100 == 0)
    {
        return !(year % 400);
    }
    return !(year % 4);
}

int main(int argc, char const *argv[])
{
    unsigned int year;
    year = 2100;
    cout << "年份: " << year << (isLeapYear(year) ? "是" : "不是")
         << "闰年" << endl;

    year = 2000;
    cout << "年份: " << year << (isLeapYear(year) ? "是" : "不是")
         << "闰年" << endl;

    year = 2010;
    cout << "年份: " << year << (isLeapYear(year) ? "是" : "不是")
         << "闰年" << endl;

    year = 2012;
    cout << "年份: " << year << (isLeapYear(year) ? "是" : "不是")
         << "闰年" << endl;
    return 0;
}
