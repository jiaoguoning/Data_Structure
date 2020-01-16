#include <stdio.h>
#include <stdlib.h>
#define Status          int
#define OK              1
#define ERROR           0
#define OVERFLOW        -2
#define STACK_INIT_SIZE 20
#define STACKINCREMENT  5
#define SElemType       char

const SElemType OP[8] = "+-*/()#";
const char priority[][7] =					//算符间的优先级关系
{
	{ '>','>','<','<','<','>','>' },
	{ '>','>','<','<','<','>','>' },
	{ '>','>','>','>','<','>','>' },
	{ '>','>','>','>','<','>','>' },
	{ '<','<','<','<','<','=','0' },
	{ '>','>','>','>','0','>','>' },
	{ '<','<','<','<','<','0','=' },
};

typedef struct {
    SElemType *base;    // 在构造之前和销毁之后，base的值为NULL
    SElemType *top;     // 栈顶指针
    int stacksize;      // 当前已分配存储空间，以元素为单位
}SqStack;

//因为要修改栈S内存中数据成员的值，因此必须传递S的地址
Status InitStack(SqStack *S)
{
    (*S).base = (SElemType*)malloc(sizeof(SElemType) * STACK_INIT_SIZE);
    if (!(*S).base)
    {
        printf("初始化失败！\n");
        exit(OVERFLOW);     // return ERROR;
    }
    (*S).top = (*S).base;
    (*S).stacksize = STACK_INIT_SIZE;
    return OK;
}

Status GetTop(SqStack S,SElemType *e){
    //若栈不空，则用e返回S的栈顶元素，并返回OK；否则返回ERROR
    if(S.base == S.top)
        return ERROR;
    *e = *(S.top - 1);
    return OK;
}

Status Push(SqStack *S,SElemType e){
    //插入元素e为新的栈顶元素 
    if (((*S).top - (*S).base) >= (*S).stacksize)    // 栈满
    {
        (*S).base = (SElemType *)realloc((*S).base,(*S).stacksize+STACKINCREMENT);
        if (!(*S).base)
        {
            printf("追加失败!\n");
            exit(OVERFLOW);     // return ERROR;
        }
        (*S).top = (*S).base + (*S).stacksize;
        (*S).stacksize += STACKINCREMENT;
    }
    *(*S).top++ = e;
    return OK;
}

Status Pop(SqStack *S,SElemType *e)
{
    if ((*S).top == (*S).base)
    {
        printf("出栈失败，栈为空!\n");
        return ERROR;
    }
    *e = *--(*S).top;
    return OK;
}



int IsOpt(SElemType e)
{
	int i = 0;
	while (OP[i])
	{
		if (e == OP[i])		return 1;
		i++;
	}
	return 0;
}

int getIndex(char c)
{
	int i = 0;
	while (OP[i])
	{
		if (c == OP[i])
			return i;
		i++;
	}
	printf("索引失败！\n");
	return -1;
}

char Operate(char a,char theta,char b)
{
	char result = 0;
	switch (getIndex(theta))
	{
	case 0:
		result = (a -'0') + (b -'0');
		break;
	case 1:
		result = (a -'0') - (b -'0');
		break;
	case 2:
		result = (a -'0') * (b -'0');
		break;
	case 3:
		result = (a -'0') / (b -'0');
		break;
	}

	return result += '0';
}

char Precede(char theta1, char theta2)		//获取theta1与theta2之间的优先级
{
	int index1 = getIndex(theta1);
	int index2 = getIndex(theta2);
	return priority[index1][index2];
}
//支持输入   3*(7-5)#      因为存放数据的栈中数据类型为char   只能存放一位数字字符，因此中间结果不能超过两位数
//科学的做法是  采用两个不同类型的栈   一个是存放字符 只存放符号  一个是存放整数   这样更科学
char EvaluateExpression()
	//算术表达式求值的运算符优先算法。设OPTR和OPND分别为运算符栈和运算数栈，
	//OP为运算符集合。
{
	SqStack OPTR;	//运算符栈
	SqStack OPND;	//运算数栈
	int i;
	char c,e,theta,a,b;
	InitStack(&OPTR);
	InitStack(&OPND);
	Push(&OPTR,'#');
	c = getchar();
	while (c != '#' || *(OPTR.top-1) != '#')
	{
		if(!IsOpt(c))
		{
			Push(&OPND,c);
			c = getchar();
		}
		else
		{
			switch (Precede(*(OPTR.top-1),c))
			{
			case '<':
				Push(&OPTR,c);
				c = getchar();
				break;
			case '=':
				Pop(&OPTR,&e);
				c = getchar();
				break;
			case '>':
				Pop(&OPTR,&theta);
				Pop(&OPND,&b);
				Pop(&OPND,&a);
				Push(&OPND,Operate(a,theta,b));
				break;
			}

		}
	}
	return *(OPND.top-1);
}


int main(void)
{
	char r;
	printf("请输入表达式，以#号结束: ");
	//3*(7-5)#  
	r = EvaluateExpression();
	printf("\n该表达式的结果为：");
	printf("%c\n",r);

	return 0;
}



