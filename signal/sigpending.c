/*************************************************************************
	> File Name: sigpending.c
	> Author:没有缘分的主角
	> Mail:暂无
	> Created Time: 2017年02月24日 星期五 08时52分15秒
 ************************************************************************/

#include<stdio.h>
#include<signal.h>
#include<unistd.h>
void printsigset(sigset_t* set)
{
	int i = 0;
	for(;i<32;i++)
	{
		if(sigismember(set,i)){ //判断指定信号是否在目标集合中
				putchar('1');
		}else{
			putchar('0');
			}
	}
	puts("");
}
int main()
{
	sigset_t s, p;//定义信号集对象
	sigemptyset(&s); //初始化信号集清零
	sigaddset(&s,SIGINT); //向信号集s添加SIGINT信号，ctrl+c产生SIGINT信号
	sigprocmask(SIG_BLOCK,&s,NULL);//向阻塞信号集添加SIGINT信号
	while(1){
		sigpending(&p); //获取未决信号集
		printsigset(&p);
		sleep(1);

	}
	return 0;

}
