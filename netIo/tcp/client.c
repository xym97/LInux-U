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
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    server_addr.sin_port = htons(atoi(argv[2]));
    
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        printf("%d, :%s",errno, strerror(errno) );
        close(sock);
        return 2;
    }
    char buf_recv[1024] = {'\0'};
    char buf_send[1024] = {'\0'};
    while(1){
        read(0 , buf_send, sizeof(buf_send) - 1);
        send(sock, buf_send, strlen(buf_send) - 1, 0);
        memset(buf_send, '\0', sizeof(buf_send));
        recv(sock, buf_recv, sizeof(buf_recv) - 1, 0);
        printf("server: %s\n", buf_recv);
        memset(buf_recv, '\0', sizeof(buf_recv));
    }
    close(sock);
    return 0;
}

