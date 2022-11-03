//服务器端
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
 
#define N 128
 
#define ERRLOG(errmsg) do{\
                perror(errmsg);\
                printf("%s--%s(%d)\n", __FILE__, __func__, __LINE__);\
                exit(-1);\
            }while(0)
 
int main(int argc, const char *argv[]){
    if(3 != argc){
        printf("Usage : %s <ip> <port>\n", argv[0]);
        exit(-1);
    }
    //1.创建用户数据报式套接字
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(-1 == sockfd){
        ERRLOG("socket error");
    }
 
    //创建服务器网络信息结构体
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
  
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    socklen_t addrlen = sizeof(server_addr);
 
    //3.将套接字和网络信息结构体进行绑定
    if(-1 == bind(sockfd, (struct sockaddr *)&server_addr, addrlen)){
        ERRLOG("bind error");
    }
 
 
    //定义一个结构体，保存客户端的信息
    struct sockaddr_in client_addr;
    memset(&server_addr, 0, sizeof(client_addr));//清空
    socklen_t clientaddrlen = sizeof(client_addr);
 
    char buff[N] = {0};
 
    while(1){
        //接收数据，如果想要给对方回应，就必须保存对方的网络信息结构体
        //如果不回应，后两个参数写 NULL 也行
        if(-1 == recvfrom(sockfd, buff, N, 0, (struct sockaddr *)&client_addr, &clientaddrlen)){
            ERRLOG("recvfrom error");
        }
        printf("%s(%d):%s\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), buff);
        //组装应答信息
        strcat(buff, "--server");
        if(-1 == sendto(sockfd, buff, N, 0, (struct sockaddr *)&client_addr, clientaddrlen)){
            ERRLOG("sendto error");
        }
        memset(buff, 0, N);
    }
    
    //关闭套接字
    close(sockfd);
 
    return 0;
}