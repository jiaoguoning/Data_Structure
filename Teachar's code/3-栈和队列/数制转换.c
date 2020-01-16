#include <stdio.h>
#include <stdlib.h>
#define STACK_INIT_SIZE 20
#define STACKINCREMENT 5

typedef struct {
	int *base;
	int *top;
	int stacksize;
}SqStack;

//因为要修改栈S内存中数据成员的值，因此必须传递S的地址
int InitStack(SqStack *S)
{
	S->base = (int*)malloc(sizeof(int) * STACK_INIT_SIZE);
	if (!S->base)
	{
		printf("初始化失败！\n");
		return 0;
	}
	S->top = S->base;
	S->stacksize = STACK_INIT_SIZE;
	return 1;
}

int push(SqStack *S,int e)
{
	if ((S->top - S->base) >= S->stacksize)
	{
		S->base = (int *)realloc(S->base,S->stacksize+STACKINCREMENT);
		if (!S->base)
		{
			printf("追加失败!\n");
			return 0;
		}
		S->top = S->base + S->stacksize;
		S->stacksize += STACKINCREMENT;
	}
	*S->top++ = e;
	return 1;
}

int pop(SqStack *S,int *e)
{
	if (S->top == S->base)
	{
		printf("出栈失败，栈为空!\n");
		return 0;
	}
	*e = *--S->top;
	return 1;
}

int converting(SqStack *S,int N)
{
	while (N)
	{
		if(!push(S,N % 8))
			return 0;
		N /= 8;
	}
	return 1;
}

//数制转换  十进制转八进制
int converting1(SqStack *S,int N)
{
	int e;
	InitStack(S);
	while (N)
	{
		if(!push(S,N % 8))
			return 0;
		N /= 8;
	}

	while(S->base != S->top)
	{
		pop(S,&e);
		printf("%d ",e);
	}
	printf("\n");
	return 1;
}

int main(void)
{
	SqStack s;
	int N = 1348,i,e;
	InitStack(&s);
	converting(&s,N);
	while(s.base != s.top)
	{
		pop(&s,&e);
		printf("%d ",e);
	}
	printf("\n");
	return 0;
}



