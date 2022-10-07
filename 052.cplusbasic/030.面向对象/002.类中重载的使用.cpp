#include <iostream>
using namespace std;

class Compute
{
public:
    int width{0};
    int height{0};
    Compute()
    {
    }
    // 构造函数重载
    Compute(int a, int b) : width(a), height(b)
    {
    }
    int add(int a, int b)
    {
        return a + b;
    }
    // 重载 add : 参数类型不同
    double add(double a, double b)
    {
        return a + b;
    }
    void print()
    {
        cout << "Width: " << this->width << "; Height: " << this->height << endl;
    }
    // 二元运算符 + 重载
    Compute operator+(const Compute &a)
    {
        Compute res; // 默认构造函数
        res.width = this->width + a.width;
        res.height = this->height + a.height;
        return res;
    }
};

int main(int argc, char const *argv[])
{
    Compute c1(11, 12);
    Compute c2(22, 24);
    c1.print();
    c2.print();
    Compute c3 = c1 + c2;
    c3.print();
    return 0;
}
