#include"http_server.h"
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

namespace http_server{

void* HttpServer::ThreadEnter(void* arg){
    Context* context = reinterpret_cast<Context*>(arg);
    //1、从文件描述符中取数据， 转换成req对象
    HttpServer* server = context->server;
    int ret = 0;
    ret = server->ReadOneRequest(context);
    if(ret < 0){
        LOG(ERROR) << "ReadOneRequest error!" << "\n";
        Process404(context);
        goto END;
    }
    ret = server->HandlerRequest(context);
    if(ret < 0){
        LOG(ERROR) << "ReadOneRequest error!" << "\n";
        Process404(context);
        goto END;
    }
END:
    server->WriteOneResponse(context);
    //2、把req对象通过业务逻辑 生成resp对象
    //3、resp序列化  发送给new_sock

    //TODO 处理失败的情况
    close(context->new_sock);//收尾工作
    delete context;
}

int HttpServer::Start(const std::string& ip, short port ){
    int listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(listen_sock < 0){
        perror("socket");
        return -1;
    }
    sockaddr_in addr;
    addr.sin_addr.s_addr = inet_addr(ip.c_str());
    addr.sin_port = htons(port);
    int ret = bind(listen_sock, (sockaddr*)&addr, sizeof(addr));
    if(ret < 0){
        perror("bind");
        return -2;
    }
    ret = listen(listen_sock, 10);
    if(ret < 0){
        perror("listen");
        return -3;
    }
    LOG(INFO) << "start OK";
    while(1){
        sockaddr_in peer;
        socklen_t len = sizeof(peer);
        int new_sock = accept(listen_sock, (sockaddr*)&peer, &len);
        if(new_sock < 0){
            perror("accept");
            continue;
        }
        //创建新线程
        Context* context = new Context();
        context->new_sock = new_sock;
        context->server = this;
        pthread_t tid;
        pthread_create(&tid, NULL,ThreadEnter ,context );
        pthread_detach(tid);

    }
    return listen_sock;
}
    
}
