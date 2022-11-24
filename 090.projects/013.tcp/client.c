#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

extern void readme();
extern void autoSend();
extern void manualSend();

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

int main(int argc, char const *argv[])
{
    // 参数判断
    if (2 != argc)
    {
        readme();
        return -1;
    }
    int sendMode = atoi(argv[1]);
    printf("参数: %d\n", sendMode);
    if (1 != sendMode && 2 != sendMode)
    {
        readme();
        return -1;
    }

    //创建一个通信的套接字，需要指定服务器的IP和端口号y
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(sockfd != -1);

    struct sockaddr_in *servAddr = socketIpAddress("127.0.0.1", 6000);

    //连接服务器，需要知道服务器绑定的IP和端口
    int res = connect(sockfd, (struct sockaddr *)servAddr, sizeof(*servAddr));
    assert(res != -1);

    //通信
    if (1 == sendMode)
    {
        autoSend(sockfd); // 自动发送
    }
    else
    {
        manualSend(sockfd); // 手动发送
    }
    //断开连接
    close(sockfd);
    return 0;
}

// 工具介绍
void readme()
{
    printf("========== 使用说明 START ==========\n");
    printf("该程序是一个 TCP 协议的客户端\n");
    printf("运行时需要一个额外的参数\n");
    printf("  额外参数说明，之支持两种:\n");
    printf("    1: 自动发送内容\n");
    printf("    2: 手动输入发送内容\n");
    printf("========== 使用说明 END   ==========\n");
}

// 数据自动发送
void autoSend(int sockfd)
{
    int count = 0;
    while (1)
    {
        count++;

        char buff[128];
        sprintf(buff, "第%d次发送", count);
        send(sockfd, buff, strlen(buff), 0); //\n不发

        memset(buff, 0, 128);
        recv(sockfd, buff, 127, 0);
        printf("响应数据: %s\n", buff);
        usleep(1000000);
    }
}

// 数据手动发送
void manualSend(int sockfd)
{
    while (1)
    {
        printf("输入发送数据: ");
        char buff[128] = {0};
        fgets(buff, 127, stdin);
        if (strncmp(buff, "end", 3) == 0)
        {
            break;
        }

        send(sockfd, buff, strlen(buff) - 1, 0); //\n不发

        memset(buff, 0, 128);
        recv(sockfd, buff, 127, 0);
        printf("响应数据: %s\n", buff);
    }
}
