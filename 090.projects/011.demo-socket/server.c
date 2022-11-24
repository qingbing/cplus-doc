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