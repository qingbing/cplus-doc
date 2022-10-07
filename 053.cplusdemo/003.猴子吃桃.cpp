/*
一只小猴子一天摘了许多桃子，第一天吃了一半，然后忍不住又吃了一个；第二天又吃了一半，再加上一个；后面每天都是这样吃。到第10天的时候，小猴子发现只有一个桃子了。问小猴子第一天共摘了多少个桃子?

分析:
10 - 10: 1
10 - 9: (1 + 1) * 2 = 4
10 - 3: (4 + 1) * 2 = 10
10 - 4: (10 + 1) * 2 = 22
10 - 5: (22 + 1) * 2 = 46

10 - 0: ...

倒推法:
f(n) = 2(f(n-1) + 1)
*/

#include <iostream>
using namespace std;

int eatNum(int n)
{
    if (0 == n)
    {
        return 1;
    }
    return 2 * (eatNum(n - 1) + 1);
}

int main(int argc, char const *argv[])
{
    for (int i = 0; i < 10; i++)
    {
        cout << "第 " << i << " 天剩余: " << eatNum(i) << endl;
    }

    return 0;
}
