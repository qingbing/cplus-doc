#include <iostream>
#include <cstring>
using namespace std;

int main(int argc, char const *argv[])
{
    char str_01[20] = "Hello";
    char str_02[20] = "World";
    // strcpy(s1, s2); 复制字符串 s2 到字符串 s1, 如果 s1 有值将会清空
    strcpy(str_01, str_02);
    cout << str_01 << endl;
    // strcat(s1, s2); 连接字符串 s2 到字符串 s1 的末尾
    strcat(str_01, "_test");
    cout << str_01 << endl;
    // strlen(s1); 返回字符串 s1 的长度
    cout << "长度: " << strlen(str_01) << endl;
    // strcmp(s1, s2); 字符串对比，相同返回0,s1 < s2 返回 -1,反之返回 1
    int num_01;
    cout << "对比: " << strcmp("hello1", "hello1") << endl;
    cout << "对比: " << strcmp("hello2", "hello1") << endl;
    cout << "对比: " << strcmp("hello1", "hello2") << endl;
    // strchr(s1, ch); 返回一个指针，指向字符串 s1 中字符 ch 的第一次出现的位置
    const char *ptr_1;
    ptr_1 = strchr("hello", 'l');
    printf("位置: %p, 值: %c\n", ptr_1, *ptr_1);
    ptr_1 = strchr("hello", 'p'); // nil
    printf("位置: %p\n", ptr_1);
    // strstr(s1, s2); 返回一个指针，指向字符串 s1 中字符串 s2 的第一次出现的位置
    ptr_1 = strstr("hello", "lo");
    printf("位置: %p, 值: %c\n", ptr_1, *ptr_1);
    ptr_1 = strstr("hello", "loo"); // nil
    printf("位置: %p\n", ptr_1);
    return 0;
}
