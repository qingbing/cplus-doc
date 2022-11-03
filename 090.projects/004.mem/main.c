#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    // memchr
    printf("\n====== memchr ======\n");
    char *bug_11 = "HeelloWorld";
    int idx_11 = 5;
    char ch_11 = 'e';
    char *ptr_12 = memchr(bug_11, ch_11, idx_11);
    if (NULL != ptr_12)
    {
        printf("在 %s 的 0~%d 中找到了 %c; 找到后原字符串为: %s\n", bug_11, idx_11, ch_11, ptr_12);
    }
    else
    {
        printf("在 %s 的 0~%d 中找不到 %c\n", bug_11, idx_11, ch_11);
    }

    // memcmp
    printf("\n====== memcmp ======\n");
    char bug_21[20] = "hello1";
    char bug_22[20] = "hello2";
    char bug_23[20] = "hello2";
    char bug_24[20] = "hello3";
    printf("%s 和 %s 比较结果: %d\n", bug_21, bug_22, memcmp(bug_21, bug_22, 10));
    printf("%s 和 %s 比较结果: %d\n", bug_22, bug_23, memcmp(bug_22, bug_23, 10));
    printf("%s 和 %s 比较结果: %d\n", bug_23, bug_24, memcmp(bug_23, bug_24, 10));

    // memcpy
    printf("\n====== memcpy ======\n");
    char bug_31[20] = "This is a test!";
    char *b = "insert";
    memcpy(bug_31, b, strlen(b));
    printf("%s\n", bug_31);

    // memmove
    printf("\n====== memmove ======\n");
    int i;
    int bug_40[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    memcpy(bug_40 + 3, bug_40, 7);
    printf("== memcpy:"); // == memcpy: 1  2  3  1  2  6  7  8  9  10
    for (i = 0; i < 10; i++)
    {
        printf(" %d ", bug_40[i]);
    }
    printf("\n");

    int bug_41[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    memmove(bug_41 + 3, bug_41, 7); // == memmove: 1  2  3  1  2  6  7  8  9  10
    printf("== memmove:");
    for (i = 0; i < 10; i++)
    {
        printf(" %d ", bug_41[i]);
    }
    printf("\n");

    // memset
    printf("\n====== memset ======\n");
    char bug_51[20] = "what is csdn";
    printf("替换前: %s\n", bug_51);
    memset(bug_51, '@', 5);
    printf("替换后: %s\n", bug_51);
    return 0;
}
