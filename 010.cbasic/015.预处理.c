
#include <stdio.h>
#include <math.h>

#define PI 3.1415926

#ifdef PI
#undef PI
#define PI 3.14
#endif

// 有添加引用头文件
#if SYSTEM_1
#include "system_1.h"
#elif SYSTEM_2
#include "system_2.h"
#endif

/*
// 直接使用宏名进行预处理定义
 #define SYSTEM_H "system_1.h"
 ...
 #include SYSTEM_H
*/

// 只引用一次
/*
#ifndef HEADER_FILE
#define HEADER_FILE
...
#endif
*/

#define helloWorld() printf("Hello World\n")                            // 函数宏
#define hello(name) printf("Hello " #name "\n")                         // 函数参数化宏
#define tokenpaster(num, token) printf(#token #num " = %d", token##num) // 使用 "##" 合并两个标记成一个
#define square(x) (x * x)                                               // 参数化的宏 => type square(type x) {return x * x;}

int main(int argc, char const *argv[])
{
    // 系统预定义宏
    printf("File :%s\n", __FILE__);
    printf("Date :%s\n", __DATE__);
    printf("Time :%s\n", __TIME__);
    printf("Line :%d\n", __LINE__);
    printf("ANSI :%d\n", __STDC__);
    // 自定义宏
    printf("PI: %f\n", PI);
    // 函数宏
    helloWorld();      // Hello World
    hello(qingbing);   // Hello qingbing
    hello("qingbing"); // Hello "qingbing"
    // ## 宏的标签合并, 必须确保组合的标签时存在的变量，否则编译不通过
    int name10 = 31;
    tokenpaster(10, name); // name10 = 31
    // 参数化宏
    printf("%d 的平方 = %d\n", 10, square(10));
    printf("%f 的平方 = %f\n", 10.1, square(10.1));
    return 0;
}
