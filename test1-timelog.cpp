

#include <time.h>
#include <stdio.h>
#include <sys/time.h>

#include <chrono>


void PrintTimeStamp2(const char* fmt){

    struct timeval tv;
    gettimeofday(&tv, nullptr);

    tm* t =  localtime(&tv.tv_sec);                                                                                                                        
    printf( "[%.2d:%.2d:%.2d.%ld]: %s \n", t->tm_hour, t->tm_min, t->tm_sec, tv.tv_usec, fmt); 
}

#define PrintTimeStamp(fmt, args...)            \
{                                               \
    struct timeval tv;                          \
    gettimeofday(&tv, nullptr);                 \
    tm* t =  localtime(&tv.tv_sec);             \                                                                                                          
    printf( "[%.2d:%.2d:%.2d.%d]:" fmt, t->tm_hour, t->tm_min, t->tm_sec, static_cast<int>(tv.tv_usec*0.001f), ##args); \
} 

int main(){

    int aa = 10;
    PrintTimeStamp("%d == \n" , ++aa);
    PrintTimeStamp("%d == \n" , ++aa);
    PrintTimeStamp("%d == \n" , ++aa);
    PrintTimeStamp("%d == \n" , ++aa);
    PrintTimeStamp("%d == \n" , ++aa);
    PrintTimeStamp("%d == \n" , ++aa);
    PrintTimeStamp("%d == \n" , ++aa);
    PrintTimeStamp("%d == \n" , ++aa);
    PrintTimeStamp("222");

    return 0;
}