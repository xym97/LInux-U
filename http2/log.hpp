#pragma once

#include<sys/time.h>

enum Loglevel{
    INFO, WARNING, ERROR, CRITIAL
};

class TimeUtil{
public:
    static int64_t TimeStamp(){
        struct timeval tv;
        gettimeofday(&tv, NULL);
        return tv.tv_sec;
    }
    
    static int64_t TimeStampUS(){
        struct timeval tv;
        gettimeofday(&tv, NULL);
        return tv.tv_sec * 1000 * 1000 + tv.tv_usec;
    }
};

inline std::ostream& Log(Loglevel level, const char* file, int line){
    std::string prefix = "I";
    if(level == WARNING){
        prefix = "W";
    }
    else if(level == ERROR){
        prefix = "E";
    }
    else if(level == CRITIAL){
        prefix = "C";
    }
    std::cout << "[" << prefix << TimeUtil::TimeStamp() << " " << file << ":" << line << "]";
    return std::cout;
}

#define LOG(level) Log(level , __FILE__, __LINE__)//用宏才可以使 __FILE__  __LINE__ 表示具体使用的那一行。

























