/*************************************************************************
	> File Name: pro_con.c
	> Author:没有缘分的主角
	> Mail:暂无
	> Created Time: 2017年02月22日 星期三 08时39分27秒
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
sem_t blanks; //格子
sem_t datas;//数据
#define SIZE 100
int ringBuf[SIZE];
void* productRun(void* arg)
{
	int i = 0;
	while(1)
	{
	//	sleep(1);
	 sem_wait(&blanks);  //生产者关心空格子数目 wait类似于P操作	
	 int data = rand()%1000;
		ringBuf[i]=data;
		printf("I am producter:%d\n",data);
		i++;
		i%=SIZE;
	 sem_post(&datas); //将数据添加进去，所以数据的个数增加 post类似于v操作
	}
}
void* consumerRun(void* arg)
{
 int i = 0;
while(1)
 {
	//sleep(1);
	sem_wait(&datas); //消费者关心数据数目
	int data= ringBuf[i];
	printf("i am consumer :%d\n",data);
	i++;
	i%=SIZE;
	sem_post(&blanks);
 }
 
}
int main()
{
	sem_init(&blanks,0,SIZE);//初始化格子数目为SIZE个
	sem_init(&datas,0,0);//初始化数据个数为0个
	
	pthread_t product,consumer;
	pthread_create(&product,NULL,productRun,NULL);
	pthread_create(&consumer,NULL,consumerRun,NULL);

    pthread_join(product,NULL);
	pthread_join(consumer,NULL);
    sem_destroy(&blanks);
	sem_destroy(&datas);
	return 0;	
}
