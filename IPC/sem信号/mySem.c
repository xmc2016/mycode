/*************************************************************************
	> File Name: mySem.c
	> Author:没有缘分的主角
	> Mail:暂无
	> Created Time: Fri 17 Feb 2017 02:55:56 PM CST
 ************************************************************************/

#include"mySem.h"
int InitSem(int semid)
{
	union semun un;
	un.val =1;
	int ret = semctl(semid,0,SETVAL,un);//用来执行在信号量集上的控制操作
	if(ret<0)
	{
		perror("semclt error\n");
		return -1;

	}
	return 0;

}
//ftok(const char*pathname,int pro_id) 
//获得系统建立IPC通信时必须指定一个ID值
//semget(key_t key,int nsmes,int senflg);
//创建/获取一个信号量集合 key 由ftok函数获取
static int CommSem(int nsems,int flags)
{	
	key_t _k =ftok(PATHNAME,PROJID);
	if(_k<0){
		perror("ftok error\n");
		return -1;
	}
	int semid= semget(_k,nsems,flags);
	if(semid<0){
		perror("semget error\n");
		return -2;
	}                                    
	return semid;
} 
int CreateSem(int nsems)
{
	return CommSem(nsems,IPC_CREAT|IPC_EXCL|0666);
}
int GetSemID()
{
	return CommSem(0,0);
}
int SemOp(int semid,int op,int num)
{
	struct sembuf buf;
	buf.sem_op=op;// 表示该信号量的操作
	buf.sem_num=num;//sem_num 指信号量在集合中的编号
	buf.sem_flg=0;//信号操作标志
	int ret = semop(semid,&buf,1);//信号量集合操作
	if(ret<0)
	{
		perror("Semop error\n");
		return -1;
	}
	return 0;
}
int P(int semid,int which) //请求资源
{
	return SemOp(semid,-1,which);
}
int V(int semid ,int which) //释放资源
{
   return SemOp(semid,1,which);
}
int DestorySem(int semid)
{
	int ret = semctl(semid,0,IPC_RMID);
	if(ret<0)
	{
		perror("semctl error\n");
	}
	return 0;
}




