/*************************************************************************
	> File Name: Linklist.c
	> Author:没有缘分的主角
	> Mail:暂无
	> Created Time: 2017年02月19日 星期日 14时48分16秒
 ************************************************************************/

#include"LinkList.h"
node_p BuyNode(int x)
{
  node_p  tmp=(node_p)malloc(sizeof(node_t));
  if(tmp==NULL)
  {
	  perror("malloc error\n");
	  return;

  }
   tmp->data=x;
   tmp->next=NULL;
   return tmp;

}
void Push_front(node_p list,int x)
{
  assert(list);
  node_p node = BuyNode(x);
  node->next=list->next;
  list->next=node;
}
void Pop_front(node_p list)
{
    if(IsEmpty(list))
	{
	   printf("list empty \n");
	   return ;
	}
	node_p Node = list->next;
	list->next=Node->next;
   free(Node);
   Node=NULL;
}
void Display(node_p list)
{
	if(IsEmpty(list))
	{
		return;
	}
	node_p cur = list->next;
	while(cur!=NULL)
	{
		printf("%d->",cur->data);
		cur =cur->next;
	}
    printf("NULL\n");

}
int IsEmpty(node_p list)
{
	if(list->next!=NULL)
	{
		return 0;
	}
	else{
		return 1;
	}
}

void Init(node_pp head)
{
	*head=BuyNode(0);
}

