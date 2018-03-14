#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>

//udp
int main(int argc, char* argv[]) { 
    if(argc != 3){ 
        printf("./server  ip port\n"); 
        return 1; 
    } 

    int sock = socket(AF_INET, SOCK_DGRAM, 0); 
    if(sock < 0){ 
        perror("socket"); 
        return 2;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_port = htons(atoi(argv[2]));
    
    int ret = bind(sock, (struct sockaddr*)&addr, sizeof(addr));
    if(ret < 0){
        perror("bind");
        return 3;
    }

    while(1){
        struct sockaddr_in client_addr;
        socklen_t addrlen = sizeof(client_addr);
        char buf[1024] = {'\0'};
        ssize_t read_size = recvfrom(sock, buf, sizeof(buf)-1,0, (struct sockaddr*)&client_addr, &addrlen);
        if(read_size < 0){
            perror("recvfrom");
            continue;
        }
        buf[read_size] = '\0';
        printf("[%s:%d] %s\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), buf);
        char buf_send[1024] = {'\0'};
        ssize_t send_size = read(0, buf_send, sizeof(buf) - 1);
        buf_send[send_size] = '\0';
        sendto(sock, buf_send, strlen(buf_send) - 1, 0, (struct sockaddr*)&client_addr, addrlen);
    }
    return 0;
}
