/*************************************************************************
	> File Name: Pthread.c
	> Author:没有缘分的主角
	> Mail:暂无
	> Created Time: 2017年02月18日 星期六 21时29分07秒
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<sys/types.h>
#include<unistd.h>
void CleanPthread(void*arg)
{
	printf("I am in CleanPthread..\n");
	printf("tid:%lu,cleaning...\n",pthread_self());
}
void* Func(void*arg)
{
	int count=3;
	pthread_cleanup_push(CleanPthread,NULL);
	while(count--)
	{
		printf("I am new thead...,tid:%lu,pid:%d\n",pthread_self(),getpid());
		sleep(1);
	}
	sleep(3);
	pthread_cleanup_pop(0);
	printf("The End..\n");
	//return (void*) 0;
}
int main()
{

	pthread_t tid =0;
	int *status=0;
	int ret=pthread_create(&tid,NULL,Func,(void*)&status);
	if(ret<0)
	{
		perror("pthread_create error\n");
		return -1;
	}
	int count = 4;
	while(count--)
	{
		printf("I am main pthread,tid:%lu,pid:%d\n",pthread_self(),getpid());
		sleep(2);
	}
	//pthread_cancel(tid);//线程终止
	void*r_val;
	ret=pthread_join(tid,&r_val);//线程等待
    printf("PTHREAD_CANCELED:%d\n",PTHREAD_CANCELED);
  	printf("ret code:%d,ret=%d\n",(long)r_val,ret);
	return 0;

}
