/*************************************************************************
	> File Name: server.c
	> Author:没有缘分的主角
	> Mail:暂无
	> Created Time: 2017年03月14日 星期二 13时14分32秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<stdlib.h>

static void Usage(const char*  proc)
{
	printf("Usage:%s [local_ip] [local_port]\n",proc);
}
int main(int argc ,char* argv[])
{
	if(argc!=3)
	{
		Usage(argv[0]);
	}
	int sock = socket(AF_INET,SOCK_DGRAM,0); //创建sock套接字
	if(sock<0)
	{
		perror("sock\n");
		return -1;
	}
	//使用IPv4协议
	struct sockaddr_in local;
	local.sin_family=AF_INET;
	local.sin_port=htons(atoi(argv[2]));
	local.sin_addr.s_addr=inet_addr(argv[1]);
	socklen_t len = sizeof(local);
	if(bind(sock,(const struct sockaddr*)&local,len)<0)
	{
		perror("bind\n");
		return -2;
	}
	char buf[1024]; //定义缓冲区
	int buflen = sizeof(buf);
	while(1)
	{
		struct sockaddr_in peer;
		int len = sizeof(peer);
		int recv = recvfrom(sock,buf,buflen ,0,
				(struct sockaddr*)&peer,&len);
		if(recv<0)
		{
			perror("recv");
			return -3;
		}
		else
		{
			printf("connect success ,ip is %s,port is %u \n",\
					inet_ntoa(peer.sin_addr),ntohs(peer.sin_port));
			printf("from client# %s\n",buf);
			continue;
		}
	}
	close(sock);

	return 0;
}
