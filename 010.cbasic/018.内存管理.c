#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char *description;
    // 动态分配内存
    description = (char *)malloc(20 * sizeof(char)); // 为 description 动态分配 200个 char 的内存空间
    if (NULL == description)
    {
        fprintf(stderr, "内存分配失败");
    }
    else
    {
        strcpy(description, "内容");
        fprintf(stdout, "description: %s\n", description);
    }

    // 扩大内存
    description = (char *)realloc(description, 100 * sizeof(char)); // 为 description
    if (NULL == description)
    {
        fprintf(stderr, "内存扩充失败");
    }
    else
    {
        strcat(description, "追加内容在这里呢");
        fprintf(stdout, "description: %s\n", description);
    }

    free(description); // 释放动态分配的内存空间
    return 0;
}
