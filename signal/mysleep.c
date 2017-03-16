/*************************************************************************
	> File Name: mysleep.c
	> Author:没有缘分的主角
	> Mail:暂无
	> Created Time: 2017年02月24日 星期五 09时43分20秒
 ************************************************************************/

#include<stdio.h>
#include<signal.h>
#include<unistd.h>
void sig_alrm(int signo)
{
	
}
unsigned int mysleep(unsigned int nsecs)
{
	struct sigaction new,old;
	unsigned int unslept=0;
	new.sa_handler=sig_alrm;//sig_alrm 指用户自定义处理信号的函数
	sigemptyset(&new.sa_mask);
	new.sa_flags=0;
	sigaction(SIGALRM,&new,&old);//注册信号处理函数
	alarm(nsecs);//设置闹钟
	pause();//使进程挂起直到有信号递达
	unslept=alarm(0);//清空闹钟
	sigaction(SIGALRM,&old,NULL);//恢复默认信号处理动作
	return unslept;

}
int main()
{
	while(1){
		mysleep(5);
		printf("5 seconds passed\n");
	}
}
