#include <stdio.h>
/*
gcc 019.命令行参数.c
./a.out good test hello
=== output ===
程序名: ./a.out
程序参数个数: 4
第 1 个参数: ./a.out
第 2 个参数: good
第 3 个参数: test
第 4 个参数: hello
*/
int main(int argc, char const *argv[])
{
    printf("程序名: %s\n", argv[0]);
    printf("程序参数个数: %d\n", argc);

    for (int i = 0; i < argc; i++)
    {
        printf("第 %d 个参数: %s\n", i + 1, argv[i]);
    }
    return 0;
}
