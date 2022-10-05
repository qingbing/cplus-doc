#include <stdio.h>
#include <stdarg.h>

double sum(int many, ...)
{
    va_list vaList;         // 定义一个变量，存放可变参数列表
    va_start(vaList, many); // 初始化可变参数列表
    // 循环访问 vaList
    double sum = 0;
    for (int i = 0; i < many; i++)
    {
        sum += va_arg(vaList, double); // va_arg 后面一个参数为变量类型，int， char*, double, 不支持 float
    }
    va_end(vaList); // 清理 vaList 保留的内存
    return sum;
}

int main(int argc, char const *argv[])
{
    printf("sum: %.3f\n", sum(3, 4.0, 5.0, -6));
    printf("sum: %.3f\n", sum(4, 5.0, 6.0, 8.0, 9.1));
    return 0;
}