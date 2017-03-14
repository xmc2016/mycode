/*************************************************************************
	> File Name: comm.h
	> Author:没有缘分的主角
	> Mail:暂无
	> Created Time: 2017年02月17日 星期五 20时14分32秒
 ************************************************************************/
#ifndef _COMM_H_
#define _COMM_H_
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<sys/wait.h>
#define PATHNAME "."
#define PROJID 0x6666
#define SIZE 4096*1  //大小为4k的整数倍
int creatshm();
int getshm();
char* atshm(int shmid);
int dtshm(const void* shmaddr);
int destroyshm(int shmid);
#endif


