/*************************************************************************
	> File Name: LinkList.h
	> Author:没有缘分的主角
	> Mail:暂无
	> Created Time: 2017年02月20日 星期一 13时18分45秒
 ************************************************************************/
#ifndef _LINK_
#define _LINK_
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include <unistd.h>
typedef struct node_t
{
	int data;
	struct node_t*next;
}node_t,*node_p,**node_pp;
void Push_front(node_p list,int x);
void Pop_front(node_p list);
void Display(node_p list);
int IsEmpty(node_p list);
void Init(node_pp head);
#endif
