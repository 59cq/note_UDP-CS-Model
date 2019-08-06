#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>

typedef struct sockaddr* SP;

int main(){

    printf("1.创建socket.....\n");
    int sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if(0 > sockfd){
        perror("socket");
        return -1;
    }
    printf("2.准备地址...\n");
    struct sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(6655);//your VPS port
    addr.sin_addr.s_addr = inet_addr("your VPS private IP");
    socklen_t len = sizeof(addr);
    printf("3.绑定socket与地址...\n");
    if(bind(sockfd,(SP)&addr,len)){
        perror("bind");
        return -1;
    }
    struct sockaddr_in addrcli = {};
    char buf[1024] = {};
    while(1){
        printf("4.接收请求...\n");
        int ret = recvfrom(sockfd,buf,sizeof(buf),0,(SP)&addrcli,&len);
        printf("recv:%s ip:%s port:%hu size:%d\n",buf,inet_ntoa(addrcli.sin_addr),ntohs(addrcli.sin_port),ret);
        if(0 == strcmp("quit",buf)){
            printf("通信结束\n");
            break;
        }
        printf("5.响应请求...\n");
        sendto(sockfd,buf,strlen(buf)+1,0,(SP)&addrcli,len);
    }
        printf("6.关闭socket...\n");
    close(sockfd);
}