/*************************************************************************
	> File Name: server.c
	> Author:没有缘分的主角
	> Mail:暂无
	> Created Time: 2017年02月14日 星期二 21时18分10秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#define _PATH_ "./cmd_pipe"
int main()  //fifo write
{
	umask(0);
	int ret = mkfifo(_PATH_,0666|S_IFIFO);
	 if(ret == -1)
	 {
		 printf("mkfifo error\n");
		 return 1;
	 }
	 int fd = open(_PATH_,O_WRONLY);
	 if(fd<0)
	 {
		 printf("open error\n");

	 }
     char buf[1024];
	  memset(buf,'\0',sizeof(buf));
	  while(1)
	  {
 
		  printf("请输入：\n"); 
		  scanf("%s",buf);
		  int ret = write(fd,buf,strlen(buf)+1);
		  if(ret<0)
		  {
			  printf("write error\n");
			  break;
		  }
		 // if(strncmp(buf,"quit",4)==0);
		 // {
		   //  break;
		 // }
	  }
     close(fd);
  return 0;

}
