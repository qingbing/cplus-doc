#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

int main(int argc, char const *argv[])
{
    // ip 地址转换
    char *sip = {"127.0.0.1"};
    unsigned long longIp = inet_addr(sip);
    printf("ip: %ld", longIp);


    struct in_addr addr;
    addr.s_addr = inet_addr("192.168.1.12");
    char *nip = inet_ntoa(addr);
    printf("ip: %s", nip);
    return 0;
}
