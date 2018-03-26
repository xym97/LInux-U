#pragma once
#include<mysql.h>
#include<iostream>
#include<string>


class sqlApi{
public:
    sqlApi(const std::string &_h,const int& _port,\
               const std::string &_u="root",const std::string &_p=""\
               ,const std::string &_db="http");
    int connect();
    ~sqlApi();
    int insert(const std::string& _name, const std::string& _sex,\
           const std::string& _age, const std::string& _hobby, const std::string& _school);
    int select();
private:
    MYSQL *conn;
    MYSQL_RES* res;
    std::string host;
    std::string user;
    std::string passwd;
    std::string db;
    int port;
};
