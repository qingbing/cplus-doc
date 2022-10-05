#include <stdio.h>
/*
将一个十六进制的无符号数进行翻转
个位放在最前，依次翻转
*/
unsigned int reversal_num_hex(unsigned int num)
{
    unsigned int r = 0;
    while (num > 0)
    {
        r <<= 4;
        r += num % 16;
        num /= 16;
    }
    return r;
}

/*
将一个10进制的无符号数进行翻转
个位放在最前，依次翻转
*/
unsigned int reversal_num(unsigned int num)
{
    unsigned int r = 0;
    while (num > 0)
    {
        r *= 10;
        r += num % 10;
        num /= 10;
    }
    return r;
}

int main(int argc, char const *argv[])
{
    unsigned int num;

    num = 0x134f56;
    printf("数据: %x 翻转后位: %x\n", num, reversal_num_hex(num));

    num = 134656;
    printf("数据: %d 翻转后位: %d\n", num, reversal_num(num));

    return 0;
}
