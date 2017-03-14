/*************************************************************************
	> File Name: mySem.h
	> Author:没有缘分的主角
	> Mail:暂无
	> Created Time: Fri 17 Feb 2017 02:40:08 PM CST
 ************************************************************************/
#ifndef _SEM_H_
#define _SEM_H_
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/sem.h>
#include<sys/ipc.h>
#define PATHNAME "."
#define PROJID 0x66666
union semun{	
	int val;//使用的值
	struct semid_ds*buf; //IPC_STAT，IPC_SET使用的缓冲区
	unsigned short *array;//GETALL，SETALL使用的缓冲区
    struct seminfo *_buf;//IPC_INFO（linux特有）使用缓冲区
};
int CreatSem(int nsems);//nsems指创建信号量集合中信号量的个数
int InitSem(int semid);
int GetSemID();
int P(int semid,int which); //这个which指第几个信号量
int V (int semid,int which);
int DestorySem(int semid);
#endif
