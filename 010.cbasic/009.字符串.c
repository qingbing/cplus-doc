#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    // 字符串初始化
    char str_1[6] = {'h', 'e', 'l', 'l', 'o'};
    int len;
    len = strlen(str_1);
    printf("字符串: %s, 长度: %d\n", str_1, len);
    char str_2[] = {'h', 'e', 'l', 'l', 'o', '\0'};
    len = strlen(str_2);
    printf("字符串: %s, 长度: %d\n", str_2, len);
    char str_3[] = "hello";
    printf("%s\n", str_3);

    // 字符串函数，需要 stirng.h 的支持
    char str_11[50] = "ijust test";
    // strcpy(s1, s2); 复制字符串 s2 到字符串 s1, 如果 s1 有值将会清空
    strcpy(str_11, str_1);
    printf("%s\n", str_11);
    // strcat(s1, s2); 连接字符串 s2 到字符串 s1 的末尾
    strcat(str_11, "_test");
    printf("%s\n", str_11);
    // strlen(s1); 返回字符串 s1 的长度
    len = strlen(str_11);
    printf("长度: %d\n", len);
    // strcmp(s1, s2); 字符串对比，相同返回0,s1 < s2 返回 -1,反之返回 1
    int num_01;
    num_01 = strcmp("hello1", "hello1");
    printf("对比: %d\n", num_01);
    num_01 = strcmp("hello2", "hello1");
    printf("对比: %d\n", num_01);
    num_01 = strcmp("hello1", "hello3");
    printf("对比: %d\n", num_01);
    // strchr(s1, ch); 返回一个指针，指向字符串 s1 中字符 ch 的第一次出现的位置
    char *ptr_1;
    ptr_1 = strchr("hello", 'l');
    printf("位置: %p, 值: %c\n", ptr_1, *ptr_1);
    // strstr(s1, s2); 返回一个指针，指向字符串 s1 中字符串 s2 的第一次出现的位置
    ptr_1 = strstr("hello", "lo");
    printf("位置: %p, 值: %c\n", ptr_1, *ptr_1);
    return 0;
}
