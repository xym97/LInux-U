#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<strings.h>

void mymath(char* arg)
{
    printf("huhuhuhahaha\n");
    char* argv[3];
    int i = 0;
    char* start = arg;
    while(*start){
        if(*start == '='){
            start++;
            argv[i++] = start;
            continue;
        }
        if(*start == '&'){
            *start = '\0';
        }
        start++;
    }
    argv[i] = NULL;
    int data1 = atoi(argv[0]);
    int data2 = atoi(argv[1]);
    printf("<html><body><h1>");
    printf("%d + %d = %d\n<br>",data1, data2, data1 + data2);
    printf("%d - %d = %d\n<br>",data1, data2, data1 - data2);
    printf("%d * %d = %d\n<br>",data1, data2, data2 == 0 ? 0 : data1 * data2);
    printf("%d / %d = %d\n<br>",data1, data2, data1 / data2);
    printf("%d %% %d = %d\n<br>",data1, data2, data2 == 0 ? 0 : data1 % data2);
    printf("</h1><body></html>");
}

int main()
{
    printf("enter math_cgi\n");
    char* method = NULL;
    char* query_str = NULL;
    char* string_arg = NULL;
    int content_len = -1;
    char buf[1024];
    //method = getenv("METHOD");
    //printf("%s\n",method);
    if((method = getenv("METHOD"))){
        if(strcasecmp(method, "GET") == 0){
            if(query_str=getenv("QUERY_ENV")){
                string_arg = query_str;
            }
        }else{
            if(getenv("CONTENT_LENGTH")){
                content_len =  atoi(getenv("CONTENT_LENGTH"));
                int i = 0;
                for(; i < content_len; i++){
                    read(0, &buf[i], 1);
                }
                buf[i] = '\0';
                string_arg = buf;
            }
        }
        printf("string_arg: %s\n", string_arg);
        mymath(string_arg);
    }
    return 0;
}
