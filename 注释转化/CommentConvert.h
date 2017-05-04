/*************************************************************************
	> File Name: CommentConvert.h
	> Author:没有缘分的主角
	> Mail:暂无
	> Created Time: 2017年05月04日 星期四 13时15分33秒
 ************************************************************************/
#ifndef __COMMENTCONVERT__
#define __COMMENTCONVERT__
#include<stdio.h>
#define INPUT_FILE    "input.c"
#define OUTPUT_FILE   "output.c"
enum  STATE 
{
	NUL_STATE,
	C_STATE,
	CPP_STATE,
	END_STATE
};

void CommentConvert(FILE* pfRead,FILE*pfWrite);
void Do_NUL_State(FILE* pfRead,FILE*pfWrite); //无状态
void Do_C_State(FILE*pfRead,FILE*pfWrite);//C状态
void Do_CPP_State(FILE*pfRead,FILE*pfWrite);//C++状态
#endif 

