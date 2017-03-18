/*************************************************************************
	> File Name: client.c
	> Author:没有缘分的主角
	> Mail:暂无
	> Created Time: 2017年03月16日 星期四 13时15分12秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
int main(int argc,const char* argv[])
{
 if (argc!=3)
 {
	 printf("Usage:%s,[server_ip],[server_port]",argv[0]);
	 return -1;
 }
 int sock = socket(AF_INET,SOCK_STREAM,0);
 if(sock<0)
 {
	 perror("sock");
	 return -2;
 }
struct sockaddr_in server;
server.sin_family=AF_INET;
server.sin_port=htons(atoi(argv[2]));
server.sin_addr.s_addr=inet_addr(argv[1]);
int c = connect(sock,(struct sockaddr*)&server,sizeof(server));
if(c<0)
{
	perror("connect");
	return -3;
}
while(1)
{
	char buf[1024];
	printf("send# ");
	fflush(stdout);
	ssize_t s = read(0,buf,sizeof(buf)-1);
	 buf[s-1] = 0;
	if(s>0)
	{
		if(write(sock,buf,s)<0)
		{
			perror("write");
			return  -4;
		}
	}

}
close(sock);
return 0;
}

