#include <stdio.h>

/*
最小公倍数 = a*b/最大最小公倍数
*/

int min_common_multiple(int a, int b)
{
    int total = a * b;
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
    return total / a;
}

int main(int argc, char const *argv[])
{
    int a, b;

    a = 10;
    b = 25;
    printf("%d, %d 的最小公倍数是: %d\n", a, b, min_common_multiple(a, b));

    a = 99;
    b = 18;
    printf("%d, %d 的最小公倍数是: %d\n", a, b, min_common_multiple(a, b));
    return 0;
}
