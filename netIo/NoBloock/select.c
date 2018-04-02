#include<stdio.h>
#include<sys/select.h>
#include<unistd.h>
//circle read data from stdin
//after read data write stdout
int main()
{
    while(1){
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(0 , &fds);
        printf("Before select\n");
        int ret = select(1 , &fds, NULL, NULL, NULL);
        if(ret < 0){
            perror("select");
            return 1;
        }else if(ret == 0){
            printf("select time out\n");
            continue;
        }
        printf("after select\n");
        if(! FD_ISSET(0, &fds)){
            continue;
        }
        char buf[1024] = {0};
        ssize_t read_size = read(0, buf, sizeof(buf) - 1);
        if(read_size < 0){
            perror("read");
            return 1;
        }else if(read_size == 0){
            printf("read Done!\n");
            return 0;
        }
        buf[read_size] = '\0';
        printf("buf = %s\n", buf);
    }
    return 0;
}
