#include <stdio.h>

/*
最大最大公约数：

循环比较
    大数 == 小数； 这个小数就是最大最大公约数
    大数 = 大数-小数
*/
int max_common_divisor(int a, int b)
{
    while (a != b)
    {
        if (a > b)
        {
            a -= b;
        }
        else
        {
            b -= a;
        }
    }
    return a;
}

int main(int argc, char const *argv[])
{
    int a, b;

    a = 10;
    b = 25;
    printf("%d, %d 的最大公约数是: %d\n", a, b, max_common_divisor(a, b));

    a = 99;
    b = 18;
    printf("%d, %d 的最大公约数是: %d\n", a, b, max_common_divisor(a, b));
    return 0;
}
