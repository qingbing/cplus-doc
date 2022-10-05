#include <stdio.h>

int main(int argc, char const *argv[])
{
    // while 循环
    int a = 5;
    while (a > 0)
    {
        printf("while 当前数据: %d\n", a);
        a--;
    }

    // do-while 循环
    int b = 10;
    do
    {
        b--;
        if (7 == b)
        {
            continue; // 跳出本次循环
        }
        if (4 == b)
        {
            break; // 结束循环
        }
        printf("do-while 当前数据: %d\n", b);
    } while (b > 0);

    // for 循环
    for (int i = 0; i < 5; i++)
    {
        printf("for 当前数据: %d\n", i);
    }

    // 无限循环， 内部需要使用 goto 或 break 跳出循环
    /*
    for (;;)
    {
        // code
    }
    while (1)
    {
        // code
    }
    do
    {
        // code
    } while (1);
    */

    int c = 5;
    while (1)
    {
        c--;
        printf("无限循环 当前数据: %d\n", c);
        if (c < 0)
        {
            goto out;
        }
    }
out:
    printf("\n结束了\n");
    return 0;
}
