//客户端
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
    //1.创建用户数据报套接字
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(-1 == sockfd){
        ERRLOG("socket error");
    }
 
    //填充服务器网络信息结构体
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    socklen_t addrlen = sizeof(server_addr);
 
    char buff[N] = {0};
    while(1){
        printf("input your msg:");
        fgets(buff, N, stdin);
        buff[strlen(buff)-1] = '\0';//清除 \n
        if(0 == strcmp(buff, "quit")){
            break;
        }
        if(-1 == sendto(sockfd, buff, N, 0, (struct sockaddr *)&server_addr, addrlen)){
            ERRLOG("sendto error");
        }
 
        //因为客户端已经知道服务器的网络信息了 所以后两个参数可以传NULL
        if(-1 == recvfrom(sockfd, buff, N, 0, NULL, NULL)){
            ERRLOG("recvfrom error");
        }
        printf("recv:[%s]\n", buff);
        memset(buff, 0, N);
    }
    //关闭套接字
    close(sockfd);
 
    return 0;
}