#include"comm.h"
int main()
{

	int msgid = creatMsgQueue();
	char buf [2*MYSIZE];
	while(1){

		if(recvMessage(msgid,CLIENT_TYPE,buf)<0)
		{
			break;
		}
		printf("client# %s\n",buf);
		if(sendMessage(msgid,SERVER_TYPE,buf)<0)
		{
			break;
		}
	}
   destroyMsgQueue(msgid);
	return 0;
}
