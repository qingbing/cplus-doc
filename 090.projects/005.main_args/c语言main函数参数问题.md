# c语言 main 函数参数问题

- 参考链接
  - https://blog.csdn.net/wucz122140729/article/details/98435291


main 函数是c语言程序的入口， 其是可以接受参数的，参数从命令提示符下执行程序的时候传入(启动时确定)

## main 函数有三个参数

- int argc: 用于存放命令行参数的个数
- char *argv[]: 是个字符串的数组，每个元素都是一个字符指针，指向一个字符串，即命令行中的每一个参数
- char *envp[]: 也是一个字符串的数组，这个数组的每一个元素是指向一个环境变量的字符指针, 该参数使用很少

## main 函数参数使用 demo

```c
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
```
