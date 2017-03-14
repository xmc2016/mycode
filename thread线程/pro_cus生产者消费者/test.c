/*************************************************************************
	> File Name: test.c
	> Author:没有缘分的主角
	> Mail:暂无
	> Created Time: 2017年02月20日 星期一 14时15分02秒
 ************************************************************************/

#include"LinkList.h"
int main()
{
	node_p head;
	Init(&head);
	int i = 0;

	printf("head:%d\n",head->data);
	while(i<10)
	{
		sleep(1);
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
	return 0;
}
