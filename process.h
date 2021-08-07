/*************************************************************************
	> File Name: process.h
	> Author: GZY
 ************************************************************************/

#ifndef _PROCESS_H
#define _PROCESS_H

#include<unistd.h>
#include<stdio.h>
#include<sys/param.h>
#include<rpc/types.h>
#include<getopt.h>
#include<cstring>
#include<string>
#include<time.h>
#include<signal.h>
#include<algorithm>
#include <atomic>
#define METHOD_GET 0 //get请求的宏
#define METHOD_HEAD 1 //head请求的宏
#define PROGRAM_VERSION "1.0" //版本类型
#define MAXHOSTSIZE 256 //host最长256
#define MAXREQUESTSIZE 1024 //请求包最长1024
#define MAXPORT 65535//max port
#define MAXPTHREAD 100 //最多创建100线程
using namespace std;
using std::string;

class TTTHREAD
{
    /*本线程运行内部的相关信息*/
public:
    int speed; // 成功次数
    int fail; // 失败次数
    int bytes; // 接收到的字节数
    TTTHREAD(int &s,int& f,int &b){
        speed = s;
        fail = f;
        bytes = b;
    }
};

class PROCESS
{
public:
    volatile int timerecpired;
    atomic_int allspeed;//可支持的访问数量
    atomic_int allfailed;//失败次数
    atomic_int allbytes;//传输比特
    int httpv;//http版本
    int method ;//请求方法
    int clients ;//线程个数
    int force;//是否强制返回
    int force_reload;//强制返回消息
    string proxyhost;//代理的host
    int proxyport;//代理的端口
    int benchtime;//倒计时
    string host;//host最大
    string request;//request最大
public:
    bool bench();//压力测试
    void benchcore(TTTHREAD& t);//压力测试核心
    void build_request(char*);//创建http请求包
    void usage(void);//使用说明函数
public:

    PROCESS();//构造函数
    int start(int argc,char*argv[]);//启动压力测试
};


void childToProcess(PROCESS &process, TTTHREAD &th);
int mysocket(string ip,int port);

#endif
