#include"http_server.h"


using namespace http_server;

int main(){
    HttpServer server;
    int ret = server.Start("0", 9000);
    std::cout<< ret << std::endl;
}
