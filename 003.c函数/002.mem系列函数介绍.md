# c 语言中 mem 系列函数

- 参考链接
  - https://www.jb51.net/article/237433.htm

## 1. 特点

- mem系列函数是针对内存进行操作，操作的基本单位是字节，与类型无关
- 头文件均为&lt;string.h&gt;

## 2. 函数

### 2.1 memchr: 字符串查找

- 原型: void *memchr(const void *str, int c, size_t n)
- 功能: 在 str 的前 n 个字符串总进行寻找
  - 返回结果
    - 如果成功找到，返回一个指向该字符位置的指针
    - 如果没有没有找到指定字符，则返回NULL

### 2.2 memcmp: 比较两个 buf 内容的大小

- 原型: int memcmp( const void *buf1, const void *buf2, size_t count )
- 功能: 比较 buf1 和 buf2 的前 count 个字节, 与strcmp()类似, 不过该函数是逐个比较的内存中的字节对应的ASCII码
- 返回值:
  - 如果返回值 < 0，则表示 buf1 小于 buf2
  - 如果返回值 > 0，则表示 buf2 小于 buf1
  - 如果返回值 = 0，则表示 buf1 等于 buf2

```c
// 模拟实现 memcmp
int my_memcmp(const void* buf1,const void *buf2,size_t count)
{
    assert(buf1 && buf2);
    while ((count--) && !(*(((char*)buf1)++) - *(((char*)buf2)++)));
    return *(--(char*)buf1) - *(--(char*)buf2);//这里要 -- 是因为上面的最后还++了一下
}
```

### 2.3 memcpy: 复制 src 的 count 个字符到 dest 的开始位置

- 原型: void *memcpy( void *dest, const void *src, size_t count )
- 功能
  - 该函数将 src 的 count 个字节复制到 dest 并返回 dest 的起始位置的指针
  - 与strcpy相比，memcpy并不是遇到'\0'就结束，而是一定会拷贝完n个字节

```c
// 模拟实现 memcpy
void* my_memcpy(void* a, const void* b, size_t count)
{
	assert(a && b);
	void* ret = a;
	while (count--)
	{
		*(char*)a = *(char*)b;
		a = (char*)a + 1;
		b = (char*)b + 1;
	}
	return ret;
}
```

### 2.4 memmove: 复制 src 的 count 个字符到 dest 的开始位置

- 原型: void *memmove( void *dest, const void *src, size_t count )
- 功能: 
  - 和 memcpy 功能类似
  - 介绍说 memmove 函数在操作同一块内存时能确保正确性，实验好像不可以，和 memcpy 一样，记住只要是操作同一块内存用 memmove 就是了

```c
// 模拟实现 memmove
void* my_memmove(void* a,const void* b,size_t count) //a:dest b:source
{
	assert(a && b);
	void* ret = a;
	//s<d 从右往左
	if (b < a)
	{
		a = (char*)a + count - 1;
		b = (char*)b + count - 1;
		while (count--)
		{
			*(char*)a = *(char*)b;
			a = (char*)a - 1;
			b = (char*)b - 1;
		}
	}
	else
	{
		while (count--)
		{
			*(char*)a = *(char*)b;
			a = (char*)a + 1;
			b = (char*)b + 1;
		}
	}
	return ret;
}
```


### 2.5 memset: 初始化内存的前 count 个字节

- 原型: void *memset( void *dest, int c, size_t count );
- 功能: 将 dest 的前 count 个字节用字符 c 替换并返回s
- 使用注意:
  - 赋值不管你数组是什么类型的，它都是以字节为单位赋值的(即使是int型，4个字节，也是逐个字节赋值)
  - 一般常用于一段数据的初始化(就是可以初始化一块内存为具体值)

```c
// 模拟实现 memchr
void* my_memchr(const char* str,int c,size_t n)
{
    assert(str != NULL);
    while ((n--) && (*(str++) - c));
    if (!(*str - c))
        return NULL;
    return str;
}
```



### 2.2 简单使用

```c
#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    // memchr
    printf("\n====== memchr ======\n");
    char *bug_11 = "HeelloWorld";
    int idx_11 = 5;
    char ch_11 = 'e';
    char *ptr_12 = memchr(bug_11, ch_11, idx_11);
    if (NULL != ptr_12)
    {
        printf("在 %s 的 0~%d 中找到了 %c; 找到后原字符串为: %s\n", bug_11, idx_11, ch_11, ptr_12);
    }
    else
    {
        printf("在 %s 的 0~%d 中找不到 %c\n", bug_11, idx_11, ch_11);
    }

    // memcmp
    printf("\n====== memcmp ======\n");
    char bug_21[20] = "hello1";
    char bug_22[20] = "hello2";
    char bug_23[20] = "hello2";
    char bug_24[20] = "hello3";
    printf("%s 和 %s 比较结果: %d\n", bug_21, bug_22, memcmp(bug_21, bug_22, 10));
    printf("%s 和 %s 比较结果: %d\n", bug_22, bug_23, memcmp(bug_22, bug_23, 10));
    printf("%s 和 %s 比较结果: %d\n", bug_23, bug_24, memcmp(bug_23, bug_24, 10));

    // memcpy
    printf("\n====== memcpy ======\n");
    char bug_31[20] = "This is a test!";
    char *b = "insert";
    memcpy(bug_31, b, strlen(b));
    printf("%s\n", bug_31);

    // memmove
    printf("\n====== memmove ======\n");
    int i;
    int bug_40[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    memcpy(bug_40 + 3, bug_40, 7);
    printf("== memcpy:"); // == memcpy: 1  2  3  1  2  6  7  8  9  10
    for (i = 0; i < 10; i++)
    {
        printf(" %d ", bug_40[i]);
    }
    printf("\n");

    int bug_41[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    memmove(bug_41 + 3, bug_41, 7); // == memmove: 1  2  3  1  2  6  7  8  9  10
    printf("== memmove:");
    for (i = 0; i < 10; i++)
    {
        printf(" %d ", bug_41[i]);
    }
    printf("\n");

    // memset
    printf("\n====== memset ======\n");
    char bug_51[20] = "what is csdn";
    printf("替换前: %s\n", bug_51);
    memset(bug_51, '@', 5);
    printf("替换后: %s\n", bug_51);
    return 0;
}
```
