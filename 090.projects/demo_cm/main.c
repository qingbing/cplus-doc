#include <stdio.h>
#include "test.h"
#include "test_01/test_01.h"
#include "test_02/test_02.h"
#include "static-mymath.h"
#include "sync-mymath.h"


// 1. 直接运行
// 2. 加载当前目录
// 3. 加载子目录
// 4. 子目录单独编译， 有 CMakeLists.txt
// 5. 外部静态库加载
// 6. 外部动态库加载

int main(int argc, char const *argv[])
{
    printf("==== 直接运行 ====\n");
    printf("Hello World!\n");

    printf("==== 加载当前目录 ====\n");
    print_test_main();

    printf("==== 加载子目录 ====\n");
    print_test01();

    printf("==== 子目录单独编译， 有 CMakeLists.txt ====\n");
    print_test02();

    printf("==== 外部静态库加载 .a 文件 ====\n");
    printf("7+5 = %d\n", StaticAdd(7, 5));
    printf("7-5 = %d\n", StaticSub(7, 5));

    printf("==== 外部动态库加载 .so 文件 ====\n");
    printf("7+5 = %d\n", SyncAdd(7, 5));
    printf("7-5 = %d\n", SyncSub(7, 5));
    return 0;
}
