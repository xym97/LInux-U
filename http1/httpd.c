#include"httpd.h"

void print_log( char* msg, int level)
{
    const char* const level_msg[] = {
        "SUCCESS",
        "NOTICE",
        "WARNING",
        "ERROR",
        "FATAL"
    };
#ifdef _STDOUT_

    printf("[%s][%s]\n", msg, level_msg[level%5]);
        
#endif
};

int startup(const char* ip, int port)
{
    int sock = socket(AF_INET , SOCK_STREAM, 0);
    if(sock < 0){
        print_log(strerror(errno), FATAL);
        exit(2);
    }

    int op = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &op, sizeof(op));//she zhi wei duan kou fu yong

    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_addr.s_addr = inet_addr(ip);
    local.sin_port = htons(port);

    if(bind(sock, (struct sockaddr*)&local, sizeof(local)) < 0){
        print_log(strerror(errno), FATAL);
        exit(3);
    }
    if(listen(sock, 10) < 0){
        print_log(strerror(errno), FATAL);
        exit(4);
    }
    return sock;
}

static void echo_string(int sock)
{

}

static int echo_www(int sock, char* path, int size)
{
    //printf("run to echo_www\n");
    //printf("path: %s\n", path);
    int fd  = open(path, O_RDONLY);
    if(fd  < 0){
        echo_string(sock);
        print_log(strerror(errno), FATAL);
        return 8;
    }
    
    const char* echo_line="HTTP/1.0 200 OK\r\n";
    send(sock, echo_line, strlen(echo_line), 0);
    const char* null_line="\r\n";
    send(sock, null_line,2 , 0);//my frist error

    //printf("ready to sendfile\n");
    if(sendfile(sock, fd, NULL, size) < 0){
        echo_string(sock);
        //printf("sendfile faild\n");
        print_log(strerror(errno), FATAL);
        return 9;
    }

    close(fd);
    return 0;
}

//success ret > 1, line != '\0', ret == 1 & line == '\n', ret == 0&&line=='\0'
static int get_line(int sock, char line[], int size)
{
    // read 1 char, one by one
    char c = '\0';
    int num = 0;
    int len = 0;
    while( c  != '\n' && len < size-1){
        int ret = recv(sock, &c, 1 ,0);
        if(ret > 0){
        if(c == '\r'){
                //spy
                int ret = recv(sock, &c, 1 ,MSG_PEEK);
                if(ret > 0){
                    if(c == '\n'){
                        recv(sock, &c, 1, 0);
                    }else{
                        c = '\n';
                    }
                }
            }// \r->\n \r\n -> n ->\n;
            line[len++] = c;
        }else{
            c = '\n';
        }
    }
    line[len] = '\0';
    return len;
}

void drop_headler(int sock)
{
    char line[1024];
    int ret = -1;
    do{
         ret = get_line(sock, line, sizeof(line));
              
    }while(ret > 0 && strcmp(line, "\n"));
}

static int exe_cgi(int sock, char* method, char* path, char* query_str)
{
   int  content_len = -1;
   char method_env[SIZE];
   char query_str_env[SIZE];
   char content_len_env[SIZE/10];

   if(strcasecmp(method, "GET") == 0){
       drop_headler(sock);
   }else{
       char line[1024];
       int ret = -1;
       do{
           ret = get_line(sock, line, sizeof(line));
           if(ret > 0 && \
              strncasecmp(line, "Content-Length: ", 16) == 0){
               content_len = atoi(&line[16]);
           }
       }while(ret > 0 && strcmp(line,"\n"));
       if(content_len == -1){
           echo_string(sock);
           return 10;
       }
   }

    const char* echo_line="HTTP/1.0 200 OK\r\n";
    send(sock, echo_line, strlen(echo_line), 0);
    const char* type = "Content-Type;text/html;charset=ISO-8599-1\r\n";
    send(sock, type, strlen(type), 0);
    const char* null_line="\r\n";
    send(sock, null_line, 2 , 0);
   
   int input[2];
   int output[2];
   if(pipe(input) < 0 || pipe(output) < 0){
       echo_string(sock);
       return 12;
   }

   printf("query_str: %s\n", query_str);
   pid_t id = fork();
   if(id < 0){
       echo_string(sock);
       return 11;
   }else if(id == 0){
       printf("fork success\n");
       close(input[1]);
       close(output[0]);
       sprintf(method_env, "METHOD=%s", method);
       putenv(method_env);
       printf("method_end\n");
       if(strcasecmp(method, "GET") == 0){
           sprintf(query_str_env, "QUERY_ENV=%s", query_str);
           putenv(query_str_env);
           printf("query\n");
       }else{
           sprintf(content_len_env, "CONTENT_LENGTH=%d", content_len);
           putenv(content_len_env);
       }
       printf("content_len_env\n");
       dup2(input[0], 0);
       dup2(output[1], 1);

       //printf("ready to execl\n");
       //printf("path: %s\n", path);
       execl(path, path, NULL);
       printf("exec, error\n");
       exit(1);
   }else{
       close(input[0]);
       close(output[1]);
       
       int i = 0;
       char c = '\0';
       if(strcasecmp(method, "POST") == 0){
           for(; i < content_len; i++){
               recv(sock, &c, 1, 0);
               write(input[1], &c, 1);
           }
       }
       c = '\0';
       while(read(output[0], &c, 1)){
               send(sock, &c, 1, 0);
       }
    // while(1){
    //       ssize_t s = read(output[0], &c, 1);
    //       printf("---------%c\n", c);
    //       if(s > 0){
    //           send(sock, &c, 1, 0);
    //       }else{
    //           break;
    //       }
    //   }

       int ret = waitpid(id, NULL ,0);
       close(input[1]);
       close(output[0]);
   }
}

void* handler_req(void* arg)
{
    //printf("run to handler_req\n");
    long sock= (long)arg;
    char line[1024];
#ifdef _DEBUG_
    do{
        int ret = get_line(sock, line, sizeof(line));
        if(ret > 0){
            printf("%s", line);
        }else{
            printf("request........ done !\n");
            break;
        }
    }while(1);
#else
    long ret = 0;
    char buf[SIZE];
    char method[SIZE/10];
    char url[SIZE];
    int i, j;
    if(get_line(sock, buf, sizeof(buf)) <= 0){
        echo_string(sock);
        ret = 5;
        goto end;
    }
    
    i = 0;//method ->index;
    j = 0;//buf -> index;
    //GET / http/1.0
    int cgi = 0;
    char* query_str = NULL;
    char path[SIZE];
    while( !isspace(buf[j]) && i < sizeof(method) - 1  \
           && j < sizeof(buf) ){
        method[i++] = buf[j++];
    }
    method[i] = 0;
    if(strcasecmp(method, "GET") && strcasecmp(method, "POST")){
        echo_string(sock);
        ret = 6;
        goto end;
    }
    if(strcasecmp(method, "POST") == 0){
        cgi = 1;
    }
    while(isspace(buf[j]) && j < sizeof(buf))
        j++;
    i = 0;
    while(!isspace(buf[j]) && j < sizeof(buf) && i < sizeof(url) - 1){
        url[i++] = buf[j++];
    }
    url[i] = 0;
    printf("method : %s, url : %s\n", method, url);
    query_str = url;
    while(*query_str != '\0'){
        if(*query_str == '?'){
            *query_str = '\0';
            query_str++;
            cgi = 1;
            break;
        }
        query_str++;
    }
    //url leagal
    //printf("url: %s\n", url);
    //printf("path: %s\n", path);// path: wwwroot/
    if(url[strlen(path)-1]  == '/'){
        printf("%s 1\n", path);
        strcat(path, "index.html");//path=
    }
    sprintf(path, "wwwroot%s", url);
    printf("path: %s, query: %s\n", path, query_str);


    struct stat st;
    if(stat(path, &st) != 0){
        echo_string(sock);
        ret = 7;
        goto end;
    }else{
       if(S_ISDIR(st.st_mode)){//shi dir
           strcat(path, "index.html");
       }else if((st.st_mode & S_IXUSR) || \
                (st.st_mode & S_IXGRP) || \
                (st.st_mode & S_IXOTH))  {
           cgi = 1;
       }else{

       }
       printf("cgi: %d\n", cgi);

        if(cgi){
            printf("GET cgi\n");
            exe_cgi(sock, method, path, query_str);
        }else{
            drop_headler(sock);
            echo_www(sock, path, st.st_size);
        }
    }
end:
    printf("client end........\n");
    close(sock);
    return (void*)ret;
#endif
}

