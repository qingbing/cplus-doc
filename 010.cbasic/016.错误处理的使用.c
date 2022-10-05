#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    perror("打开文件失败");                             // 打开文件失败: Success
    printf("错误代码: %d\n", errno);                    // 错误代码: 0
    fprintf(stderr, "错误描述: %s\n", strerror(errno)); // 错误描述: Success

    FILE *fp = NULL;
    fp = fopen("xxx", "r");
    if (!fp)
    {
        perror("打开文件失败");                             // 打开文件失败: No such file or directory
        printf("错误代码: %d\n", errno);                    // 错误代码: 2
        fprintf(stderr, "错误描述: %s\n", strerror(errno)); // 错误描述: No such file or directory
    }
    else
    {
        fclose(fp);
    }
    return 0;
}