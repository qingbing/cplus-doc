#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>

sem_t sem_val;
pthread_t thread;
int threadNum = 0;

void instrduce()
{
    printf("****************************************\n");
    printf("** 输入进程睡眠时间: 秒(小于等于0 退出) *****\n");
    printf("****************************************\n");
}

typedef struct
{
    char name[50];
    int sec;
} param;

void *myFunc(void *ptr)
{
    // 进程中参数转化
    param *pPtr = (param *)ptr;
    sem_wait(&sem_val); // 信号量减 1
    printf("============== Task 开始 %s: %d 秒 ======= \n", pPtr->name, pPtr->sec);
    sleep(pPtr->sec);
    printf("============== Task 结束 %s ============== \n", pPtr->name);
    threadNum--;
    //等待线程结束
    pthread_join(thread, NULL);
}

int main()
{
    instrduce();

    int sec;
    int num = 0;
    // 初始化信号量
    sem_init(&sem_val, 0, 0);
    while (scanf("%d", &sec) != EOF)
    {
        if (sec > 20)
        {
            printf("等待太久了, 输入一个20以下的数吧\n");
            continue;
        }
        if (sec > 0)
        {

            threadNum++;
            num++;
            char threadName[100];
            sprintf(threadName, "Thread%d", num);
            param pa;
            strcpy(pa.name, threadName);
            pa.sec = sec;
            pthread_create(&thread, NULL, myFunc, &pa);
            sem_post(&sem_val); // 信号量加 1
            continue;
        }
        if (threadNum > 0)
        {
            // 进程执行完毕，退出循环
            printf("还有 %d 个任务没有完成\n", threadNum);
            continue;
        }
        else
        {
            // 进程执行完毕，退出循环
            printf("输入小于0退出来了\n");
            break;
        }
    }

    // 销毁信号量
    sem_destroy(&sem_val);
    return 0;
}
