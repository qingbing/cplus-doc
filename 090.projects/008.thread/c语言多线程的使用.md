# c 语言多线程的使用

- 参考链接
  - https://blog.csdn.net/baidu_35692628/article/details/69487525


==pthread 库不是 Linux 系统默认的库，连接时需要使用静态库 libpthread.a，所以在使用pthread_create()创建线程，以及调用 pthread_atfork()函数建立fork处理程序时，需要链接该库` -lpthread`==

```shell
gcc thread.c -o thread -lpthread
```

## 1. 描述

### 1.1 进程和线程

- 什么时进程？

进程指的是一个正在执行的应用程序。

- 什么时线程？

线程的功能是执行应用程序中的某个具体的任务，比如一段程序，一个函数。

- 进程和线程的联系
  - 每个进程执行前，操作系统都会为其分配所需的资源，包括要执行的程序代码、数据、内存空间等。一个进程至少包含1个线程，可以包含多个线程，所有线程共享进程的资源，各个线程也可以拥有属于自己的私有资源
  - 进程仅负责为各个线程提供所需的资源，真正执行任务的是线程，而不是进程
  - 多线程，即一个进程中拥有多个（>=2）线程，线程之间相互协作，共同执行一个应用程序

### 1.2 线程使用

- 需要加入头文件: &lt;pthread.h&gt;
- 编译时

## 2. 线程中结构

### 2.1 pthread_t 结构体

```c
// 由 restrict 修饰的指针是最初唯一对指针所指向的对象进行存取的方法，仅当第二个指针基于第一个时，才能对对象进行存取
// pthread_t 原型, 打印时要使用%lu或%u方式
typedef unsigned long int pthread_t
```

## 3. 线程操作函数

### 3.1 线程创建函数

```c
// 原型
int pthread_create (pthread_t *restrict tidp, const pthread_attr_t *restrict attr, void *(*start_rtn)(void), void *restrict arg)

说明：创建一个具有指定参数的线程。

形参：
    tidp       要创建的线程的线程id指针
    attr       创建线程时的线程属性
    start_rtn  返回值是void类型的指针函数
    arg        start_rtn的形参

返回值：若是成功建立线程返回 0 ,否则返回错误的编号
```

### 3.2 等待线程结束函数

```c
// 原型
int pthread_join (pthread_t thread, void **retval)

说明：这个函数是一个线程阻塞的函数，调用它的函数将一直等待到被等待的线程结束为止，当函数返回时，被等待线程的资源被收回

形参：
    thread     被等待的线程标识符
    retval     一个用户定义的指针，它可以用来存储被等待线程的返回值

返回值：成功返回0,否则返回错误的编号
```

### 3.3 线程退出函数

```c
// 原型
void pthread_exit (void *retval)

说明：终止调用它的线程并返回一个指向某个对象的指针

形参：
    retval     函数的返回指针，只要 pthread_join 中的第二个参数 retval 不是NULL，这个值将被传递给 retval

返回值：无
```

### 3.4 线程取消函数

```c
// 原型
int pthread_cancel (pthread_t thread)

说明：取消某个线程的执行

形参：
    thread     要取消线程的标识符ID

返回值：若是成功返回0,否则返回错误的编号

其他说明：一个线程能够被取消并终止执行需要满足两个条件 (1) 线程是否可以被取消，默认可以被取消；(2) 线程处于可取消点才能取消，可以设置线程为立即取消或只能在取消点被取消。
```

### 3.5 设置可取消状态函数

```c
// 原型
int pthread_setcancelstate (int state, int *oldstate);

说明：设置当前线程的可取消性状态

形参：
	state     要更新的心状态值
	oldstate  原来存储的状态

state的合法值：
	PTHREAD_CANCEL_DISABLE  针对目标线程的取消请求将处于未决状态，请求未处理但仍然存在，除非该线程修改自己的状态，否则不会被取消
	PTHREAD_CANCEL_ENABLE   针对目标线程的取消请求将被传递，此状态为创建线程时的默认状态

返回值：成功返回0，否则返回错误编号以指明错误
```

### 3.6 设置取消类型函数

```c
// 原型
int pthread_setcanceltype (int type, int *oldtype);

说明：设置当前线程的取消类型，即设置在接收到取消操作后是立即终止还是在取消点终止

形参：
	type     为调用线程新的可取消性
	oldtype  存储原来的类型

type的合法值如下：
	PTHREAD_CANCEL_ASYNCHRONOUS  可随时执行新的或未决的取消请求
	PTHREAD_CANCEL_DEFERRED      目标线程到达一个取消点之前，取消请求将一直处于未决状态；此类型为创建线程时的默认类型
	
返回值：成功返回0，否则返回错误编号以指明错误
```

### 3.7 获取当前线程ID函数

```c
// 原型
pthread_t pthread_self (void);

说明：获取当前调用线程的 thread identifier(标识号)
形参：无
返回值：当前线程的线程ID标识
```

### 3.8 分离释放线程函数

```c
// 原型
int pthread_detach (pthread_t thread);

说明：线程资源释放方式设置函数

形参：
	thread     要释放线程的标识符ID

返回值：若是成功返回0,否则返回错误的编号
```

- 其他说明: 
  - linux线程执行和windows不同，pthread有两种状态joinable状态和unjoinable状态。
  - 一个线程默认的状态是joinable，如果线程是joinable状态，当线程函数自己返回退出时或pthread_exit时都不会释放线程所占用堆栈和线程描述符（总计8K多），只有当你调用了pthread_join之后这些资源才会被释放。
  - 若是unjoinable状态的线程，这些资源在线程函数退出时或pthread_exit时自动会被释放。
  - unjoinable属性可以在pthread_create时指定，或在线程创建后在线程中pthread_detach自己设置， 如：pthread_detach(pthread_self())，将状态改为unjoinable状态，确保资源的释放。如果线程状态为joinable，需要在之后适时调用pthread_join。

### 3.9 比较两个线程是否是同一线程

```c
// 原型
int pthread_equal (pthread_t thread1, pthread_t thread2);

说明：判断两个线程ID是否是同一个

形参：
	thread1     要比较的线程的标识符ID1
	thread2     要比较的线程的标识符ID2

返回值：不相等返回0，相等非零
```

### 3.10 线程私有数据操作函数

### 3.10.1 创建线程私有数据

```c
// 原型
int pthread_key_create (pthread_key_t *key, void (*destr_function) (void *));

说明：创建线程私有数据TSD，提供线程私有的全局变量。使用同名而不同内存地址的线程私有数据结构

形参：
	key       线程私有数据
	第二个参数  如果第二个参数不为空，在线程退出时将以key所关联数据为参数调用其指向的资源释放函数，以释放分配的缓冲区
```

- 其他说明
  - 不论哪个线程调用 pthread_key_create() 函数，所创建的 key 都是所有线程可访问的，但各个线程可根据自己的需要往 key 中填入不同的值
  - 相当于提供了同名不同值的全局变量,各线程对自己私有数据操作互相不影响


### 3.10.2 注销线程私有数据

```c
// 原型
int pthread_key_delete (pthread_key_t *key);

该函数并不检查当前是否有线程正是用该TSD，也不会调用清理函数(destr_function)
将TSD释放以供下一次调用pthread_key_create()使用
```

### 3.10.3 读写线程私有数据

```c
// 原型
// 写
int pthread_setspecific (pthread_key_t key, const void *pointer);
// 读
void pthread_getspecific (pthread_key_t key);
```

- 函数 pthread_setspecific() 将 pointer 的值(非内容)与key相关联
- 函数 pthread_getspecific() 将与 key 相关联的数据读出来
- 所有数据都设置为void *，因此可以指向任何类型的数据

## 4. 线程属性函数

线程的属性对象是不透明的，不能通过赋值直接进行修改。系统提供了一组函数，用于初始化、配置和销毁线程属性

### 4.1 初始化一个线程对象的属性

```c
// 原型
int pthread_attr_init (pthread_attr_t *attr);

说明：pthread_attr_init实现时为属性对象分配了动态内存空间
	 Posix线程中的线程属性pthread_attr_t主要包括scope属性、detach属性、堆栈地址、堆栈大小、优先级
形参：
	attr       指向一个线程属性的指针
	
返回值：若是成功返回0,否则返回错误的编号
```

### 4.2 销毁一个线程属性对象

```c
// 原型
int pthread_attr_destroy (pthread_attr_t *attr);

说明：经pthread_attr_destroy去除初始化之后的pthread_attr_t结构被pthread_create函数调用，将会导致其返回错误

形参：
	attr       指向一个线程属性的指针

返回值：若是成功返回0,否则返回错误的编号
```

### 4.3 获取线程分离状态属性

```c
// 原型
int pthread_attr_getdetachstate (pthread_attr_t *attr, int *detachstate);

说明：获取线程分离状态属性；pthread_detach()分离释放线程资源函数

形参：
	attr          指向一个线程属性的指针
    detachstate   保存返回的分离状态属性

返回值：若是成功返回0,否则返回错误的编号
```

### 4.4 修改线程分离状态属性

```c
// 原型
int pthread_attr_setdetachstate (pthread_attr_t *attr, int detachstate);

说明：修改线程分离状态属性；pthread_detach()分离释放线程资源函数

形参：
	attr         指向一个线程属性的指针
    detachstate  有两个取值
PTHREAD_CREATE_JOINABLE（可连接），使用attr创建的所有线程处于可连接状态，线程终止不会回收相关资源，需在其他线程调用pthread_detach()或pthread_join()函数
PTHREAD_CREATE_DETACHED(分离)，使用attr创建的所有线程处于分离状态，这类线程终止带有此状态的线程相关资源将被系统收回

返回值：若是成功返回0,否则返回错误的编号
```

### 4.5 获取线程间的CPU亲缘性

```c
// 原型
int pthread_attr_getaffinity_np (pthread_attr_t *attr, size_t cpusetsize, cpu_set_t *cpuset);

说明：获取线程的CPU亲缘属性

形参：
	attr         指向一个线程属性的指针
    cpusetsize   指向CPU组的缓冲区大小
    cpuset       指向CPU组的指针

返回值：若是成功返回0,否则返回错误的编号
```

### 4.6 设置线程的CPU亲缘性

```c
// 原型
int pthread_attr_setaffinity_np (pthread_attr_t *attr, size_t cpusetsize, const cpu_set_t *cpuset);

说明：通过指定cupset来设置线程的CPU亲缘性

形参：
	attr         指向一个线程属性的指针
    cpusetsize   指向CPU组的缓冲区大小
    cpuset       指向CPU组的指针

返回值：若是成功返回0,否则返回错误的编号
```

### 4.7 获取线程的作用域

```c
// 原型
int pthread_attr_getscope (pthread_attr_t *attr, int *scope);

说明：指定了作用域也就指定了线程与谁竞争资源

形参：
	attr       指向一个线程属性的指针
    scope      返回线程的作用域

返回值：若是成功返回0,否则返回错误的编号
```

### 4.8 设置线程的作用域

```c
// 原型
int pthread_attr_setscope (pthread_attr_t *attr, int scope);

说明：指定了作用域也就指定了线程与谁竞争资源

形参：
	attr       指向一个线程属性的指针
    scope      线程的作用域，可以取如下值
PTHREAD_SCOPE_SYSTEM  与系统中所有进程中线程竞争
PTHREAD_SCOPE_PROCESS 与当前进程中的其他线程竞争

返回值：若是成功返回0,否则返回错误的编号
```

### 4.9 获取线程的栈保护区大小

```c
// 原型
int pthread_attr_getguardsize (pthread_attr_t *attr, size_t *guardsize);

说明：获取线程的栈保护区大小

形参：
	attr       指向一个线程属性的指针
    guardsize  返回获取的栈保护区大小

返回值：若是成功返回0,否则返回错误的编号
```

### 4.10 设置线程的栈保护区大小

```c
// 原型
int pthread_attr_setguardsize (pthread_attr_t *attr, size_t *guardsize);

说明：参数提供了对栈指针溢出的保护。默认为系统页大小，如果设置为0表示没有保护区。
     大于0，则会为每个使用 attr 创建的线程提供大小至少为 guardsize 字节的溢出保护区

形参：
	attr       指向一个线程属性的指针
    guardsize  线程的栈保护区大小

返回值：若是成功返回0,否则返回错误的编号
```

### 4.11 获取线程的堆栈信息（栈地址和栈大小）

```c
// 原型
int pthread_attr_getstack (pthread_attr_t *attr, void **stackaddr, size_t *stacksize);

说明：获取线程的堆栈地址和大小

形参：
	attr       指向一个线程属性的指针
    stackaddr  返回获取的栈地址
    stacksize  返回获取的栈大小

返回值：若是成功返回0,否则返回错误的编号
```

### 4.12 设置线程的堆栈区

```c
// 原型
int pthread_attr_setstack (pthread_attr_t *attr, void *stackaddr, size_t stacksize);

说明：设置堆栈区，将导致pthread_attr_setguardsize失效

形参：
	attr       指向一个线程属性的指针
    stackaddr  线程的堆栈地址：应该是可移植的，对齐页边距的，可以用posix_memalign来进行获取
    stacksize  线程的堆栈大小：应该是页大小的整数倍

返回值：若是成功返回0,否则返回错误的编号
```

### 4.13 获取线程堆栈地址

```c
// 原型
int pthread_attr_getstackaddr (pthread_attr_t *attr, void **stackaddr);

说明：函数已过时，一般用pthread_attr_getstack来代替

形参：
	attr       指向一个线程属性的指针
    stackaddr  返回获取的栈地址

返回值：若是成功返回0,否则返回错误的编号
```

### 4.14 设置线程堆栈地址

```c
// 原型
int pthread_attr_setstackaddr (pthread_attr_t *attr, void *stackaddr);

说明：函数已过时，一般用pthread_attr_setstack来代替

形参：
	attr       指向一个线程属性的指针
    stackaddr  设置线程堆栈地址

返回值：若是成功返回0,否则返回错误的编号
```

### 4.15 获取线程堆栈大小

```c
// 原型
int pthread_attr_getstacksize (pthread_attr_t *attr, size_t *stacksize);

说明：获取线程堆栈大小

形参：
	attr       指向一个线程属性的指针
    stacksize  返回线程的堆栈大小

返回值：若是成功返回0,否则返回错误的编号
```

### 4.16 设置线程堆栈大小

```c
// 原型
int pthread_attr_setstacksize (pthread_attr_t *attr, size_t stacksize);

说明：设置线程堆栈大小

形参：
	attr       指向一个线程属性的指针
    stacksize  设置线程的堆栈大小,stack属性的合法值包括
    PTHREAD_STACK_MIN 该线程的用户栈大小将使用默认堆栈大小，为某个线程所需最小堆栈大小，但对于所有线程，这个大小可能无法接受
    具体指定的大小       使用线程的用户堆栈大小的数值，必须不小于最小堆栈大小PTHREAD_STACK_MIN

返回值：若是成功返回0,否则返回错误的编号
```

### 4.17 获取线程的调度策略

- 需要头文件: #include &lt;sched.h&gt;

```c
// 原型
int pthread_attr_getschedpolicy (pthread_attr_t *attr, int *policy);

说明：获取线程的调度策略

形参：
	attr       指向一个线程属性的指针
    policy     返回线程的调度策略

返回值：若是成功返回0,否则返回错误的编号
```

按照如下方法使用sched_get_priority_max()和sched_get_priority_min()，可以得到优先级的最大值和最小值。调用形式

```c
#include <sched.h> 
int sched_get_priority_max(int policy);  
int sched_get_priority_min(int policy); 
```

两个函数都以调度策略policy为参数，目的是获得对应调度策略的优先级值，而且都返回调度策略的最大或最小优先级值。

### 4.18 设置线程的调度策略

- 需要头文件: #include &lt;sched.h&gt;

```c
// 原型
int pthread_attr_setschedpolicy (pthread_attr_t *attr, int policy);

说明：设置线程的调度策略

形参：
	attr       指向一个线程属性的指针
    policy     线程的调度策略，posix指定了3种调度策略属性：
               SCHED_FIFO    先入先出策略
               SCHED_RR      轮转调度，类似于 FIFO，但加上了时间轮片算法
               SCHED_OTHER   系统默认策略

SCHED_OTHER是不支持优先级使用的
SCHED_FIFO和SCHED_RR支持优先级的使用，他们分别为1和99，数值越大优先级越高

返回值：若是成功返回0,否则返回错误的编号
```

### 4.19 获取线程的调度参数

- 需要头文件: #include &lt;sched.h&gt;

```c
// 原型
int pthread_attr_getschedparam (pthread_attr_t *attr, struct sched_param *param);

说明：获取线程的调度参数

形参：
	attr       指向一个线程属性的指针
    param      返回获取的调度参数
               
返回值：若是成功返回0,否则返回错误的编号
```

### 4.20 设置线程的调度参数

- 需要头文件: #include &lt;sched.h&gt;

```c
// 原型
int pthread_attr_setschedparam (pthread_attr_t *attr, const struct sched_param *param);

说明：设置线程的调度参数，用于设置优先级

形参：
	attr       指向一个线程属性的指针
    param      要设置的调度参数，sched_param结构体至少需要定义这个数据成员
		       struct sched_param 
               {
                    int sched_priority;     /* Scheduling priority */
               };
    sched_param可能还有其他的数据成员，以及多个用来返回和设置最小优先级、最大优先级、调度器、参数等的函数。
    如果调度策略是SCHED_FIFO或SCHED_RR，那么要求具有值的唯一成员是sched_priority。
               
返回值：若是成功返回0,否则返回错误的编号
```

### 4.21 获取线程是否继承调度属性

- 需要头文件: #include &lt;sched.h&gt;

```c
// 原型
int pthread_attr_getinheritsched (pthread_attr_t *attr, int *inheritsched);

说明：获取线程是否继承调度属性

形参：
	attr          指向一个线程属性的指针
    inheritsched  返回继承调度属性的设置
	
返回值：若是成功返回0,否则返回错误的编号
```

### 4.22 设置线程是否继承调度属性

- 需要头文件: #include &lt;sched.h&gt;

```c
// 原型
int pthread_attr_setinheritsched (pthread_attr_t *attr, int inheritsched);

说明：设置线程是否继承调度属性

形参：
	attr          指向一个线程属性的指针
    inheritsched  设置线程是否继承调度属性，可能取值如下
    
    PTHREAD_INHERIT_SCHED  调度属性将继承于正创建的线程。忽略在 pthread_create() 的attr定义中的调度属性设置
	PTHREAD_EXPLICIT_SCHED 调度属性将被设置为pthread_create()的attr中指定的属性值
    
返回值：若是成功返回0,否则返回错误的编号
```

## 5. 线程 demo

## 5.1 普通 demo

```c
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
```

## 5.12 线程共同求和 demo

```c
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
```
