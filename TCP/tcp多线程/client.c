/*************************************************************************
	> File Name: client.c
	> Author:没有缘分的主角
	> Mail:暂无
	> Created Time: 2017年03月16日 星期四 17时49分01秒
 ************************************************************************/

#include<stdio.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

int main(int argc,char*argv[])
{
	if(argc!=3)
	{
		printf("Usage%s,[server_ip],[server_port]\n",argv[0]);
		return -1;
	}
	int sock = socket(AF_INET,SOCK_STREAM,0);//client端socket()函数返回的文件描述符，直接用于通信
	if(sock<0)
	{
		perror("sock");
		return -2;
	}
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(atoi(argv[2]));
	server.sin_addr.s_addr = inet_addr(argv[1]);
	socklen_t len = sizeof(server);	
	int ret  = connect(sock,(struct sockaddr*)&server , len); //只用于连接客户端 ,成功返回0，失败返回-1
	if(ret<0)
	{
		perror("connect");
		return -3;
	}
	char buf[1024];
	while(1)
	{
		printf("send # ");
		fflush(stdout);
		ssize_t  size = read(0,buf,sizeof(buf)-1);
		if(size>0)
		{
			buf[size-1] = 0;
			if(write(sock,buf,size)<0)//将buf里的内容写入sock
			{
				break;
			}
            ssize_t  s =read(sock,buf,sizeof(buf)-1);//sock里读到buf
													//	接受server发送的信息
			if(s>0)
			{
				buf[s]=0;
				printf(" serer echo# %s\n",buf);
			}
		}
	}
	close(sock);
	return 0;
}
