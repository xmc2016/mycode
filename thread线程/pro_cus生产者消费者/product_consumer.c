/*************************************************************************
	> File Name: test.c
	> Author:没有缘分的主角
	> Mail:暂无
	> Created Time: 2017年02月20日 星期一 14时15分02秒
 ************************************************************************/
#include<pthread.h>
#include"LinkList.h"
pthread_mutex_t mylock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t mycond=PTHREAD_COND_INITIALIZER;
void test()
{

	node_p head;
	Init(&head);
	int i = 0;

	printf("head:%d\n",head->data);
	while(i<10)
	{
	 usleep(1000);
		Push_front(head,i);
	    Display(head);
		i++;
	}
    while(i>0)
	{
		sleep(1);
		Pop_front(head);
		Display(head);
		i--;
	}
}
void* pthread_product(void* arg)
{
	node_p head =(node_p)arg;
	int data =0;
	while(1)
	{
		sleep(2);
	  pthread_mutex_lock(&mylock);//上锁
	 data =rand()%1000;
		 Push_front(head,data);
	  printf("I am a producter,%d\n",data);
	 pthread_cond_signal(&mycond);//唤醒一个线程
	// Display(head);
	 pthread_mutex_unlock(&mylock);//下锁
	}
}
void* pthread_consumer(void* arg)
{
   node_p head= (node_p) arg;
   int data = 0;
while(1)
{

	sleep(1);
  pthread_mutex_lock(&mylock);
  if(IsEmpty(head))
  {
	pthread_cond_wait(&mycond,&mylock);
  }
 printf("I am a consumer:");
 Display(head);
  Pop_front(head);
  printf("\n");
  pthread_mutex_unlock(&mylock);
} 
 

}
int main()
{
   //	test();
   node_p head=NULL;
   Init(&head); 
   pthread_t tid1,tid2;
   int ret1 = pthread_create(&tid1,NULL,pthread_product,(void*)head);
   int ret2 = pthread_create(&tid2,NULL,pthread_consumer,(void*)head);
	printf("ret1:%lu,ret2:%lu\n",ret1,ret2);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	pthread_mutex_destroy(&mylock);
	pthread_cond_destroy(&mycond);
   return 0;
}
