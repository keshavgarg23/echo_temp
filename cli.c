#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>


#define err(x,val) if(x<0){printf("%s error!\n",val);exit(0);}

int main(){
    struct sockaddr_in c;
    char msg[100];
    int sock = socket(AF_INET,SOCK_STREAM,0);
    
    err(sock,"socket");

    c.sin_family = AF_INET;
    c.sin_port = htons(22000);
    c.sin_addr.s_addr = inet_addr("103.240.233.206");

    err(connect(sock,(struct sockaddr*)&c,sizeof(c)),"connection");
    printf("Connected!\n");
    while(1){
        memset(msg,0,sizeof(msg));
        fgets(msg,sizeof(msg),stdin);
        send(sock,msg,strlen(msg),0);
        memset(msg,0,sizeof(msg));
        recv(sock,msg,sizeof(msg),0);
        printf("\tReceived:%s",msg);
    }

    return 0;
}