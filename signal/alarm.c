/*************************************************************************
	> File Name: alarm.c
	> Author:没有缘分的主角
	> Mail:暂无
	> Created Time: 2017年02月23日 星期四 11时05分58秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include <signal.h>

long long count = 0;
void func()
{
	alarm(1);
	printf("count is :%d\n",count);
}
int main()
{
	signal(SIGALRM,func);
	alarm(1);
	while(1)
	{
		count++;
//		printf("main count: %d\n",count);
	}
	return 0;
}

