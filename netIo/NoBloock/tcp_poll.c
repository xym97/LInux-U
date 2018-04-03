#include<stdio.h>
#include<sys/socket.h>
#include<poll.h>
#include<unistd.h>
#include<stdlib.h>


int main()
{
    struct pollfd fds;
    fds.fd = 0;
    fds.events =POLLIN;
    while(1){
        int ret = poll(&fds, 1, 0);
        if(ret < 0){
            perror("poll");
            break;
        }
        char buf[1024] = {0};
        ssize_t read_size = read(0, buf, sizeof(buf)- 1);
        if(read_size < 0){
            perror("read");
            return 1;
        }
        if(read_size == 0){
            printf("read done\n");
            return 0;
        }
        printf(": %s ", buf);
    }
    return 0;
}
