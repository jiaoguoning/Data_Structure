#include <stdio.h>
#include <stdlib.h>
#define STACK_INIT_SIZE 20
#define STACKINCREMENT 5
#define ElemType int
typedef struct {
	ElemType *base;
	ElemType *top;
	int stacksize;
}SqStack;

//因为要修改栈S内存中数据成员的值，因此必须传递S的地址
int InitStack(SqStack *S)
{
	S->base = (ElemType*)malloc(sizeof(ElemType) * STACK_INIT_SIZE);
	if (!S->base)
	{
		printf("初始化失败！\n");
		return 0;
	}
	S->top = S->base;
	S->stacksize = STACK_INIT_SIZE;
	return 1;
}

int push(SqStack *S,ElemType e)
{
	if ((S->top - S->base) >= S->stacksize)
	{
		S->base = (ElemType *)realloc(S->base,S->stacksize+STACKINCREMENT);
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

int pop(SqStack *S,ElemType *e)
{
	if (S->top == S->base)
	{
		printf("出栈失败，栈为空!\n");
		return 0;
	}
	*e = *--S->top;
	return 1;
}

int GetTop(SqStack S,ElemType *e)
{
	if(S.base == S.top)
		return 0;
	*e = *(S.top - 1);
	return 1;
}

void PrintStack(SqStack S)
{
	ElemType *p = S.base;
	while(p < S.top)
	{
	
		printf("%d ",(*(p)));
		++p;
	}
	printf("\n");
}

int main(void)
{
	SqStack s;
	int e,i,Status = 0;
	InitStack(&s);
	push(&s,11);
	push(&s,22);
	push(&s,33);
	push(&s,44);
	push(&s,55);

	for (i = 0; i < 6; i++)
	{
		Status = pop(&s,&e);
		if (Status)
			printf("e = %d\n",e);
	}


	return 0;
}



