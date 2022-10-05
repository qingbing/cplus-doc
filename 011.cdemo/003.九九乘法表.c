#include <stdio.h>

void multiplication_table()
{
    printf("九九乘法表：、\n\n");
    for (int i = 1; i <= 9; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            printf("%d*%d=%-2d ", i, j, i * j);
        }
        printf("\n");
    }
}

int main(int argc, char const *argv[])
{
    multiplication_table();
    return 0;
}
