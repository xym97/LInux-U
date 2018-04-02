#include<stdio.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>


typedef struct FdSet{
    fd_set set;
    int max_fd;
}FdSet;

void FdSetinit(FdSet* fds){
    FD_ZERO(&fds->set);
    fds->max_fd = 0;
}

void FdSetAdd(FdSet* fds, int fd){
    FD_SET(fd, &fds->set);
    if(fd > fds->max_fd){
        fds->max_fd = fd;
    }
}

void FdSetDel(FdSet* fds, int fd){
    FD_CLR(fd, &fds->set);
    int i = 0;
    int max_fd = -1;
    for(; i < fds->max_fd; ++i){
        if(!FD_ISSET(i , &fds->set)){
            continue;
        }
        if(i > max_fd){
            max_fd = i;
        }
    }
    fds->max_fd = max_fd;
}

int serverinit(const char* ip, uint16_t port)
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0){
        perror("socket");
        return -1;
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);
    
    int ret = bind(fd, (struct  sockaddr*)&addr, sizeof(addr));
    if(ret < 0){
        perror("bind");
        return -2;
    }
    ret = listen(fd, 10);
    if(ret < 0){
        perror("listen");
        return -3;
    }
    return fd;
}

void ProcessRequest(int new_sock, FdSet* fds){
    char buf[1024] ={0};
    ssize_t read_size = read(new_sock, buf, sizeof(buf) - 1);
    if(read_size < 0){
        perror("read");
        return;
    }else if(read_size == 0){
        printf("read Done!\n");
        close(new_sock);
        FdSetDel(fds, new_sock);
        printf("%s\n", buf);       
    }
    buf[read_size] = '\0';
    write(new_sock, buf, sizeof(buf) - 1);
}

int main(int argc, char* argv[])
{
    if(argc != 3){
        printf("use error! ip port \n");
        return -1;
    }
    int listen_sock = serverinit(argv[1], atoi(argv[2]));
    
    
    printf("server init OK!\n");
    FdSet fds;
    FdSetinit(&fds);
    FdSetAdd(&fds, listen_sock);
    while(1){
        FdSet tmp = fds;
        int ret = select(tmp.max_fd + 1, &tmp.set, NULL, NULL, NULL);
        if(ret < 0){
            perror("select");
            continue;
        }
        if(FD_ISSET(listen_sock, &tmp.set)){
            struct sockaddr_in peer;
            socklen_t len = sizeof(peer);
            int new_sock = accept(listen_sock, (struct sockaddr*)&peer, &len);
            if(new_sock < 0){
                perror("accept");
                continue;
            }
            FdSetAdd(&fds, new_sock);
            printf("client %s, %d connect! new_sock=%d\n", inet_ntoa(peer.sin_addr), ntohs(peer.sin_port)\
                   ,new_sock);
        }else{
            int i = 0; 
            for(; i <= tmp.max_fd; ++i){
                if(!FD_ISSET(i, &tmp.set)){
                    continue;
                }
                ProcessRequest(i, &fds);
            }
        }
    }
}


