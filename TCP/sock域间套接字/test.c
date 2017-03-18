
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	int sv[2]={0,0};
	int sock=socketpair(PF_LOCAL,SOCK_STREAM,0,sv);
	if(sock == -1)
	{
		perror("socketpair");
		exit(1);
	}
	pid_t id=fork();
	if(id < 0)
	{
		perror("fork");
		exit(2);
	}
	else if(id == 0)  //child
	{
		char buf[1024];
		close(sv[0]);
		while(1)
		{
			char msg[]="hi,my name is kiki";
			write(sv[1],msg,strlen(msg));
			ssize_t size=read(sv[1],buf,sizeof(buf));
			if(size > 0)
			{
				buf[size]='\0';
				printf("echo# %s\n",buf);
			}
			else
			{
				printf("client is quit!\n");
				exit(3);
			}
			sleep(1);
		}
	}
	else   //father
	{
		close(sv[1]);
		char buf[1024];
		while(1)
		{
			ssize_t size=read(sv[0],buf,sizeof(buf));
			if(size > 0)
			{
				buf[size]='\0';
				printf("client# %s\n",buf);
				buf[0]='H';
				write(sv[0],buf,sizeof(buf));
			}
			sleep(1);
		}
		waitpid(id,NULL,0);
	}
	return 0;
}
