#pragma once
#include<iostream>
#include<string>
#include<unordered_map>
#include"log.hpp"

namespace http_server{

typedef std::unordered_map<std::string, std::string>  Header;

struct Request{
    std::string method;
    std::string url;
    std::string url_path;
    std::string query_string;
    Header header;//头部信息

    std::string body;

};

struct Response{
    int code;//状态码。
    std::string desc;//状态吗描述。
    Header header;
    
    std::string body;
};

//当前请求的上下文 包含了这次请求所有需要的中间数据。
//方便进行扩展、整个处理请求的过程中、 每一个环节都能够拿到。
//所有和这次请求相关的数据。//这样设计是为了程序的维护性
class HttpServer;

struct Context{
    Request req;
    Response resp;
    int new_sock;
    HttpServer* server;
};

class HttpServer{
public:
    //一下几个函数返回0 表示成功  小于0  表示失败。
    int Start(const std::string& ip, short port);
    int ReadOneRequest(Context* cont);//从sock中读取字符串  反序列化出请求的对象
    int WriteOneResponse(Context* cont);//把要相应的对象给序列化成字符串，  写到sock中
    int HandlerRequest(Context* cont);//根据Request 对象  构造 Response对象

    static void* ThreadEnter(void* arg);
    int Process(Context* cont);
};

}



















