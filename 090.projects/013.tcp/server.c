#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/**
 * 封装一个获取 socket 地址的函数
 */
struct sockaddr_in *socketIpAddress(const char *ip, uint16_t port)
{
    // 使用 malloc 分配内容
    struct sockaddr_in *ipAddr = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
    ipAddr->sin_family = AF_INET;
    ipAddr->sin_port = htons(port);
    ipAddr->sin_addr.s_addr = inet_addr(ip);
    return ipAddr;
}

int main()
{
    //创建用于监听的套接字，这个套接字是一个文件描述符，用于检测有没有客户端发起一个新的连接
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(listenfd != -1);

    struct sockaddr_in *servAddr = socketIpAddress("127.0.0.1", 6000);
    // 将得到的监听的文件描述符和本地的IP端口进行绑定
    int res = bind(listenfd, (struct sockaddr *)servAddr, sizeof(*servAddr));
    assert(res != -1);

    // 设置监听(成功之后开始监听，监听的是客户端的连接)
    res = listen(listenfd, 5);
    assert(res != -1);

    int counter = 0;
    // 定义接收到客户的 socket 地址
    struct sockaddr_in *clientAddr = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
    socklen_t clientAddrLen = sizeof(struct sockaddr_in);

    while (1)
    {
        counter++;
        // 接收到客户端请求
        int c = accept(listenfd, (struct sockaddr *)clientAddr, &clientAddrLen);
        if (c == -1)
        {
            printf("Get One Client Link Error\n");
            continue;
        }

        while (1)
        {
            char buff[128] = {0};
            printf("buff: %s\n", buff);
            int n = recv(c, buff, 127, 0); //读取数据放在buff中，一次读取127个
            if (n <= 0)
            {
                printf("Client will unlink\n");
                break;
            }
            printf("第 %d 次接受 accept(%d) 数据: (%s)\n", counter, c, buff);

            char rep[200];
            sprintf(rep, "响应: %s", buff);
            send(c, rep, strlen(rep), 0);
        }
        close(c);
    }

    //断开连接，关闭套接字（四次挥手）
    close(listenfd);
    return 0;
}
