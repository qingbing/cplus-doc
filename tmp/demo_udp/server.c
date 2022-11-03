#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    assert(sockfd != -1);

    struct sockaddr_in saddr, caddr;
    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(6000);
    saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int res = bind(sockfd, (struct sockaddr *)&saddr, sizeof(saddr));
    assert(res != -1);

    int counter = 0;
    while (1)
    {
        counter++;
        int len = sizeof(caddr);
        char buff[128] = {0};
        recvfrom(sockfd, buff, 127, 0, (struct sockaddr *)&caddr, &len);
        printf("=== 第 %d 次接受数据 === ip: %s, port: %d \n", counter, inet_ntoa(caddr.sin_addr), ntohs(caddr.sin_port));
        printf("接受到数据: %s\n", buff);

        char rev[200];
        sprintf(rev, "receive: %s", buff);
        sendto(sockfd, rev, strlen(rev), 0, (struct sockaddr *)&caddr, sizeof(caddr));
    }

    close(sockfd);
}
