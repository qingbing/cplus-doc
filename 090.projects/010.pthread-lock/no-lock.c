#include <stdio.h>
#include <pthread.h>

int global_num = 0;

extern void *print();

int main()
{
    // 定义线程标志
    pthread_t thread01;
    pthread_t thread02;

    if (pthread_create(&thread01, NULL, print, "thread01"))
    {
        printf("Create thread 01 failed!");
        return 0;
    }
    if (pthread_create(&thread02, NULL, print, "thread02"))
    {
        printf("Create thread 02 failed!");
        return 0;
    }

    // 线程等待
    if (0 != pthread_join(thread01, NULL))
    {
        printf("Join thread 01 failed!");
    }
    if (0 != pthread_join(thread02, NULL))
    {
        printf("Join thread 02 failed!");
    }

    printf("Main end: %d\n", global_num); // 在没加锁的情况下，每次结果有出入
    return 0;
}

void *print(void *ptr)
{
    char *ch = (char *)ptr;
    for (int i = 0; i < 1000000; i++)
    {
        printf("%s: %d\n", ch, global_num++);
    }
}
