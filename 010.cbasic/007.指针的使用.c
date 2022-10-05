#include <stdio.h>

// 申明函数
extern void swap(int *a, int *b);
extern int *create_arr();

int main(int argc, char const *argv[])
{
    /* 指针的基础使用 */
    // 指针定义，修改指针内容，相应的变量也就改变了
    int num_01 = 100;
    int *ptr_num_01 = &num_01;
    printf("地址: %p, 值: %d\n", ptr_num_01, *ptr_num_01);
    *ptr_num_01 = 1000;
    printf("%d %d\n", *ptr_num_01, num_01);

    /* 空指针 NULL */
    int *ptr_num_02 = NULL;
    // ptr_num_02 = &num_01;
    // 空指针判断
    if (ptr_num_02)
    {
        printf("不是空指针。地址: %p, 值: %d\n", ptr_num_02, *ptr_num_02);
    }
    else
    {
        printf("空指针。地址: %p\n", ptr_num_02); // nil
    }

    /* 指针的运算 */
    int num_11[5] = {
        11,
        12,
        13,
        14,
    };
    int *ptr_11 = num_11;
    // 对于数组变量，其实就是一个指针
    printf("数组地址: %p； 指针地址: %p； \n", num_11, ptr_11); // nil
    for (int i = 0; i < 5; i++)
    {
        printf("第 %d 个元素的值是: %d\n", i, *ptr_11);
        ptr_11++;
    }
    // 指针比较
    ptr_11 = &num_11[4];
    while (ptr_11 > num_11)
    {
        printf(" %d", *ptr_11);
        ptr_11--;
    }
    printf("\n");

    /* 指针数组 */
    int num_21 = 21;
    int num_22 = 22;
    int num_23 = 23;
    int *ptr_21[3];
    ptr_21[0] = &num_21;
    ptr_21[1] = &num_22;
    ptr_21[2] = &num_23;
    for (int i = 0; i < 3; i++)
    {
        printf("第 %d 个元素的值是: %d\n", i, *(*ptr_21 + i));
        printf("第 %d 个元素的值是: %d\n", i, *ptr_21[i]);
    }

    /* 指向指针的指针 */
    int num_31 = 100;
    int *ptr_31 = &num_31;
    int **ptr_32 = &ptr_31;
    printf("数据: %d, 地址: %p \n", num_31, &num_31);
    printf("一级指针数据: %d, 指向地址: %p, 指针地址: %p \n", *ptr_31, ptr_31, &ptr_31);
    printf("二级指针数据: %d, 指向地址: %p, 指针地址: %p \n", **ptr_32, ptr_32, &ptr_32);

    /* 指针作为函数参数 */
    int num_41 = 41;
    int num_42 = 42;
    printf("交换前， num_41: %d; num_42: %d \n", num_41, num_42);
    swap(&num_41, &num_42);
    printf("交换前， num_41: %d; num_42: %d \n", num_41, num_42);

    /* 函数返回指针 */
    int *ptr_51;
    ptr_51 = create_arr();
    for (int i = 0; i < 5; i++)
    {
        printf("第 %d 个元素, 元素的值为: %d\n", i, *ptr_51);
        ptr_51++;
    }

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

// 数据交换，使用指针参数
void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

// 返回 static 修饰的指针
int *create_arr()
{
    static int arr[5];
    arr[0] = 11;
    arr[1] = 12;
    arr[2] = 13;
    arr[4] = 15;
    return arr;
}
