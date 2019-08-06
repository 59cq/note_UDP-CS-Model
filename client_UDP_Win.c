#include <stdio.h>
#include <winsock2.h>

int main()
{
    WSADATA wsadata;
    if(WSAStartup(MAKEWORD(1,2),&wsadata))
    {
        perror("WSAStartup");
        return -1;
    }

    printf("create socket...\n");
    SOCKET sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if(0 > sockfd)
    {
        perror("socket");
        return -1;
    }

    printf("prepare address...\n");
    struct sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(6655);
    addr.sin_addr.s_addr = inet_addr("120.55.165.233");
    int len = sizeof(addr);
    char buf[1024] = {};

    printf("start communication...\n");
    for(;;)
    {
        printf(">");
        gets(buf);
        sendto(sockfd,buf,strlen(buf)+1,0,(struct sockaddr*)&addr,len);
        if(0 == strcmp("quit",buf))
        {
            printf("stop communication!\n");
            break;
        }
        recvfrom(sockfd,buf,sizeof(buf),0,(struct sockaddr*)&addr,&len);
        printf("recv:%s\n",buf);
    }

    closesocket(sockfd);
    WSACleanup();
}













