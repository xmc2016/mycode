/*************************************************************************
	> File Name: client.c
	> Author:没有缘分的主角
	> Mail:暂无
	> Created Time: 2017年03月14日 星期二 13时18分43秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<stdlib.h>
static Usage(const char* proc)
{
	printf("Usage:%s,[server_ip] [server_port]\n",proc);
}
int main(int argc,char* argv[])
{
	if(argc!=3)
	{
		Usage(argv[0]);
	}
	int sock = socket(AF_INET,SOCK_DGRAM,0);
	if(sock<0)
	{
		perror("sock\n");
		return -1;
	}
	char buf[1024];
	while(1)
	{
		printf("sendto# ");
		fflush(stdout);
		struct sockaddr_in server;
		server.sin_family=AF_INET;
		server.sin_port =htons(atoi(argv[2]));
		server.sin_addr.s_addr=inet_addr(argv[1]);
		socklen_t len = sizeof(server);
		ssize_t s=read(0,buf ,sizeof(buf)-1);
		if(s>0)
		{
			buf[s-1]=0;
			if(sendto(sock,buf,sizeof(buf),0,(struct sockaddr*)&server,len)<0)
			{
				perror("send to");
				return -2;
			}
		}
		else{

			continue;
		}


	}
	close(sock);
	return 0;
}
