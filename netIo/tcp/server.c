#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<netinet/in.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>


int main(int argc, char* argv[])
{
    if( argc != 3 ){
        printf("Usage: ./server/client ip port\n");
        return 1;
    }
    int listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    struct sockaddr_in client_addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_port = htons(atoi(argv[2]));

    if (bind(listen_sock, (struct sockaddr*)&addr, sizeof(addr)) < 0){
        printf("%d, :%s",errno, strerror(errno) );
        close(listen_sock);
        return 2;
    }  
    if (listen(listen_sock, 10) < 0){
        printf("%d, :%s",errno, strerror(errno) );
        close(listen_sock);
        return 3;
    }
    
    for(; ; ){
        socklen_t len = 0;
        int new_sock = accept(listen_sock, (struct sockaddr*)&client_addr,&len );
        if(new_sock < 0){
            printf("%d, :%s",errno, strerror(errno) );
            close(listen_sock);
            return 4;
        }
        char buf_ip[30] = {'\0'};
        inet_ntop(AF_INET, &client_addr.sin_addr, buf_ip, sizeof(buf_ip));
        printf("client ip:%s , port :%d\n", buf_ip, ntohs(client_addr.sin_port));

        char buf_recv[1024] = {'\0'};
        char buf_send[1024] = {'\0'};
        while(1){
            recv(new_sock, buf_recv, sizeof(buf_recv) - 1, 0);
            printf("client: %s\n", buf_recv);
            memset(buf_recv,'\0',sizeof(buf_recv));
            read(0, buf_send, sizeof(buf_send) - 1);
            send(new_sock, buf_send, strlen(buf_send) - 1, 0);
            memset(buf_send,'\0',sizeof(buf_send));
        }
    }
    close(listen_sock);
    return 0;
}

