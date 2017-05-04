/*************************************************************************
	> File Name: test.c
	> Author:没有缘分的主角
	> Mail:暂无
	> Created Time: 2017年05月04日 星期四 14时35分55秒
 ************************************************************************/

#include"CommentConvert.h"
int main()
{
	FILE* fpRead = NULL;
	FILE* fpWrite=NULL;
	printf("转化开始\n");
	 fpRead=fopen(INPUT_FILE ,"r");
	if(NULL==fpRead)
	{
		perror("open file for read\n");
		exit(1);
	}
	 fpWrite =fopen(OUTPUT_FILE,"w");
	if(NULL==fpWrite)
	{
		perror("open file for write\n");
		exit(2);
	}
	CommentConvert(fpRead,fpWrite);
	fclose(fpRead);
	fclose(fpWrite);
	printf("转化结束\n");
	return 0;
}

