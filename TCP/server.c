/*************************************************************************
	> File Name: server.c
	> Author:没有缘分的主角
	> Mail:暂无
	> Created Time: 2017年03月13日 星期一 16时42分55秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
int startup(int _port,const char* _ip) //参数为端口号和ip地址
{
	int sock = socket(AF_INET,SOCK_STREAM,0);
	printf("sock:%d\n",sock);
	if(sock<0)
	{
		perror("socket");
		exit(1);
	}
	struct sockaddr_in local;
	local.sin_family=AF_INET;
	local.sin_port = htons(_port);
	local.sin_addr.s_addr =inet_addr(_ip);
	int on =1;
	if(setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on))<0)
	{
		perror("setsockopt");
		exit(2);
	}
	if(bind(sock,(struct sockaddr*)&local,sizeof(local))<0)
	{
		perror("bind");
		exit(3);
	}
	if(listen(sock,10)<0)  //listen：监听来自客户端的tcp socket的连接请求
	{
		perror("listen");
		exit(4);
	}
	return sock;

	
}
int main(int argc,char* argv[])
{
	if(argc!=3)
	{
		printf("Usage: %s, [local_iP] [locat_port]\n",argv[0]);
		return 3;
	}
	int listen_sock = startup(atoi(argv[2]),argv[1]);
	while(1)
	{
		socklen_t len =sizeof(struct sockaddr_in);
		struct sockaddr_in routem ;
	    int connfd = accept(listen_sock,(struct sockaddr*)&routem,&len);
		if(connfd<0)
		{
			continue;
		}
		printf("client link ip :%s, port %d \n",\
		inet_ntoa(routem.sin_addr)),ntohs(routem.sin_port);
		char buf[1024];
		while(1)
		{
			ssize_t s = read(connfd,buf,sizeof(buf)-1);
			if(s>0)
			{
			  buf[s] = 0;
				printf("client# %s\n",buf);
			}
		}
	close(connfd);
	}

	return 0;
}
