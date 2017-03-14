/*************************************************************************
	> File Name: server.c
	> Author:没有缘分的主角
	> Mail:暂无
	> Created Time: 2017年02月17日 星期五 20时17分06秒
 ************************************************************************/
#include"comm.h"
int main()
{
	int shmid = creatshm();//创建共享内存
	printf("shmid is %d:\n",shmid);
	char* buf = (char*)atshm(shmid);//得到共享内存的虚拟地址
	while(1)
	{
		printf("%s\n",buf);

	}
	dtshm(buf);
	destroyshm(shmid);
	return 0;
}
