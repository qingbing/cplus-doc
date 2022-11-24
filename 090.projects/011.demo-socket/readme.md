# Socket 编程整理

- 参考链接
  - https://blog.csdn.net/weixin_41857871/article/details/124476225

## 1. socket 结构体整理

### 1.1 sockaddr: 接字地址信息

```c
struct sockaddr {
    unsigned short sa_family; // 地址家族: AF_xxx
    char sa_data[14]; //协议地址(14字节): xxx.xxx.xxx.xxx
};
```

### 1.2 in_addr: Internet 地址(xxx.xxx.xxx.xxx) 转换而来数据

```c
struct in_addr {
    unsigned long s_addr; // 通过unsigned long inet_addr("xxx.xxx.xxx.xxx")转换而来
};
```

### 1.3 sockaddr_in: Internet 网络的结构体

```c
struct sockaddr_in {
    short int sin_family; // 通信类型, 通常使用 AF_INET (IPv4的网络协议套接字类型), windows 和 linux 系统相同
    unsigned short int sin_port; // 端口号。范围是 0-65535
    struct in_addr sin_addr; // Internet 地址
    unsigned char sin_zero[8]; // 用于保存sockadd数据，需要使用 memset 置零
};
```

## 2. 地址转换函数

```c
// 地址转换需要头文件
#include <arpa/inet.h>
```

### 2.1 将ip(x.x.x.x)转换成 unsigned long

```c
unsigned long inet_addr(const char* addr)

// eg:
char *sip = {"127.0.0.1"};
unsigned long longIp = inet_addr(sip);
```

### 2.2 将struct inddr 转换成 char*

```c
char *inet_ntoa(struct in_addr in)

// eg:
struct in_addr addr;
addr.s_addr = inet_addr("192.168.1.12");
char *nip = inet_ntoa(addr);
printf("ip: %s", nip);
```

## 3. socket 函数

### 3.1 创建 sokect

- 功能: 创建一个 socket，返回 socket 文件的文件描述符
- 原型: int socket(int domain, int type, int protocol)
- 参数
  - domain: 协议族,通常写AF_INET
  - type: 传输方式，字节流填 SOCK_STREAM 数据报填 SOCK_DGRAM
    - SOCK_STREAM 提供双向连续且可信赖的数据流，即 TCP ， 支持00B机制，在所有数据传送前必须使用connect。来建立连线状态
    - SOCK_DGRAM 使用不连续不可信赖的数据包连接， 即 UDP
    - SOCK_SEQPACKET 提供连续可信赖的数据包连接
    - SOCK_RAW 提供原始网络协议存取
    - SOCK_RDM 提供可信赖的数据包连接
    - SOCK_PACKET 提供和网络驱动程序直接通信
  - protocol: 使用协议，通常有 IPPROTO_TCP, IPPROTO_UDP, IPPROTO_IP
    - 用来指定 socket 所使用的传输协议编号，通常此参考不用管它，设为0即可
- 返回
  - 成功返回文件描述符
  - 失败返回 -1

```c
int fds = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
if (fds == -1) {
    return -1;
}
```

### 3.2 给 socket 文件描述符绑定 ip

- 功能: 将地址绑定到 socket 文件上
- 原型: int bind(int sockfd, struct sockaddr *my_addr, int addrlen)
- 参数
  - sockfd: socket() 得到的文件描述符
  - my_addr: 绑定地址 "struct sockaddr" 指针
  - addrlen: 地址长度，通常写sizeof(struct sockaddr)
- 返回
  - 成功返回 0
  - 失败返回 -1

```c
bind(servSock, (struct sockaddr*)&servAddr, sizeof(servAddr))
```

### 3.3 <font color="red">客户端</font>连接服务器函数 connect

- 功能: 客户端向申请服务器建立连接, 填入服务器的地址和地址长度, 建立连接
- 原型: int connect(int sockfd, struct sockaddr *servAddr, int addrlen)
- 参数
  - sockfd: socket() 得到的文件描述符
  - servAddr: 绑定地址 "struct sockaddr" 指针
  - addrlen: 地址长度，通常写sizeof(struct sockaddr)
- 返回
  - 成功返回 0
  - 失败返回 -1

```c
bind(servSock, (struct sockaddr*)&servAddr, sizeof(servAddr))
```

### 3.4 <font color="red">服务端</font>监听函数 listen

- 功能: 设置监听的端口和最大连接数目
- 原型: int listen(int sockfd, int backlog)
- 参数
  - sockfd: socket() 得到的文件描述符
  - backlog: 允许进入队列的最大连接数目,最大值为128
- 返回
  - 成功返回 0
  - 失败返回 -1

```c
listen(socketFds, 2)
```

### 3.5 <font color="red">服务端</font>等待操作 accept

- 功能: 在等待接收的时候会阻塞在这个函数上，直到有客户端连接成功或者传输数据, 返回客户端的 socket 文件描述符，并保存地址信息
- 原型: int accept(int sockfd, void *addr, int *addrlen)
- 参数
  - sockfd: 通过sokect()函数
  - addr: 接收到的客户端的 sockaddr_in 的指针
  - addrlen: 接收到的客户端的 sockeaddr_in 的长度的指针
- 返回
  - 成功返回`客户端`文件描述符
  - 失败返回 -1

```c
int clientSock = accept(servSock, (struct sockaddr*)&clientAddr, &clientAddrSize)
```

### 3.6 <font color="red">服务端</font>数据的发送 send()、write()

- 功能: 将数据发送给指定的客户端，传入客户都拿socket文件描述符，数据，数据大小
- 原型: 
  - int send(int sockfd, const void *msg, int len, int flags)
  - int write(int sockfd, const void *msg, int len)
- 参数
  - sockfd: 接收端socket文件描述符
  - *msg: 发送的数据缓冲区指针
  - len: 数据长度
- 返回
  - 成功返回 0
  - 失败返回 -1

```c
char buf[] = "hello";
if (-1 == send(fd, buf, sizeof(buf), 0)) {
    return -1;
}
if (-1 == write(fd, buf, sizeof(buf))) {
    return -1;
}
```

### 3.7 <font color="red">客户端</font>数据接收 read()、recv()

- 功能: 客户端通过读文件socket文件描述符指定的文件, 将数据放到缓存中, 并保存缓存的指针和长度, 在等待接收的时候会阻塞在这个函数中, 函数每次将长度为len的数据推到缓冲区buf中
- 原型: 
  - int read(int sockfd, const void *msg, int len, int flags)
  - int recv(int sockfd, const void *msg, int len)
- 参数
  - sockfd: 客户端通过 socket() 函数得到的文件描述符
  - msg: buf 缓存的头指针，函数会将长度为 len 数据存到这个缓存中
  - len: 一次性读取的buf的长度
- 返回
  - 成功返回 0
  - 失败返回 -1

### 3.8 <font color="red">客户端</font> UDP 的发送和接收 sendto()、recvfrom()

- 功能: UDP 客户端发送和接受数据
- 原型: 
  - int sendto(int sockfd, const void *msg, int len, unsigned int flags, const struct sockaddr *to, int tolen)
  - int recvfrom(int sockfd, void *buf, int len, unsigned int flags, struct sockaddr *from, int *fromlen)
- 参数
  - sockfd: 文件描述符
  - msg: 缓冲区的头指针
  - len: 缓冲区大小
  - flags: 通常写0就行
  - *to: 目标地址的指针
  - tolen: 目标地址结构体的大小
  - *from: 源地址的指针
  - *fromlen: 源地址结构的大小
- 返回
  - 成功返回 0
  - 失败返回 -1

### 3.9 关闭套接字 close()、shutdown()

- 功能: 关闭套接字
- 原型:
  - int close(int sockfd)
  - int shutdown(int sockfd, int how)
- 参数
  - sockfd: 文件描述符
  - how: 关闭的方式[0: 不允许接收; 1: 不允许发送; 2: 都不允许]
- 返回
  - 成功返回 0
  - 失败返回 -1

```c
//函数和头文件
#include <sys/socket.h>
int close(int sockfd);
int shutdown(int sockfd, int how);
```

### 3.10 非阻塞 fcntl()

- 功能: 将 socket 阻塞状态设置成非阻塞状态。在上面的函数中，accept()和read(),recv()都是阻塞的，但是这种阻塞状态并不适合一个高并发服务器，所以我们要将他设置成非阻塞状
- 原型: fcntl(sockfd, F_SETFL, O_NONBLOCK)
- 参数
  - sockfd: 文件描述符
- 返回
  - 成功返回文件描述符
  - 失败返回 -1
- 头文件: unistd.h, fontl.h
- 需要IO多路复用的知识

```c
//函数和头文件
#include <unistd.h>
#include <fontl.h>
 
sockfd = socket(AF_INET, SOCK_STREAM, 0);
fcntl(sockfd, F_SETFL, O_NONBLOCK);
```

## 4. demo 演示
### 4.1 服务端(SERVER)

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <assert.h>

int main()
{
    // 创建套接字，返回套接字的文件操作符
    // int servSocketFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    int servSocketFd = socket(AF_INET, SOCK_STREAM, 0);
    // 确保套接字创建成功
    assert(servSocketFd != -1);

    // 将套接字和IP、端口绑定
    struct sockaddr_in servAddr;
    // 每个字节都用0填充
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;                     // 使用IPv4地址
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // 具体的IP地址
    servAddr.sin_port = htons(1234);                   // 端口

    // 绑定端口
    if (-1 == bind(servSocketFd, (struct sockaddr *)&servAddr, sizeof(servAddr)))
    {
        // 绑定端口失败
        printf("bind error\n");
        return -1;
    }

    // 监听端口，限制最大队列为20个
    if (-1 == listen(servSocketFd, 20))
    {
        // 监听失败
        printf("listen error\n");
    }

    printf("服务器启动....\n");
    printf("ip: %s\n", inet_ntoa(servAddr.sin_addr));
    printf("服务port: %d\n", 1234);
    printf("开始监听>>>>\n");

    // 接收客户端请求
    struct sockaddr_in clientAddr; // 客户端的地址
    socklen_t clientAddrSize = sizeof(clientAddr);

    printf("阻塞在accept(),等待.....\n");
    int cliSocketFd = accept(servSocketFd, (struct sockaddr *)&clientAddr, &clientAddrSize);
    if (-1 == cliSocketFd)
    {
        printf("accept fail.");
        return -1;
    }

    // 向客户端发送数据
    char str[100] = "server";
    // write(cliSocketFd, str, sizeof(str));
    printf("发送字符: %s\n", str);
    ssize_t status = send(cliSocketFd, str, sizeof(str), 0);
    if (-1 == status)
    {
        printf("send fail.");
        return -1;
    }

    // 关闭套接字
    close(cliSocketFd);
    close(servSocketFd);
    printf("关闭套接字\n");
    return 0;
}
```

### 4.2 客户端(CLIENT)

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main()
{
    // 创建套接字
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    // 向服务器（特定的IP和端口）发起请求
    struct sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));           // 每个字节都用 0 填充
    servAddr.sin_family = AF_INET;                     // 使用IPv4地址
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // 具体的IP地址
    servAddr.sin_port = htons(1234);                   // 端口

    if (-1 == connect(sock, (struct sockaddr *)&servAddr, sizeof(servAddr)))
    {
        printf("建立连接失败\n");
        return -1;
    }
    printf("阻塞再read()，等待服务器回消息\n");
    // 读取服务器传回的数据
    char buf[100];
    // read(sock, buffer, sizeof(buffer)-1);
    recv(sock, buf, sizeof(buf), 0);
    // for (int i = 0; i < 20; i++)
    // {
    //     char buffer[2];
    //     // read(sock, buffer, sizeof(buffer)-1);
    //     recv(sock, buffer, sizeof(buffer), 0);
    //     buf[2 * i] = buffer[0];
    //     buf[2 * i + 1] = buffer[1];
    // }
    printf("客户端接收到消息:%s\n", buf);
    // 关闭套接字
    close(sock);
    return 0;
}
```

### 4.3 测试效果(TESTING)

```shell

# 1. 清理
make clean

# 2. make 生成二进制 ./server.out ./client.out
make

# 3. 先启动服务端
ghostcloud@gc:/code/capp/cplus-doc/tmp/demo-socket$ ./server.out 
服务器启动....
ip: 127.0.0.1
服务port: 1234
开始监听>>>>
阻塞在accept(),等待.....
发送字符: server
关闭套接字

# 4. 新开再启动客户端
ghostcloud@gc:/code/capp/cplus-doc/tmp/demo-socket$ ./client.out 
阻塞再read()，等待服务器回消息
客户端接收到消息:server
```
