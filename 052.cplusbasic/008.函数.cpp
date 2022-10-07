#include <iostream>
using namespace std;

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void say_message(string name, string message = "Hello c++")
{
    cout << name << "say: \"" << message << "\"" << endl;
}

int main(int argc, char const *argv[])
{
    int a = 100;
    int b = 200;
    cout << "变换前, a = " << a << "; b = " << b << endl;

    // 函数传递引用
    int &a1 = {a};
    int &b1 = {b};
    swap(a1, b1);
    cout << "变换后, a = " << a << "; b = " << b << endl;

    // 函数默认值的使用
    say_message("qingbing", "ok");
    say_message("qingbing"); // 默认值

    // Lambda 函数与表达式
    int num_01 = 100;
    int num_02 = 200;
    auto num_03 = [&](int x, int y) -> int
    {
        return x + y;
    };

    cout << num_01 << ":" << num_02 << ":" << num_03(12, 33) << endl;

    return 0;
}
