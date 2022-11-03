# c语言中字符串的使用

- 参考链接
  - https://blog.csdn.net/weixin_42645653/article/details/115176722

## 1. 字符串的表示

- 字符串以空字符 ('\0' ) 结束 (即空开始位置读取,直到发现 '\0' 后, 字符串才算结束)
  - 空字符(Null Character)又称结束符，缩写 (NUL)
  - 因为空字符的存在，所以，字符串占用的空间长度比实际的字符串长度大 1
- 针对字符数组,一次性初始化赋值会直接在最后加上 '\0', 采用数组方式赋值需要手动加 '\0'
- 只初始化部分数组元素，那么剩余的数组元素会自动初始化为 "零" 值,如："char str[30] = {0}", 将所有元素都初始化为 0，或者说 '\0'

## 2. 字符串的初始化和打印

```c
#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    // 数组形式
    char ch_01[] = {'H', 'e', 'l', 'l', 'o', '\0'};
    char ch_02[6] = {'H', 'e', 'l', 'l', 'o', '\0'};
    char ch_03[] = "Hello";
    char ch_04[6] = "Hello";
    char ch_05[] = {"Hello"};
    char ch_06[6] = {"Hello"};
    int len_01 = strlen(ch_01);
    printf("ch_01: %s, len: %d\n", ch_01, len_01);
    int len_02 = strlen(ch_02);
    printf("ch_02: %s, len: %d\n", ch_02, len_02);
    int len_03 = strlen(ch_03);
    printf("ch_03: %s, len: %d\n", ch_03, len_03);
    int len_04 = strlen(ch_04);
    printf("ch_04: %s, len: %d\n", ch_04, len_04);
    int len_05 = strlen(ch_05);
    printf("ch_05: %s, len: %d\n", ch_05, len_05);
    int len_06 = strlen(ch_06);
    printf("ch_06: %s, len: %d\n", ch_06, len_06);

    // 指针形式
    char *ch_07 = "Hello";
    int len_07 = strlen(ch_07);
    printf("ch_07: %s, len: %d\n", ch_07, len_07);
    return 0;
}
```

## 3. 字符串函数

- strcpy(s1, s2):  复制字符串 s2 到字符串 s1, 如果 s1 有值将会清空
- strcat(s1, s2):  连接字符串 s2 到字符串 s1 的末尾
- strlen(s1):  返回字符串 s1 的长度
- strcmp(s1, s2):  字符串对比，相同返回0,s1 < s2 返回 -1,反之返回 1
- strchr(s1, ch):  返回一个指针，指向字符串 s1 中字符 ch 的第一次出现的位置
- strstr(s1, s2):  返回一个指针，指向字符串 s1 中字符串 s2 的第一次出现的位置

## 4. 函数和指针使用 demo

```c
#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char *ch_07 = "Hello";
    int len_07 = strlen(ch_07);
    printf("ch_07: %s, len: %d\n", ch_07, len_07);

    /**
     * 定义赋值
     *    定义时可以一次性赋值
     *    定以后要在修改就只能使用数组索引的方式
     */
    char str01[] = "Hello world!";
    char str02[20] = {"hello World!"};
    char str03[5];
    char str04[30] = {0}; // 全部赋值为 0

    // 数组索引赋值
    str03[0] = 'a';
    str03[1] = 'b';
    str03[2] = 'c';
    str03[3] = 'e';
    str03[4] = '\0'; // 最后一个字符必须是 '\0' 结束符号,否则找不到结束符,读取时会向后面的内存继续读取
    int len;
    len = strlen(str01);
    printf("str01: %s, len: %d, p: %p\n", str01, len, str01);
    len = strlen(str02);
    printf("str02: %s, len: %d, p: %p\n", str02, len, str02);
    len = strlen(str03);
    printf("str03: %s, len: %d, p: %p\n", str03, len, str03);
    len = strlen(str04);
    printf("str04: %s, len: %d, p: %p\n", str04, len, str04); // str04: , len: 0, p: 0x7ffe2d6b7c90

    // 字符串函数，需要 stirng.h 的支持
    char str_1[10] = "Hello";
    char str_11[50] = "i just test";
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
    return 0;
}
```
