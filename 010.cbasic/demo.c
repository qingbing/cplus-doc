#include <stdio.h>
#include <float.h>


int add()
{
    extern int x;
    extern int y;
    x = 1;
    y = 2;
    return x + y;
}

int main(int argc, char const *argv[])
{
    // sizeof 用法
    printf("short 存储最大字节: %lu \n", sizeof(short)); // 2
    printf("int 存储最大字节: %lu \n", sizeof(int));     // 4
    printf("float 存储最大字节: %lu \n", sizeof(float)); // 4
    // float.h
    printf("float 最小值: %E \n", FLT_MIN); // 1.175494E-38
    printf("float 最大值: %E \n", FLT_MAX); // 3.402823E+38
    printf("float 精度值: %d \n", FLT_DIG); // 6

    printf("%d; \n", add());

    return 0;
}
