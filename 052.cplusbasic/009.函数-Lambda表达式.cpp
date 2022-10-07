#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
    int num_01{100};
    int num_02{200};
    int num_03{300};

    // []: 内部不能访问任何变量
    []()
    { cout << "不能访问任何变量" << endl; }();

    // [=]: 任何被使用到的外部变量都隐式地以传值方式加以引用
    [=]()
    {
        cout << "[=] 任何被使用到的外部变量都隐式地以传值方式加以引用" << endl;
        cout << "num_01: " << num_01 << "; num_02: " << num_02 << endl;
        // num_01 = 300; // 由于时值传递，不能修改，编译不通过
    }();
    cout << "num_01: " << num_01 << "; num_02: " << num_02 << endl;

    // [&]: 任何被使用到的外部变量都隐式地以引用方式加以引用
    [&]()
    {
        cout << "[&] 所有外部变量以引用方式隐式传递，修改会印象外部变量" << endl;
        cout << "num_01: " << num_01 << "; num_02: " << num_02 << endl;
        num_02 = 400;
    }();
    cout << "[&]: num_02值被修改了: " << num_02 << endl;

    // [x, &y]: x以传值方式传入（默认），y以引用方式传入
    [&num_02, num_01]()
    {
        cout << "[x, &y]: x以传值方式传入(默认), y以引用方式传入" << endl;
        cout << "num_01: " << num_01 << "; num_02: " << num_02 << endl;
        // num_01 = 300; // 由于时值传递，不能修改，编译不通过
        num_02 = 500;
    }();
    cout << "[&]: num_02值被修改了: " << num_02 << endl;

    // [&, x]: x显式地以传值方式加以引用。其余变量以引用方式加以引用
    [&, num_01]()
    {
        cout << "[&, x]: x显式地以传值方式加以引用。其余变量以引用方式加以引用" << endl;
        cout << "num_01: " << num_01 << "; num_02: " << num_02 << endl;
        num_02 = 700;
    }();
    cout << "[&]: num_02值被修改了: " << num_02 << endl;

    // [=, &z]: z显式地以引用方式加以引用。其余变量以传值方式加以引用
    [=, &num_02]()
    {
        cout << "[=, &z]: z显式地以引用方式加以引用。其余变量以传值方式加以引用" << endl;
        cout << "num_01: " << num_01 << "; num_02: " << num_02 << endl;
        num_02 = 800;
    }();
    cout << "[&]: num_02值被修改了: " << num_02 << endl;

    // lambda 制作命名函数调用
    auto lambda_01 = [=]()
    {
        cout << "num_01: " << num_01 << "; num_02: " << num_02 << "; num_03: " << num_03 << endl;
    };
    lambda_01();

    // lambda 传递参数
    auto lambda_02 = [](string name, string message = "Hello World")
    {
        cout << name << "say: \"" << message << "\"" << endl;
    };
    lambda_02("qingbing");
    lambda_02("qingbing", "ok");

    // 带返回值的 lambda
    auto lambda_sum = [](int a, int b) -> int
    {
        return a + b;
    };
    int a{10};
    int b{20};
    cout << a << " + " << b << " = " << lambda_sum(a, b) << endl;
    return 0;
}
