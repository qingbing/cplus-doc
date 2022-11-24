
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
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
    // 命令参数不是 2 个,直接返回命令操作提示
    if (2 != argc)
    {
        readme();
        return -1;
    }
    // 确保额外参数为1或2
    int sendMode = atoi(argv[1]);
    printf("参数: %d\n", sendMode);
    if (1 != sendMode && 2 != sendMode)
    {
        readme();
        return -1;
    }

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    assert(sockfd != -1);

    struct sockaddr_in *servAddr;
    servAddr = socketIpAddress("127.0.0.1", 6000);

    if (1 == sendMode)
    {
        autoSend(sockfd, servAddr);// 自动发送数据包
    }
    else
    {
        manualSend(sockfd, servAddr);// 手动发送数据包
    }
    close(sockfd);
}

// 工具介绍
void readme()
{
    printf("========== 使用说明 START ==========\n");
    printf("该程序是一个 UDP 协议的客户端\n");
    printf("运行时需要一个额外的参数\n");
    printf("  额外参数说明，只支持两种:\n");
    printf("    1: 自动发送内容\n");
    printf("    2: 手动输入发送内容\n");
    printf("========== 使用说明 END   ==========\n");
}

// 数据自动发送
void autoSend(int sockfd, struct sockaddr_in *servAddr)
{
    int count = 0;
    int len = sizeof(*servAddr);
    while (1)
    {
        count++;
        char buff[128];
        sprintf(buff, "第 %d 次发送", count);
        // 向服务端发送数据
        sendto(sockfd, buff, strlen(buff), 0, (struct sockaddr *)servAddr, len);
        memset(buff, 0, 128);

        // 接受服务端的响应
        recvfrom(sockfd, buff, 127, 0, (struct sockaddr *)servAddr, &len);
        printf("响应数据: %s\n", buff);
        usleep(1000000);
    }
}

// 手动发送数据
void manualSend(int sockfd, struct sockaddr_in *servAddr)
{
    int len = sizeof(*servAddr);
    while (1)
    {
        char buff[128] = {0};
        printf("input:\n");
        fgets(buff, 128, stdin);
        if (strncmp(buff, "end", 3) == 0)
        {
            break;
        }
        // 向服务端发送数据
        sendto(sockfd, buff, strlen(buff), 0, (struct sockaddr *)servAddr, len);
        memset(buff, 0, 128);

        // 接受服务端的响应
        recvfrom(sockfd, buff, 127, 0, (struct sockaddr *)servAddr, &len);
        printf("响应数据: %s\n", buff);
    }
}
