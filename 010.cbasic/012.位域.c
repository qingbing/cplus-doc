#include <stdio.h>

struct
{
    unsigned int widthValidated;  // 4 字节
    unsigned int heightValidated; // 4 字节
} status1;

// 不够 32 字节， 占 32bit
struct
{
    unsigned int widthValidated : 1; // 1 bit
    unsigned int heightValidated : 1;
} status2;

// 总体超过了 32bit， 为了符合内存读取，扩充为 8字节(64bit)
struct
{
    unsigned int a1 : 29; // 29 bite
    unsigned int a2 : 3;
    unsigned int a3 : 1;
} status3;

// 示例
struct Person
{
    unsigned int sex : 2;    // 0: 未知; 1: 男; 0: 女;
    unsigned : 6;            // 空域，为了让下一成员从下一单元开始，空域会用0占位
    unsigned int age : 7;    // 从下一单元开始，7位可以最大存储 127, 这个算高龄
    unsigned : 1;            // 空域
    unsigned int height : 8; // 8位最大存储 255, 这个算高的
    char name[4];
};

int main(int argc, char const *argv[])
{
    printf("%lu\n", sizeof(unsigned int)); // 4
    printf("%lu\n", sizeof(status1));      // 8
    printf("%lu\n", sizeof(status2));      // 4
    printf("%lu\n", sizeof(status3));      // 8

    struct Person p;
    printf("%lu\n", sizeof(p)); // 4
    p.sex = 1;
    p.age = 18;
    p.height = 168;

    struct Person *ptr;
    ptr = &p;
    ptr->age = 12;
    printf("%d %d\n", ptr->age, p.age);
    return 0;
}
