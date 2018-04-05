#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/epoll.h>

//char* my_inet_ntoa(uint32_t ip){
//    uint8_t a = (ip >> 24) & 0xff;
//    uint8_t b = (ip >> 16) & 0xff;
//    uint8_t c = (ip >> 8)  & 0xff;
//    uint8_t d = (ip >> 8)  & 0xff;
//    static char buf[1024] = {0};
//    sprintf(buf, "%u, %u, %u, %u\n", a,b,c,d);
//    return buf;
//}
//
//union Ip{
//    uint32_t ip_32;
//    struct ip_8{
//        uint8_t a;
//        uint8_t b;
//        uint8_t c;
//        uint8_t d;
//    };
//};
//
//char* my_inet_ntoa(uint32_t ip){
//    uint8_t* ptr = (uint8_t*)&ip;
//    static char buf[1024] = {0};
//    sprintf("buf, %u,%u,%u,%u\n", ptr[0],ptr[1],ptr[2,ptr[3]]);
//}

int startUp(char* ip, char* port)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0){
        perror("socket");
        return 2;
    }
    int opt = 1;
    setsockopt(sock, SOL_SOCKET,SO_REUSEADDR, &opt , sizeof(opt));
    struct sockaddr_in server;
    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_port = htons(atoi(port));
    if( bind(sock, (struct sockaddr*)&server, sizeof(struct sockaddr_in)) < 0 ){
        perror("bind");
        return 3;
    }
    if( listen(sock , 10) < 0 ){
        perror("listen");
        return 4;
    }
    return sock;
}

int main(int argc, char* argv[])
{
    if(argc != 3){
        printf("Usage: ./tcp_epoll ip port\n");
        return 1;
    }
    int listen_sock = startUp(argv[1], argv[2]);
    int epfd = epoll_create(256);
    if(epfd < 0){
        perror("epoll_create");
        return 5;
    }
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = listen_sock;
    epoll_ctl(epfd, EPOLL_CTL_ADD, listen_sock, &ev);
    struct epoll_event revs[64];
    int nums = -1;
    int timeout = 5000;
    while(1){
        switch((nums = epoll_wait(epfd, revs, 64, timeout))){
            case -1: perror("epoll_wait");
            case 0 : printf("timeout\n");
            default:
                     {
                        int i = 0;
                        for(i = 0 ; i < nums; ++i){
                            //printf("%d\n", nums);
                            int fd = revs[i].data.fd;
                            if(fd == listen_sock && revs[i].events & EPOLLIN){
                                struct sockaddr_in client;
                                socklen_t len = sizeof(client);
                                int new_sock = accept(listen_sock, (struct sockaddr*)&client, &len);
                                if(new_sock < 0){
                                    perror("accept");
                                    continue;
                                }
                                printf("%s, %d", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
                                ev.events = EPOLLIN;
                                ev.data.fd = new_sock;
                                epoll_ctl(epfd, EPOLL_CTL_ADD,new_sock, &ev);
                            }
                            else if(fd != listen_sock){
                                //printf("new_sock read or write event jiuxu\n");
                                if(revs[i].events & EPOLLIN){
                                    char buf[1024];
                                    ssize_t s = read(fd, buf, sizeof(buf) - 1);
                                    if(s > 0){
                                        buf[s] = 0;
                                        printf("client say: %s\n",buf );
                                        ev.events = EPOLLOUT;
                                        ev.data.fd = fd;
                                        epoll_ctl(epfd, EPOLL_CTL_MOD, fd, &ev);
                                    }else if( s == 0 ){
                                        printf("client exit!\n");
                                        close(fd);
                                        epoll_ctl(epfd, EPOLL_CTL_DEL, fd, &ev);
                                    }else{
                                        perror("read");
                                        close(fd);
                                        epoll_ctl(epfd, EPOLL_CTL_DEL, fd, &ev);
                                    }
                                }
                                else if(revs[i].events & EPOLLOUT){
                                    char buf[1024] = {0};
                                    read(0, buf, sizeof(buf) - 1);
                                    write(fd, buf, strlen(buf) - 1);
                                    ev.events = EPOLLIN;
                                    ev.data.fd = fd;
                                    epoll_ctl(epfd, EPOLL_CTL_MOD, fd, &ev);
                                }
                            }
                        }
                     }
        }
    }
    return 0;
}












