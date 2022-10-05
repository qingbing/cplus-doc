#include <stdio.h>
#include <math.h>
/*
阿姆斯壮数: 就是n位数的各位数的n次方之和等于该数，如：

153=1^3+5^3+3^3
1634=1^4+6^4+3^4+4^4

编译: gcc 008.阿姆斯壮数.c -lm
执行: ./a.out
*/
int armstrong(unsigned int num)
{
    int n = 0;
    unsigned int temp = num;
    // 计算位数
    do
    {
        n++;
        temp /= 10;
    } while (temp > 0);

    // 判断
    temp = num;
    unsigned int res = 0;
    do
    {
        res += pow(temp % 10, n);
        temp /= 10;
    } while (temp > 0);
    return res == num ? 1 : 0;
}

int main(int argc, char const *argv[])
{
    int num;

    num = 153;
    printf("数: %d, 阿姆斯壮数判断结果为: %s\n", num, armstrong(num) == 0 ? "不是" : "是");

    num = 19;
    printf("数: %d, 阿姆斯壮数判断结果为: %s\n", num, armstrong(num) == 0 ? "不是" : "是");

    num = 1634;
    printf("数: %d, 阿姆斯壮数判断结果为: %s\n", num, armstrong(num) == 0 ? "不是" : "是");
    return 0;
}
