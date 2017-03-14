
#include"comm.h"
int commMsgQueue(int flag)
{
  key_t _k = ftok(PATHNAME,PROJID);// 获得k值
 if(_k<0)
 {
   perror("ftok");
   return -1;

 } 
int msg_id =msgget(_k,flag);
if(msg_id<0)//创建失败
 {
	perror("megget");
	return -2;
 } 
	return msg_id;
}
int creatMsgQueue()//创建
{
  return commMsgQueue(IPC_CREAT |IPC_EXCL |0666);
}
int getMsgQueue() //获得消息队列
{
  return commMsgQueue(IPC_CREAT);
}
int sendMessage(int msg_id,long type,const char*msg)//发消息
{
  struct msgbuf buf;
  buf.mytype = type;
  strcpy(buf.mtext,msg);
  int ret = msgsnd(msg_id,&buf,sizeof(buf.mtext),0);
  if(ret<0)
  {
	  perror("msgsnd");
	  return -1;
  }
  return 0;
}
int recvMessage(int msg_id,int type,char out[])//接受消息
{
  struct msgbuf buf;
  int size = msgrcv(msg_id,&buf,sizeof(buf.mtext),type,0);
  if(size>0)
  {
	  //buf.mtext[size] = '\0';
	  strncpy(out,buf.mtext,size);
	  return 0;
  }
  perror("msgrcv");
  return -1;
}
int destroyMsgQueue(int msg_id)//销毁
{
	if(msgctl(msg_id,IPC_RMID,NULL)<0)
	{
		perror("msgctl");
		return -1;
	}

	return 0;

}
