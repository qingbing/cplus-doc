#include <stdio.h>

// 数组形参为指针
void print1(int *ptr, int sz)
{
    printf("数组打印1:");
    for (int i = 0; i < sz; i++)
    {
        printf(" %d", *(ptr + i));
    }
    printf("\n");
}
// 数组形参为未指定大小的数组
void print2(int param[], int sz)
{
    printf("数组打印2:");
    for (int i = 0; i < sz; i++)
    {
        printf(" %d", param[i]);
    }
    printf("\n");
}
// 数组形参为数组指针
void print3(int (*ptr)[], int sz)
{
    printf("数组打印3:");
    for (int i = 0; i < sz; i++)
    {
        printf(" %d", (*ptr)[i]);
    }
    printf("\n");
}
// 数组形参为指定大小的数组， 这个不严格，定义的长度传递不同长度也是可以的。
void print4(int param[5], int sz)
{
    printf("数组打印4:");
    for (int i = 0; i < sz; i++)
    {
        printf(" %d", param[i]);
    }
    printf("\n");
}

int main()
{
    // 逐个初始化数组
    int num_01[5];
    num_01[0] = 10;
    num_01[3] = 10;

    // 初始化语句, 大括号内数据个数不能大于数组的长度
    int num_02[5] = {10, 1, 2, 10};

    // 省略数组长度，长度为大括号中元素的个数
    int num_03[] = {10, 1, 2, 10, 0};

    int num_01[10] = {1, 2, 3, 4, 5, 6, 7, 8};
    print1(num_01, 10);
    print2(num_01, 10);
    print3(&num_01, 10);
    print4(num_01, 10);

    /* 针对二维数组，指针可以当作一维数组进行访问 */
    int num_61[2][3] = {
        {11, 12, 13},
        {21, 22, 23},
    };

    // 二维数组按下标访问
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("第 %d 行的第 %d 个元素，值为: %d\n", i, j, num_61[i][j]);
        }
    }
    // 二维数组按指针访问
    int *ptr_61;
    ptr_61 = num_61;
    for (int i = 0; i < 6; i++)
    {
        printf("二维数组的第 %d 个元素，值为: %d\n", i, *ptr_61);
        ptr_61++;
    }

    return 0;
}
