
#include <stdio.h>

int main(int argc, char const *argv[])
{
    // 单字符控制
    // printf("输入一个字符: ");
    // int c = getchar(); // 从标准输入获取 一个 字符，并返回成整数
    // printf("\n");
    // printf("输入的是: %d, 字符是: ", c);
    // putchar(c);
    // printf("\n");

    // 行控制
    /*
    char str[100];
    printf("输入一行字符串: ");
    gets(str); // 该函数被认为不安全的，危险级别，建议使用 fgets 替代
    printf("\n");
    printf("输入字符串是: ");
    puts(str);
    printf("\n");
    */
    char str1[100];
    printf("输入一行字符串");
    fgets(str1, 100, stdin);
    printf("输入字符串是: ");
    fputs(str1, stdout);

    // 格式化控制:： scanf 输入； printf 输出
    char name[10];
    unsigned int age;
    enum SEX
    {
        UNKNOWN,
        FEMALE,
        MALE
    };
    enum SEX sex;
    printf("请输入姓名: ");
    scanf("%s", name);
    printf("\n");
    printf("请输入年龄(正整数)和性别(0,1,2)，用\",\"分割: ");
    scanf("%d,%u", &age, &sex);
    printf("\n");
    printf("您输入的信息如下：\n姓名: %s, 年龄: %d, 性别: %u\n", name, age, sex);
    return 0;
}
