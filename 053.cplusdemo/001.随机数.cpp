#include <iostream>
using namespace std;

int get_rand()
{
    static bool isSrand{false};
    if (!isSrand)
    {
        srand((unsigned)time(NULL)); // time(NULL) 只是到秒级别，不够精确
    }
    isSrand = true;
    return rand();
}

int get_random(int a, int b = 0)
{
    int max, min;
    if (a == b)
    {
        return a;
    }
    else if (a > b)
    {
        max = a;
        min = b;
    }
    else
    {
        max = b;
        min = a;
    }

    return rand() % (max - min) + min;
}

int main(int argc, char const *argv[])
{
    // 随机数获取
    cout << get_rand() << endl;
    cout << get_rand() << endl;
    // 获取范围内随机数
    cout << get_random(10) << endl;
    cout << get_random(10) << endl;
    cout << get_random(10, 100) << endl;
    cout << get_random(10, 100) << endl;
    cout << get_random(10, 100) << endl;
    return 0;
}
