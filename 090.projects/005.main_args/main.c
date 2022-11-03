#include <stdio.h>

int main(int argc, char const *argv[], char const *envp[])
{
    // main 函数的第一个参数表示传递参数的个数
    printf("传递的参数个数: %d\n", argc);

    // main 函数的第二个参数为字符串数组，表示传递的字符串数组，索引 argv[0] 表示的是程序名
    printf("====== 传递的参数值 ======\n");
    for (int i = 0; i < argc; i++)
    {
        printf("第 %d 个参数是: %s\n", i + 1, argv[i]);
    }

    // envp 参数
    printf("====== 环境变量参数值 ======\n");
    int i = 0;
    while (0 != envp[i])
    {
        printf("第 %d 个参数是: %s\n", i + 1, envp[i]);
        i++;
    }
    return 0;
}
