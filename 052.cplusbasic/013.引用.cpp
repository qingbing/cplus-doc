#include <iostream>
using namespace std;

void swap(int &a, int &b)
{
    int t = a;
    a = b;
    b = t;
}

int &getVariableAlias(int vals[], int i)
{
    int &v = vals[i];
    return v;
}

int main(int argc, char const *argv[])
{
    int num_01 = 1;
    int &num_02 = num_01; // 定义引用

    // 操作引用和操作变量对内存改变效果是一样的
    cout << "num_01: " << num_01 << "; num_02: " << num_02 << endl;
    num_01 = 2;
    cout << "num_01: " << num_01 << "; num_02: " << num_02 << endl;
    num_02 = 3;
    cout << "num_01: " << num_01 << "; num_02: " << num_02 << endl;

    // 将应用作为参数
    int num_11 = 100;
    int num_12 = 200;
    int &num_13 = num_11;
    int &num_14 = num_12;
    cout << "交换前: "
         << "num_11: " << num_11 << "; num_12: " << num_12 << endl;
    swap(num_13, num_14);
    cout << "交换后: "
         << "num_11: " << num_11 << "; num_12: " << num_12 << endl;

    // 函数返回引用
    int vals[5]{1, 2, 3, 4, 5};

    cout << "改变前" << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << vals[i] << " ";
    }
    cout << endl;

    getVariableAlias(vals, 2) = 100;

    cout << "改变后" << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << vals[i] << " ";
    }
    cout << endl;
    return 0;
}
