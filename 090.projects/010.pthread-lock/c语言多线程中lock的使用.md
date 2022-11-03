# c 语言多线程中 lock 的使用

- 参考链接
  - https://blog.csdn.net/m0_47170940/article/details/123844896

## 1. 描述

### 1.1 为什么要使用锁

多线程中通过内存地址取值，当操作的共享资源(eg: 全局变量)，如果某个线程的操作完数据，但还没有放回内存时就失去了 CPU, 那么其他线程操作这个共享数据的时候，使用的就还是原来的值，从而数据就发生了混乱。

### 1.2 解决方法

在操作共享数据的时候，使用互斥锁。互斥锁的作用就是用来防止多个线程同时访问共享数据。

- 互斥锁
  - 只用两种状态: lock 和 unlock
  - 特性
    - 原子性: 把一个互斥量锁定为一个原子操作，保证了如果一个线程锁定了一个互斥量，没有其他线程在同一时间可以成功锁定这个互斥量
    - 唯一性: 如果一个线程锁定了一个互斥量，在它解除锁定之前，没有其他线程可以锁定这个互斥量
    - 非繁忙等待: 如果一个线程已经锁定了一个互斥量，第二个线程又试图去锁定这个互斥量，则第二个线程将被挂起（不占用任何cpu资源），直到第一个线程解除对这个互斥量的锁定为止，第二个线程则被唤醒并继续执行，同时锁定这个互斥量

## 2. 进程锁函数

- pthread_mutex_init
  - 原型: int pthread_mutex_init(pthread_mutex_t *mutex,const pthread_mutexattr_t *attr)
  - 功能: 初始化一个互斥锁
- pthread_mutex_lock
  - 原型: int pthread_mutex_lock(pthread_mutex_t *mutex)
  - 功能: 对互斥锁进行 lock，如果对已经上锁的资源进行调用，调用者会一直处于阻塞状态
- pthread_mutex_unlock
  - 原型: int pthread_mutex_unlock(pthread_mutex_t *mutex)
  - 功能: 有lock就有它与lock对应，对互斥锁进行unlock
- pthread_mutex_destroy
  - 原型: int pthread_mutex_destroy(pthread_mutex_t *mutex)
  - 功能: 锁用完后需要释放资源
- pthread_mutex_trylock
  - 原型: int pthread_mutex_trylock(pthread_mutex_t *mutex)
  - 功能: 调用该函数时，若互斥锁未加锁，则上锁，返回 0，如果互斥锁已加锁，则函数直接返回失败 EBUSY

## 2. demo

### 2.1 无锁时数据混乱示例

```c
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
```

### 2.2 互斥锁解决数据混乱

```output
... 几乎每次结束都不一样
thread02: 1999988
thread02: 1999989
thread02: 1999990
thread02: 1999991
thread02: 1999992
thread02: 1999993
thread02: 1999994
thread02: 1999995
thread02: 1999996
thread02: 1999997
Main end: 1999998

```

```c
#include <stdio.h>
#include <pthread.h>

extern void *print();

int global_num = 0;
pthread_mutex_t thread_lock; // 定义全局锁变量

int main()
{
    // 定义线程标志
    pthread_t thread01;
    pthread_t thread02;
    // 创建锁
    pthread_mutex_init(&thread_lock, NULL);

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

    pthread_mutex_destroy(&thread_lock); // 销毁锁

    printf("Main end: %d\n", global_num); // 在没加锁的情况下，每次结果有出入
    return 0;
}

void *print(void *ptr)
{
    char *ch = (char *)ptr;
    pthread_mutex_lock(&thread_lock);
    for (int i = 0; i < 1000000; i++)
    {
        printf("%s: %d\n", ch, global_num++);
    }
    pthread_mutex_unlock(&thread_lock);
}
```
