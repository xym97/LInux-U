#include"httpd.h"
#include<pthread.h>


static void Usage(const char* proc)
{
    printf("Usage: %s[local ip] [local port] \n", proc);
}

int main(int argc, char* argv[])
{
    if(argc != 3){
        Usage(argv[0]);
        return 1;
    }
    int listen_sock = startup(argv[1], atoi(argv[2]));

    while(1){
        struct sockaddr_in client;
        socklen_t len = sizeof(client);
        long new_sock = accept(listen_sock, (struct sockaddr*)&client, &len);
        if(new_sock < 0){
            print_log(strerror(errno), NOTICE);
            continue;
        }
        printf("get client [%s:%d]\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

        pthread_t id;
        printf("ready to handler_req\n");
        int ret = pthread_create(&id, NULL, handler_req,(void*)new_sock);
        if(ret != 0){
            print_log(strerror(errno), WARNING);
            close(new_sock);
            continue;
        }else{
            pthread_detach(id);
        }
    }
    close(listen_sock);
    return 0;
}
