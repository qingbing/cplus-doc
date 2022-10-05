#include <stdio.h>
/**
 * 斐波那契数列
 * f(0) = 0
 * f(1) = 1
 * f(n) = f(n-1) + f(n-2)
 */
unsigned int fibonaci(unsigned int num)
{
    if (0 == num || 1 == num)
    {
        return num;
    }
    return fibonaci(num - 1) + fibonaci(num - 2);
}

int main(int argc, char const *argv[])
{
    unsigned int num;

    num = 3;
    printf("%d 的斐波那契数列: %d\n", num, fibonaci(num));

    num = 6;
    printf("%d 的斐波那契数列: %d\n", num, fibonaci(num));

    num = 10;
    printf("%d 的斐波那契数列: %d\n", num, fibonaci(num));

    return 0;
}
