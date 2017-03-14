/*************************************************************************
	> File Name: client.c
	> Author:没有缘分的主角
	> Mail:暂无
	> Created Time: 2017年02月17日 星期五 20时17分52秒
 ************************************************************************/
#include"comm.h"
int main()
{
	int shmid=getshm();//得到一共享内存的id
	printf("shmid is %d\n",shmid);
	char*buf = (char*)atshm(shmid);
	int i = 0;
	while(i<SIZE-1)
	{
		sleep(1);
		buf[i++]='c';
		i %= SIZE-1;
		buf[i]='\0';
	}
	dtshm(buf);
	return 0;
}
