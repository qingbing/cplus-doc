# c 语言中 void* 的用法

- 参考链接
  - https://blog.csdn.net/ggcasfgq/article/details/124366350

## 1. void 指针及使用介绍

- void 也是一种指针
- 一般被称为通用指针或叫泛指针, 是 c 语言关于纯粹地址的一种约定, 当某个指针是 void 型指针时，所指向的对象不属于任何类型
- void* 表示一个类型未知的指针(不知道从这个指针地址开始多少字节为一个数据), 因此, void* 只能表示一个地址，不能用来 & 来取值，也不能 +±- 移动指针(不知道多少字节是一个数据单位)
- 在 c/c++ 中，在任意时刻都可以使用其它类型指针来代替 void 指针，或者用 void 指针来代替其他类型指针
- void* 的解引用
  - 对指针变量的解引用，使用间接运算符 * 达到目的
  - void* 在进行 &、移动指针之前必须转型为类型指针
  - 类型转换的时候须注意类型匹配
  - 如果函数类型可以是任意类型的指针，则需将其参数定义为void *指针, eg: void *memset(void *s, int ch, size_t n)


## 2. 简单示例

```c
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
```
