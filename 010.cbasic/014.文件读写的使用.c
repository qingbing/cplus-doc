
#include <stdio.h>
#include <string.h>

extern int copy_file(char source[], char target[]);

int main(int argc, char const *argv[])
{
    // 打开文件，如果失败，返回一个空指针
    FILE *fp = NULL;
    fp = fopen("test.out", "r");
    if (fp)
    {
        printf("success");
        fclose(fp);
    }
    else
    {
        printf("fail");
    }
    printf("\n");

    // 写模式，无文件添加，有文件先清空
    fp = fopen("empty.out", "w");
    fputs("hello\n", fp);
    fclose(fp);

    // 写模式，无文件添加，有文件继续追加
    fp = fopen("append.out", "a");
    fputs("hello\n", fp);
    fclose(fp);

    int size = copy_file("source.out", "target.out");

    printf("复制成功，长度为: %d", size);
    return 0;
}

/**
 * 复制文件，并返回复制的内容的长度
 */
int copy_file(char source[], char target[])
{
    FILE *sp, *tp;
    // 打开句柄
    sp = fopen(source, "r");
    if (!sp)
    {
        printf("源文件(%s)不存在", source);
        return 0;
    }
    tp = fopen(target, "w");
    // 循环读写并写入目标文件
    char buf[255];
    unsigned int ccount = 0;
    while (fgets(buf, 255, sp))
    {
        fputs(buf, tp);
        ccount += strlen(buf);
    }

    fclose(sp);
    fclose(tp);
    return ccount;
}