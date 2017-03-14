
#ifndef _COMM_
#define _COMM_
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdio.h>
#include<string.h>
#define SERVER_TYPE 1
#define CLIENT_TYPE 2
#define MYSIZE 128
struct msgbuf
{
	long mytype;
	char mtext[MYSIZE];
};

int creatMsgQueue();//创建
int getMsgQueue(); //获得消息队列
int sendMessage(int msg_id,long type,const char* msg);//发消息
int recvMessage(int msg_id,int type,char out[] );//接受消息
int destroyMsgQueue(int msg_id);//销毁
#define PATHNAME "."//点指当前目录
#define PROJID  0x6666

#endif //_COMM_

