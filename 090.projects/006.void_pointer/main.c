#include <stdio.h>

int main(int argc, char const *argv[])
{
    // 正常定义的变量
    char *sPtr = "This is a string";
    char cArr[] = "Char array";
    int num = 5;
    int nums[5] = {1, 2};

    // 定义泛指针
    void *vPtr;
    // 泛指针 和 字符指针
    vPtr = sPtr;                // 赋值给泛指针
    char *ssPtr = (char *)vPtr; // 强制转换
    printf("%s\n", ssPtr);

    // 泛指针 和 字符数组
    vPtr = cArr;                // 赋值给泛指针
    char *ccArr = (char *)vPtr; // 强制转换
    printf("%s\n", ccArr);

    // 泛指针 和 数字
    vPtr = &num;               // 赋值给泛指针
    int *numPtr = (int *)vPtr; // 强制转换
    printf("%d\n", *numPtr);

    // 泛指针 和 数组(长度需要预先指导)
    vPtr = nums;                // 赋值给泛指针
    int *numsPtr = (int *)vPtr; // 强制转换
    for (int i = 0; i < 5; i++)
    {
        printf("I: %d\n", *numsPtr + i);
    }
    return 0;
}
