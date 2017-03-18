/*************************************************************************
	> File Name: client.c
	> Author:没有缘分的主角
	> Mail:暂无
	> Created Time: 2017年03月13日 星期一 16时43分49秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

int main(int argc, char* argv[])
{
	if(argc!=3)
	{

		printf("please  input IP, port\n");
		return 3;
	}
	int sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock<0)
	{
		perror("sock");
		exit(1);
	}
	struct sockaddr_in server;
	server.sin_family=AF_INET;
	server.sin_port=htons(atoi(argv[2]));
	server.sin_addr.s_addr=inet_addr(argv[1]);
	int connfd=connect(sock,(struct sockaddr*)&server,sizeof(server));
	if(connfd<0)
	{
		perror("connect");
		return -1;
	}
	printf("connect success ...\n");
	char buf[1024];
	while(1)
	{
		printf("client#  ");
		fflush(stdout);
		ssize_t s =read(0,buf,sizeof(buf)-1);
		if(s>0)
		{
			buf[s-1] = 0;
			write(sock,buf,s);
		}
		else
		{
			break;
		}

	}
	close(sock);
	return 0;
}
