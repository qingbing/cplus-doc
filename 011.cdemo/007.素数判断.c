#include <stdio.h>
#include <math.h>
/*
质数（prime number）又称素数，有无限个。质数定义为在大于1的自然数中，除了1和它本身以外不再有其他因数，这样的数称为质数
*/
int isPrime(int num)
{
    // sqrt
    // int max = (int)(sqrt((double)num)); // 编译这句需要加入 gcc .. -lm, 否则 "undefined reference to `sqrt'"
    for (int i = 2; i < num / 2; i++)
    {
        if (num % i == 0)
        {
            return 1;
        }
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    int num;

    num = 14;
    printf("数: %d, 素数判断结果为: %s\n", num, isPrime(num) == 0 ? "不是" : "是");

    num = 19;
    printf("数: %d, 素数判断结果为: %s\n", num, isPrime(num) == 0 ? "不是" : "是");
    return 0;
}
