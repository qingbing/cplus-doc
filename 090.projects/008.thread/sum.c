#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

struct Params
{
    int arr[1000];
    int start;
    int end;
    int sum;
};

// 预定义
extern void *sum();
extern int computeSum(struct Params p1);

int main()
{
    // 创建数组
    int a[1000];
    int start = 0;
    for (int i = 0; i < 1000; i++)
    {
        a[i] = i + start;
    }

    // 创建线程1
    struct Params p1;
    memcpy(p1.arr, a, sizeof(int) * 1000); // 数组从内存复制
    p1.start = 0;
    p1.end = 500;

    struct Params p2;
    memcpy(p2.arr, a, sizeof(int) * 1000); // 数组从内存复制
    p2.start = 500;
    p2.end = 1000;

    int sum1 = computeSum(p1);
    int sum2 = computeSum(p2);
    printf("sum1: %d\n", sum1);
    printf("sum2: %d\n", sum2);
    return 0;
}

void *sum(void *ptr)
{
    struct Params *aPtr = (struct Params *)ptr;
    aPtr->sum = 0;
    for (int i = aPtr->start; i < aPtr->end; i++)
    {
        aPtr->sum += aPtr->arr[i];
    }
    printf("%d\n", aPtr->sum);
    return ptr;
}

int computeSum(struct Params p1)
{
    // 定义线程标志
    pthread_t thread;

    if (pthread_create(&thread, NULL, sum, &p1))
    {
        printf("Create thread 01 failed!");
        return 0;
    }
    // 线程等待
    struct Params *subBack = (struct Params *)malloc(sizeof(struct Params)); // 返回之需要先分配下内存
    if (0 != pthread_join(thread, (void **)&subBack))
    {
        printf("Join thread failed!");
        return 0;
    }
    else
    {
        printf("Thread 01 sum: %d\n", subBack->sum);
        return subBack->sum;
    }
}