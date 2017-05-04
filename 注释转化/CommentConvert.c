/*************************************************************************
	> File Name: CommentConvert.c
	> Author:没有缘分的主角
	> Mail:暂无
	> Created Time: 2017年04月27日 星期四 17时11分34秒
 ************************************************************************/
#include"CommentConvert.h"
enum STATE state =NUL_STATE;
void CommentConvert(FILE* pfRead,FILE*pfWrite)
{
	while(state!=END_STATE)
	{
		switch(state)
		{
			case NUL_STATE:
				Do_NUL_State(pfRead,pfWrite);
				break;
			case C_STATE:
				Do_C_State(pfRead,pfWrite);
				break;
			case CPP_STATE:
			Do_CPP_State(pfRead,pfWrite);
				break;
			case END_STATE:
				break;
			default:
				break;
		}
	}
}

void Do_NUL_State(FILE* pfRead,FILE*pfWrite)//无状态
{
	int first=0;
	int second =0;
	first =fgetc(pfRead);
	switch(first)
	{
		case '/':
			second = fgetc(pfRead);
			if(second=='/')
			{
				state=CPP_STATE;
				fputc('/',pfWrite);
				fputc('/',pfWrite);
			}
			else if(second=='*')
			{
				state=C_STATE;
				fputc('/',pfWrite);
				fputc('/',pfWrite);
			}
			break;
		case EOF:
			state =END_STATE;
		//	fputc(first,pfWrite);
			break;
		default: //无状态遇到其他字符之接写入
			fputc(first,pfWrite);
			break;
	}
	
}
void Do_C_State(FILE*pfRead,FILE*pfWrite)  //C状态
{
	int first=0;
	int second=0;
	int third=0; 
	first = fgetc(pfRead);
	switch(first)
	{
		case '*':
			second =fgetc(pfRead);
			if(second=='/') //C状态结束，进入无状态
			{
				state =NUL_STATE;
				third=fgetc(pfRead);
				if(third=='\n') //如果*/后面的字不是回车，则写入回车将第三个字符重新写入流中，如果是回车则写入到输出文件
				{
					fputc('\n',pfWrite);
				}
				else
				{
					fputc('\n',pfWrite);
					ungetc(third,pfRead);
				}
			}
			else //如果第二个字符不是‘'/'则将第一个字符写入，第二个字符重新返回流中
			{
				fputc(first,pfWrite);
				ungetc(second,pfRead);
			}
		break;
		case EOF:
		// fputc(first,pfWrite);
		 state=END_STATE;
		 break;
		case '\n':
		 fputc(first,pfWrite);
		 fputc('/',pfWrite);
		 fputc('/',pfWrite);
	    break;
		default:
		fputc(first,pfWrite);
		break;
	}
}
void Do_CPP_State(FILE* pfRead,FILE*pfWrite)//C++状态
{
	int first=0;
	first=fgetc(pfRead);
	switch(first)
	{
		case '\n':
			fputc('\n',pfWrite);
			state = NUL_STATE;
			break;
		case EOF:
		//	fputc(first,pfWrite);
			state=END_STATE;
			break;
		default:
			fputc(first,pfWrite);
			break;

	}
}
