/*************************************************************************
	> File Name: pro_con.c
	> Author:没有缘分的主角
	> Mail:暂无
	> Created Time: 2017年02月22日 星期三 08时39分27秒
 ************************************************************************/
//多消费者多生产者
#include<stdio.h>
#include<pthread.h>
  #include <unistd.h>
#include<semaphore.h>
pthread_mutex_t mylock = PTHREAD_MUTEX_INITIALIZER;
//pthread_cond_t mycond=PTHREAD_COND_INITIALIZER;
sem_t blanks; //格子
sem_t datas;//数据
#define SIZE 100
int ringBuf[SIZE] = {0};
void* productRun(void* arg)
{
	int i = 0;
	while(1)
	{
	 usleep(100000);
	 sem_wait(&blanks);  //生产者关心空格子数目 wait类似于P操作	
	 pthread_mutex_lock(&mylock); 
	 int data = rand()%100+1;
	    while(ringBuf[i]!=0)
		{
			i++;
		}
		i%=SIZE;
		ringBuf[i]=data;
		printf("I am producter:%d ,i =%d\n",data,i);        
		i++;
		i%=SIZE;
	 sem_post(&datas); //将数据添加进去，所以数据的个数增加 post类似于v操作
	 pthread_mutex_unlock(&mylock);
	}
}
void* productRun2(void* arg)
{
	int i = 0;
	while(1)
	{
		usleep(100000);
	 sem_wait(&blanks);  //生产者关心空格子数目 wait类似于P操作	
	pthread_mutex_lock(&mylock);
	 int data = rand()%1000+101;
	    while(ringBuf[i]!=0)
		{
			i++;
		}
		i%=SIZE;
		ringBuf[i]=data;
		printf("I am producter2:%d ,i =%d\n",data,i);
		i++;
		i%=SIZE;
	 sem_post(&datas); //将数据添加进去，所以数据的个数增加 post类似于v操作
	 pthread_mutex_unlock(&mylock);
	}
}

void* consumerRun(void* arg)
{
 int i = 0;
while(1)
 {
	usleep(100000);
	sem_wait(&datas); //消费者关心数据数目
	pthread_mutex_lock(&mylock);
	while(ringBuf[i]==0)
	{
		i++;
	}
	i%=SIZE;
	int data= ringBuf[i];
	ringBuf[i]=0;
	printf("i am consumer :%d,i=%d\n",data,i);
	i++;
	i%=SIZE;
	sem_post(&blanks);
	pthread_mutex_unlock(&mylock);
 }
 
}
void* consumerRun2(void* arg)
{
 int i = 0;
while(1)
 {
	usleep(100000);
	sem_wait(&datas); //消费者关心数据数目
	pthread_mutex_lock(&mylock);
	while(ringBuf[i]==0)
	{
		i++;
	}
	i%=SIZE;
	int data= ringBuf[i];
	ringBuf[i]=0;
	printf("i am consumer2 :%d,i = %d\n",data,i);
	i++;
	i%=SIZE;
	sem_post(&blanks);
	pthread_mutex_unlock(&mylock);
 }
 
}
int main()
{
	sem_init(&blanks,0,SIZE);//初始化格子数目为SIZE个
	sem_init(&datas,0,0);//初始化数据个数为0个
	
	pthread_t product,consumer;
   pthread_t product2,consumer2;
	pthread_create(&product,NULL,productRun,NULL);
	pthread_create(&consumer,NULL,consumerRun,NULL);
	pthread_create(&product2,NULL,productRun2,NULL);
    pthread_create(&consumer2,NULL,consumerRun2,NULL);
	pthread_join(product,NULL);
	pthread_join(consumer,NULL);
	pthread_join(product2,NULL);
	pthread_join(consumer2,NULL);
	pthread_mutex_destroy(&mylock);
	//pthread_cond_destroy(&mycond);
	sem_destroy(&blanks);
	sem_destroy(&datas);
	return 0;	
}
