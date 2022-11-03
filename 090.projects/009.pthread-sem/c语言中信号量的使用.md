# c 语言中信号量的使用——semaphore

- 参考链接
  - https://zhuanlan.zhihu.com/p/98717838

## 1. 介绍

- 定义: 又被称为信号灯，是在多线程环境下使用的一种技术，是可以用来保证两个或多个关键代码段不被并发调用
- 目的: 类似计数器，常用在多线程同步任务上，信号量可以在当前线程某个任务完成后，通知别的线程，再进行别的任务
- 分类:
  - 二值信号量: 信号量的值只有 0 和 1 ，这和互斥量很类似，若资源被锁住，信号量的值为 0，若资源可用，则信号量的值为 1
  - 计数信号量: 信号量的值在 0 到一个大于1的限制值之间，该计数表示可用的资源的个数。

信号量在创建时需要设置一个初始值，表示同时可以有几个任务可以访问该信号量保护的共享资源，初始值为 1 就变成互斥锁Mutex，即同时只能有一个任务可以访问信号量保护的共享资源

## 2. 信号量函数

使用信号量需要导入库文件 &lt;semaphore.h&gt;

```c
// 信号量结构体
sem_t
```

### 2.1 sem_init

```c
// 原型
int sem_init(sem_t *sem, int pshared, unsigned int value)

功能: 创建信号量

参数描述:
    第一个参数: 指向的信号对象
    第二个参数: 控制信号量的类型，如果其值为 0，就表示信号量是当前进程的局部信号量，否则信号量就可以在多个进程间共享
    第三个参数: 信号量sem的初始值

返回值:
    成功为 0; 失败 为-1。
```

### 2.2 sem_post

```c
// 原型
int sem_post(sem_t *sem)

功能: 信号量的值加 1

参数描述:
    第一个参数: 信号量对象

返回值:
    成功为 0; 失败 为-1。
```

### 2.3 sem_wait

```c
// 原型
int sem_wait(sem_t *sem)

功能: 信号量的值加-1

参数描述:
    第一个参数: 信号量对象

返回值:
    成功为 0; 失败 为-1。
```

### 2.4 sem_destroy

```c
// 原型
int sem_destroy(sem_t *sem)

功能: 销毁已定义的信号量

参数描述:
    第一个参数: 信号量对象

返回值:
    成功为 0; 失败 为-1。
```

## 3 demo

```c
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
```
