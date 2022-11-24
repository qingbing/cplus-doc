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
