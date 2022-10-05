
#include <stdio.h>

void myPrint(int num)
{
    printf("Print: %d\n", num);
}

// 定义函数，第二个参数是函数指针
void say(int num, void (*ptr)(int))
{
    ptr(num);
}

int main(int argc, char const *argv[])
{
    // 定义一个函数指针
    // void (*ptr_fun)(int) = myPrint;
    void (*ptr_fun)(int) = &myPrint; // & 可以省略

    say(10, ptr_fun);
    say(12, ptr_fun);

    return 0;
}
