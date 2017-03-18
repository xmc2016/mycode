/*************************************************************************
	> File Name: server.c
	> Author:没有缘分的主角
	> Mail:暂无
	> Created Time: 2017年03月16日 星期四 13时14分12秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>

int startup(const char* _ip,int _port)
{
	//创建流式套接字
	int sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock<0)
	{
		perror("sock");
		exit(2);
	}
	struct sockaddr_in local;
	local.sin_family=AF_INET;
	local.sin_port = htons(_port);
	local.sin_addr.s_addr=inet_addr(_ip);
	if(bind(sock,(struct sockaddr*)&local,sizeof(local))<0)
	{
		perror("bind");
		exit(3);
	}
	if(listen(sock ,5)<0)   //设置监听队列
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
		printf("Usage:%s, [local_ip],[local_prot]");
		exit(1);
	}
	int listen_sock = startup(argv[1],atoi(argv[2]));
	while(1)
	{
		struct sockaddr_in remote; //用来保存链接用户信息
		int len = sizeof(remote);
		int a = accept(listen_sock,(struct sockaddr*)&remote,&len);
		if(a<0)
		{
			perror("accept");
			continue;
		}
		printf("connect success, IP:%s,port:%u\n",\
				inet_ntoa(remote.sin_addr),ntohs(remote.sin_port));
		pid_t id = fork();
		if(id<0)
		{
			perror("fork");
			close(a);
			continue;
		}
		else if(id==0)  //child
		{
			if(fork()>0)  //再创建一个子进程
			{
				exit(5);
			}
			char buf[1024];
			while(1)
			{
			 ssize_t s = read(a,buf,sizeof(buf)-1);
			 if(s>0)
			 {
				 buf[s]=0;
				 printf("client# %s\n",buf);
				
			 }
			 else{
				 printf("clent is quit\n"); //子进程退出
				 break;
			 }
			
			}
		}
		else
		{
			close(a);
			waitpid(id,NULL,0);
		}

	}
	close(listen_sock);
	return 0;
}
