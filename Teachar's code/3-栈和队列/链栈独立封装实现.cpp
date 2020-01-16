#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0
#define Status int
#define SElemType int
//只在头部进行插入和删除(不带头结点)
typedef struct LNode
{
	SElemType data;
	struct LNode *next;
}LNode, *LinkList;

typedef struct 
{
	LNode *top;
	LNode *base;
	int length;
}LinkStack;


Status InitStack(LinkStack &S)
{
	S.base = NULL;
	S.top = NULL;
	S.length = 0;
	return OK;
}

Status GetTop(LinkStack S, SElemType &e)
{
	if(S.length == 0)
		return ERROR;
	e = S.top->data ;
	return OK;
}

Status Push(LinkStack &S, SElemType e)
{
	LNode *newNode = (LNode *)malloc(sizeof(LNode));
	newNode->data = e;
	newNode->next = S.top;
	S.top = newNode;
	if(!S.base)
		S.base = newNode;
	++S.length;
	return OK;
}

Status Pop(LinkStack &S, SElemType &e)
{
	LNode *p = S.top;
	if(S.length == 0)
		return ERROR;
	e = S.top->data;
	S.top = S.top->next;
	free(p);
	--S.length;
	return OK;
}

void PrintStack(LinkStack S)
{
	LNode *p = S.top;
	printf("由栈顶到栈底：");
	while (p)
	{
		printf("%d  ",p->data);
		p = p->next;
	}
	printf("\n");
}


int main(void)
{
	LinkStack LS;
	InitStack(LS);
	Push(LS,11);
	Push(LS,22);
	Push(LS,33);
	Push(LS,44);
	Push(LS,55);
	PrintStack(LS);
	SElemType e ;
	GetTop(LS , e);
	printf("栈顶元素是: %d\n",e);
	Pop(LS,e);
	PrintStack(LS);
	Pop(LS,e);
	PrintStack(LS);



	return 0;
}