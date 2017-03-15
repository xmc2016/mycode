/*************************************************************************
	> File Name: client.c
	> Author:没有缘分的主角
	> Mail:暂无
	> Created Time: 2017年02月14日 星期二 21时53分12秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#define _PATH_ "./cmd_pipe"
int main() //fifo read
{
   int fd = open(_PATH_,O_RDONLY);
   if(fd<0)
   {
	   printf("open error\n");
	   return 1;
   }
   char buf[1024];
   memset(buf,'\0',sizeof(buf));

   while(1)
   {
     int ret = read(fd,buf,sizeof(buf));
	if(ret<=0) //error or end of file
	 {
       printf("error or end of file\n");
	  break;
	 }
	 printf("%s\n",buf);
	// if(strncmp(buf,"quit",4)==0)
	  // {
	//	break;
     // }
   }
   close(fd);
	return 0;
}
