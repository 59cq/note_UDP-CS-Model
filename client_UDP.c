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
    addr.sin_port = htons(6677);
    addr.sin_addr.s_addr = inet_addr("47.97.229.46");
    socklen_t len = sizeof(addr);
    printf("3.绑定连接服务器...\n");
    if(connect(sockfd,(SP)&addr,len)){
        perror("connect");
        return -1;
    }

    struct sockaddr_in addrcli = {};
    while(1){
        char buf[1024] = {};
        printf(">");
		gets(buf);
        sendto(sockfd,buf,strlen(buf)+1,0,(SP)&addr,len);
        if(0 == strcmp("quit",buf)){
            printf("通信结束\n");
            break;
        }
        int ret = recvfrom(sockfd,buf,sizeof(buf),0,(SP)&addrcli,&len);
        printf("recv:%s ip:%s port:%hu size:%d\n",buf,inet_ntoa(addrcli.sin_addr),addrcli.sin_port,ret);
    }
    close(sockfd);

}