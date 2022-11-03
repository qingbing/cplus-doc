#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// 预定义
extern void *func01();

typedef struct
{
    char name[50]; // 名称传递
    int count;     // 循环次数
    int status;    // 表示执行状态
} Params;

int main()
{
    // 定义线程标志
    pthread_t thread01;
    pthread_t thread02;

    // 创建线程1
    Params subParam1 = {"sub01", 5};
    if (0 != pthread_create(&thread01, NULL, func01, &subParam1))
    {
        printf("Create thread 01 failed!");
        return 0;
    }

    // 创建线程2
    Params subParam2 = {"sub02", 15};
    if (0 != pthread_create(&thread02, NULL, func01, &subParam2))
    {
        printf("Create thread 02 failed!");
        return 0;
    }

    // 加入
    Params mParam = {"main", 5};
    func01(&mParam);

    // 将需要等待的子线程加入等待,否则主线程执行完后直接结束了
    // 不需要返回值
    if (0 != pthread_join(thread01, NULL))
    {
        printf("Join thread 01 failed!");
    }

    void *subBack1;
    Params *subBack2 = (Params *)malloc(sizeof(Params)); // 返回之需要先分配下内存
    if (0 != pthread_join(thread02, (void **)&subBack2))
    {
        printf("Join thread 02 failed!");
    }

    printf("thread02 excecute status: %d\n", subBack2->status);
    return 0;
}

void *func01(void *vPtr)
{
    Params *ptr = (Params *)vPtr;
    for (int i = 0; i < ptr->count; i++)
    {
        if (i > 10)
        {
            ptr->status = 100;
            pthread_exit(vPtr);
        }
        usleep(10000);
        printf("func01: %d, name: %s, pthread_self: %lu\n", i, ptr->name, pthread_self());
    }
}
