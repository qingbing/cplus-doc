#include <stdio.h>

// 函数值传递
int sum(int a, int b)
{
    return a + b;
}

// 引用传递
void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int main(int argc, char const *argv[])
{
    // 值传递的函数
    int num_01 = 10;
    int num_02 = 20;
    int res = sum(num_01, num_02);
    printf("%d + %d = %d", num_01, num_02, res);
    printf("\n");

    // 引用传递
    int num_11 = 10;
    int num_12 = 20;
    printf("num_11: %d; num_12: %d", num_11, num_12);
    printf("\n");
    swap(&num_11, &num_12);
    printf("num_11: %d; num_12: %d", num_11, num_12);
    printf("\n");
    return 0;
}
