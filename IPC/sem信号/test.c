/*************************************************************************
	> File Name: test.c
	> Author:没有缘分的主角
	> Mail:暂无
	> Created Time: Fri 17 Feb 2017 04:18:56 PM CST
 ************************************************************************/

#include"mySem.h"
int main()
{
    int semid = CreateSem(10);
	printf("semid:%d\n",semid);
	InitSem(semid);
	pid_t id = fork();
	if(id==0)
	{
	  static int count = 10;
		while(count--)
		{
		    P(semid,0);
			usleep(5300);
			printf("A ");
			fflush(stdout);
			usleep(5555);
			printf("A ");
			usleep(100000);
			fflush(stdout);
		    V(semid,0);
		}
	}
	else{
        static int count = 10;
		while(count--)
		{
		  P(semid,0);
			usleep(10000);
			printf("B ");
			fflush(stdout);
			usleep(55555);
			printf("B ");
			fflush(stdout);
			V(semid,0);
		}
	}
		DestorySem(semid);
	return 0;
}

