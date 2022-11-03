// UDP_Server
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main()
{
    // 1.创建一个通信的socket, 注意第二个参数是：SOCK_DGRAM，数据报的协议。
    int fd = socket(PF_INET, SOCK_DGRAM, 0);
    if (fd == -1)
    {
        perror("socket");
        exit(-1);
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9999);
    addr.sin_addr.s_addr = INADDR_ANY; // 服务器绑定本机所有的网卡
    // 2.绑定
    int ret = bind(fd, (struct sockaddr *)&addr, sizeof(addr));
    if (ret == -1)
    {
        perror("bind");
        exit(-1);
    }
    // 3.通信
    while (1)
    {
        char recvbuf[128];
        char ipbuf[16];
        struct sockaddr_in cliaddr;
        int len = sizeof(cliaddr); // 用来保存客户端的地址
        // 接收数据
        int num = recvfrom(fd, recvbuf, sizeof(recvbuf), 0, (struct sockaddr *)&cliaddr, &len);
        printf("client IP : %s, Port : %d\n",
               inet_ntop(AF_INET, &cliaddr.sin_addr.s_addr, ipbuf, sizeof(ipbuf)),
               ntohs(cliaddr.sin_port)); // ip和端口号, 从网络字节序转换成主机字节序
        // 发送数据
        sendto(fd, recvbuf, strlen(recvbuf) + 1, 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
    }
    close(fd);
    return 0;
}