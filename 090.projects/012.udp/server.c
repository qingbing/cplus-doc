#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
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
    // 创建 socket， 获取 socket 文件描述符，不成功返回 -1
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    assert(sockfd != -1);

    // 构建服务器 ip+port
    // struct sockaddr_in servAddr;
    // memset(&servAddr, 0, sizeof(servAddr));
    // servAddr.sin_family = AF_INET;
    // servAddr.sin_port = htons(6000);
    // servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    // 绑定服务器 ip+port
    // int res = bind(sockfd, (struct sockaddr *)&servAddr, sizeof(servAddr));
    // assert(res != -1);
    // 构建服务器 ip+port
    struct sockaddr_in *servAddr;
    servAddr = socketIpAddress("127.0.0.1", 6000);
    // 绑定服务器 ip+port
    int res = bind(sockfd, (struct sockaddr *)servAddr, sizeof(*servAddr));
    assert(res != -1);

    // struct sockaddr_in clientAddr;
    // int clientAddrLen = sizeof(clientAddr);
    struct sockaddr_in *clientAddr = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
    int clientAddrLen = sizeof(*clientAddr);

    int recvStatus;  // 保存接受包的状态
    int counter = 0; // 接受数据包个数
    while (1)
    {
        counter++;
        char buff[128] = {0};
        // recvfrom(sockfd, buff, 127, 0, (struct sockaddr *)&clientAddr, &clientAddrLen);
        recvStatus = recvfrom(sockfd, buff, 127, 0, (struct sockaddr *)clientAddr, &clientAddrLen);
        assert(recvStatus != -1);

        // printf("=== 第 %d 次接受数据 === ip: %s, port: %d \n", counter, inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
        printf("=== 第 %d 次接受数据 === %s:%d \n", counter, inet_ntoa(clientAddr->sin_addr), ntohs(clientAddr->sin_port));
        printf("接受到数据: %s\n", buff);

        char rev[200];
        sprintf(rev, "receive: %s", buff); // 字符串装载
        // 向客户端发送数据
        // sendto(sockfd, rev, strlen(rev), 0, (struct sockaddr *)&clientAddr, sizeof(clientAddr));
        sendto(sockfd, rev, strlen(rev), 0, (struct sockaddr *)clientAddr, clientAddrLen);
    }

    // 关闭服务器的 socket 文件描述符
    close(sockfd);
}
