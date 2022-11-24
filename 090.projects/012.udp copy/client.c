
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

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    assert(sockfd != -1);
    struct sockaddr_in saddr;
    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(6000);
    saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (1 == sendMode)
    {
        autoSend(sockfd, saddr);
    }
    else
    {
        manualSend(sockfd, saddr);
    }

    close(sockfd);
}

void readme()
{
    printf("========== 使用说明 START ==========\n");
    printf("该程序是一个 UDP 协议的客户端\n");
    printf("运行时需要一个额外的参数\n");
    printf("  额外参数说明，之支持两种:\n");
    printf("    1: 自动发送内容\n");
    printf("    2: 手动输入发送内容\n");
    printf("========== 使用说明 END   ==========\n");
}

void autoSend(int sockfd, struct sockaddr_in saddr)
{
    int count = 0;
    while (1)
    {
        count++;
        char buff[128];
        sprintf(buff, "第 %d 次发送", count);
        sendto(sockfd, buff, strlen(buff), 0, (struct sockaddr *)&saddr, sizeof(saddr));
        memset(buff, 0, 128);

        int len = sizeof(saddr);
        recvfrom(sockfd, buff, 127, 0, (struct sockaddr *)&saddr, &len);
        printf("响应数据: %s\n", buff);
        usleep(1000000);
    }
}
void manualSend(int sockfd, struct sockaddr_in saddr)
{
    while (1)
    {
        char buff[128] = {0};
        printf("input:\n");
        fgets(buff, 128, stdin);
        if (strncmp(buff, "end", 3) == 0)
        {
            break;
        }
        sendto(sockfd, buff, strlen(buff), 0, (struct sockaddr *)&saddr, sizeof(saddr));
        memset(buff, 0, 128);

        int len = sizeof(saddr);
        recvfrom(sockfd, buff, 127, 0, (struct sockaddr *)&saddr, &len);
        printf("响应数据: %s\n", buff);
    }
}