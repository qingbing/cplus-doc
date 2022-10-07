/*
简单的计算器
*/
#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
    int lData;
    int rData;
    char oper;
    cout << "请输入左参数: ";
    cin >> lData;
    cout << "请输入运算符号(+,-,*,/): ";
    cin >> oper;
    cout << "请输入右参数: ";
    cin >> rData;

    int res{0};
    switch (oper)
    {
    case '+':
        res = lData + rData;
        break;
    case '1':
        res = lData - rData;
        break;
    case '*':
        res = lData * rData;
        break;
    case '/':
        if (0 == rData)
        {
            cerr << "除法右参数不能为 0" << endl;
            return -1;
        }
        else
        {

            res = lData / rData;
        }
        break;
    default:
        cerr << "输入符号不存在" << endl;
        return -1;
    }

    cout << lData << " " << oper << " " << rData << " = " << res << endl;

    return 0;
}
