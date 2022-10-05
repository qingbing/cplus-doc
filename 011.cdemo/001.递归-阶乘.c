#include <stdio.h>
/**
 * 阶乘: 1 * 2 * ... n
 */
unsigned int factorial(unsigned int num)
{
    if (num > 1)
    {
        return num * factorial(num - 1);
    }
    return 1;
}

int main(int argc, char const *argv[])
{
    unsigned int num;

    num = 3;
    printf("%d 的阶乘: %d\n", num, factorial(num));

    num = 6;
    printf("%d 的阶乘: %d\n", num, factorial(num));

    num = 10;
    printf("%d 的阶乘: %d\n", num, factorial(num));

    return 0;
}
