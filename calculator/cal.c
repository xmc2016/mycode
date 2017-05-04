#include<stdio.h>
#include<ctype.h>
char getPrintChar(); //读取字符
double factor(); //处理括号
double add_sub(); //处理加减法
double term(); //处理乘除法
void  match(char exceptedToken);//读入下一个字符
void error();//错误处
char token;
double add_sub() //处理加减法
{
	double tmp = term();
	while (token == '+' || token == '-')
	{
		switch (token)
		{
		case '+':
			match('+');
			tmp += term();
			break;
		case '-':
			match('-');
			tmp -= term();
			break;
		default:
			break;
		}
	}
	return tmp;
}
double term() //处理乘除法
{
	double tmp = factor();
	while (token == '*' || token == '/')
	{
		switch (token)
		{
		case '*':
			match('*');
			tmp *= factor();
			break;
		case '/':
			match('/');
			printf("%lf\n",tmp);
			tmp /= factor();
			printf("%lf\n", tmp);
			break;
		default:
			break;
		}
	}
	return tmp;
}
double factor()//处理括号
{
	double tmp;
	if (token == '(')
	{
		match('(');
		tmp = add_sub();
		match(')');
	}
	else if (isdigit(token)) //isdigit() 判断 token是否阿拉伯数字
	{
	
		ungetc(token, stdin);//  ungetc把一个先前读入的字符返回到流中，这样它可以在以后被重新读入
		scanf("%lf", &tmp);
		token = getPrintChar(); //读入下一个字符
	}
	else
	{
		error();
	}
	return tmp;
}
void  match(char exceptedToken)//读入下一个字符
{
	if (token == exceptedToken)
	{
		token = getPrintChar();
	}
	else
	{
		error();
	}
}
void error()//错误处
{
	fprintf(stderr, "Error!\n");
	exit(0);
}
char getPrintChar() //读取字符
{
	char tmp;

	do
	tmp = getchar();
	while (isblank(tmp)); //isblank()用来判断字符是TAB或者是空格

	return tmp;
}
int main()
{
	double result;
	for (;;)
	{
		token = getPrintChar();
		if (token == 'q')
		{
			exit(0);
		}
		result = add_sub();
		if (token == '\n')
		{
			printf("Result is %lf\n", result);
		}
		else
		{
			error();
		}
	}
	return  0;
}
