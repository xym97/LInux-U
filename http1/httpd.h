#ifndef _HPPTD_
#define _HPPTD_

#include<stdio.h>
#include<stdlib.h>
#include <ctype.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/sendfile.h>
#include<sys/wait.h>

#define SUCCESS 0
#define NOTICE 1
#define WARNING 2
#define ERROR 3
#define FATAL 4
#define SIZE 1024

int startup(const char* ip, int port);
void* handler_req(void* arg);
void print_log(char* msg, int level);

#endif
