/*************************************************************************
	> File Name: server.c
	> Author:没有缘分的主角
	> Mail:暂无
	> Created Time: 2017年03月16日 星期四 17时48分23秒
 ************************************************************************/

#include<stdio.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<pthread.h>
int startup(const char* _ip,int _port)
{
	int sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock<0)
	{
		perror("sock");
		exit(1);
	}
	struct sockaddr_in local;
	local.sin_family=AF_INET;
	local.sin_port = htons(_port);
	local.sin_addr.s_addr = inet_addr(_ip);
	int on = 1;
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
	if(listen(sock,5)<0)
	{
		perror("listen");
		exit(4);
	}
	return sock;
}
void* handler(void* arg)
{
	//pthread_detach(pthread_self());  //将当前线程与主线程分离
	int sock = *((int*)arg);
	char buf[1024];
	while(1)
	{
		ssize_t s = read(sock,buf,sizeof(buf)-1);
		if(s>0)  //读到信息
		{
			buf[s] = 0;
			printf("client say#:%s\n",buf);
			if(write(sock,buf,sizeof(buf)-1)<0) //将收到的信息发送给客户端
			{
				break;
			}
		}else{  

			printf("client is quit \n");
			break;
		}
	}

}
int main(int argc,char*argv[])
{
	if(argc!=3)
	{
		printf("Usage:%s,[local_ip],[local_port]\n",argv[0]);
		return -1;
	}
	int listen_sock  = startup(argv[1],atoi(argv[2]));//创建监听套接字
	while(1)
	{
		struct sockaddr_in peer;
		int len =sizeof(peer);
		int sock = accept(listen_sock,(struct sockaddr*)&peer,&len);
 										//accept返回的文件描述符是真正用于通信的套接子
		if(sock<0)
		{
			perror("accept");
			return -2;
		}
		printf("connect access, ip is %s ,port is %u\n",\
				inet_ntoa(peer.sin_addr),ntohs(peer.sin_port));
		pthread_t tid ;
		int ret = pthread_create(&tid,NULL,handler,&sock);
	    if(ret!=0)
		{
			perror("pthread_create");
			close(sock);
			return -3;
		}
		pthread_detach(pthread_self());

	}
	close(listen_sock);
	return 0;
}
