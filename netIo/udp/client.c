#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>

int main(int argc, char* argv[])
{
    if(argc != 3){
        printf("ip + port\n");
        return 3;
    }
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0){
        perror("socket");
        return 1;
    }
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    server_addr.sin_port = htons(atoi(argv[2]));

    while(1){
        char buf[1024] = {'\0'};
        printf(">");
        fflush(stdout);
        ssize_t read_size = read(0, buf, sizeof(buf) - 1);
        if(read_size < 0){
            perror("read");
            return 2;
        }
        buf[read_size] = '\0';
        ssize_t write_size = sendto(sock, buf,strlen(buf) - 1, 0,\
                            (struct sockaddr*)&server_addr, sizeof(server_addr));
        char buf_recv[1024] = {'\0'} ;
        socklen_t server_addrlen = sizeof(server_addr);
        read_size = recvfrom(sock, buf_recv,sizeof(buf_recv) - 1 , 0 ,\
                             (struct sockaddr*)&server_addr, &server_addrlen);
        if(read_size < 0){
            perror("recvfrom");
            return 5;
        }
        printf("server:%s\n", buf_recv);
    }
}



