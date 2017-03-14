/*************************************************************************
	> File Name: comm.c
	> Author:没有缘分的主角
	> Mail:暂无
	> Created Time: 2017年02月17日 星期五 20时16分21秒
 ************************************************************************/
//int shmget(key_t key,size_t size,int flag)
//函数功能：得到共享内存的id ，
//参数：key 由ftok函数获得 
//size表示申请共享内存的大小一般为4k的整数倍 
//flag：IPC_CREAT与IPC_EXCL 一起使用，则创建一个新的共享内存，否则返回-1
//IPC_CREAT单独使用时，返回一个共享内存，有就直接返回，没有就创建

// void*shmat(int shmid); 
//shmat的作用是将申请的共享内存挂接在该进程的页表上，使得虚拟内存和物理内存
//相对应。 
//返回值：返回这块内存的虚拟地址。
//int shmdt(const void*shmaddr); 
//shmdt将这块共享内存从页表上剥离下来。 
//返回值：失败返回-1. 
//shmaddr:表示这块物理内存的虚拟地址。

//int shmctl(int shmid,int cmd,const void* addr);
//shmctl用来设置共享内存的属性。当cmd是IPC_RMID时可以用来删除一块共享内存。
#include"comm.h"
static int commShm(int flags)//将创建一个共享内存函数封装起来
{
    key_t _k=ftok(PATHNAME,PROJID);
	if(_k ==-1)
	{
		perror("ftok error\n");
		return -1;
	}
    int shmid = shmget(_k,SIZE,flags);//得到共享内存id号
	if(shmid==-1)
	{
		perror("shmget error\n");
		return -1;
	}
	return shmid;
}
int creatshm()
{
  int shmid = commShm(IPC_CREAT |IPC_EXCL |0666);
  return shmid;
}
int getshm()
{
  int shmid = commShm(IPC_CREAT);
  return shmid;
}
char* atshm(int shmid)
{
  char* addr=shmat(shmid,NULL,0);//将申请内存挂在进程的页表上，返回该进程的
								 // 虚拟地址
   return (char*)addr;	
}
int dtshm(const void*shmaddr)
{
   return shmdt(shmaddr);//将共享内存从页表上剥离下来
}
int destroyshm(int shmid)
{
  if(shmctl(shmid,IPC_RMID,NULL)<0)
  {
	  perror("shmctl error");
	  return -1;
  }
  return 0;
}
