//UDP_Client
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
int main() {
    // 1.创建一个通信的socket, 注意第二个参数是：SOCK_DGRAM，数据报的协议。
    int fd = socket(PF_INET, SOCK_DGRAM, 0);
    if(fd == -1) {
        perror("socket");
        exit(-1);
    }   
    // 服务器的地址信息
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(9999);
    inet_pton(AF_INET, "127.0.0.1", &saddr.sin_addr.s_addr); // 地址为服务器的地址
    int num = 0;  
    // 3.通信
    while(1) {
        // 发送数据
        char sendBuf[128];
        sprintf(sendBuf, "hello , i am client %d \n", num++);
        sendto(fd, sendBuf, strlen(sendBuf) + 1, 0, (struct sockaddr *)&saddr, sizeof(saddr));
        // 接收数据
        int num = recvfrom(fd, sendBuf, sizeof(sendBuf), 0, NULL, NULL); // 服务端默认是通过saddr回数据，默认NULL即可。
        printf("server say : %s\n", sendBuf);
        sleep(1);
    }
    close(fd);
    return 0;
}