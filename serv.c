#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>


#define err(x,val) if(x<0){printf("%s error!\n",val);exit(0);}

int main(){
    struct sockaddr_in b;
    struct sockaddr_in c;
    int len = sizeof(c);
    char msg[100];
    int sock = socket(AF_INET,SOCK_STREAM,0);
    err(sock,"socket");

    b.sin_addr.s_addr = INADDR_ANY;
    b.sin_family = AF_INET;
    b.sin_port = htons(22000);

    err(bind(sock,(struct sockaddr*)&b,sizeof(b)),"bind");

    err(listen(sock,10),"listen");

    printf("Server Start!\n");

    int conn = accept(sock,(struct sockaddr*)&c,&len);
    err(conn,"conn");

    printf("Connected!\n");
    while(1){
        memset(&msg,0,sizeof(msg));
        recv(conn,&msg,sizeof(msg),0);
        printf("Received:%s",msg);
        send(conn,&msg,strlen(msg),0);
    }
    return 0;
}