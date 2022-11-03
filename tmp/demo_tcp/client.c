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

    struct sockaddr_in ser_addr;
    memset(&ser_addr, 0, sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_port = htons(6000);                   //转化端口号
    ser_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //回环地址

    //连接服务器，需要知道服务器绑定的IP和端口
    int res = connect(sockfd, (struct sockaddr *)&ser_addr, sizeof(ser_addr));
    assert(res != -1);

    //通信
    if (1 == sendMode)
    {
        autoSend(sockfd);
    }
    else
    {
        manualSend(sockfd);
    }

    //断开连接
    close(sockfd);

    return 0;
}

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

void autoSend(int sockfd)
{
    int count = 0;
    while (1)
    {
        count++;

        char buff[128];
        sprintf(buff, "第 %d 次发送", count);
        send(sockfd, buff, strlen(buff), 0); //\n不发

        memset(buff, 0, 128);
        recv(sockfd, buff, 127, 0);
        printf("响应数据: %s\n", buff);
        usleep(1000000);
    }
}
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