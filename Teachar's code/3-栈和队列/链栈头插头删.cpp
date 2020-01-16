#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0
#define Status int
#define SElemType int
//只在头部进行插入和删除
typedef struct LNode
{
	SElemType data;
	struct LNode *next;
}LNode, *LinkStack;


Status InitStack(LinkStack &S)
{
	S = (LinkStack)malloc(sizeof(LNode));
	if(!S)
		return ERROR;
	S->next = NULL;
	return OK;
}

Status GetTop(LinkStack S, SElemType &e)
{
	if(!S->next)
		return ERROR;
	e = S->next->data;
	return OK;
}

Status Push(LinkStack &S, SElemType e)
{
	LinkStack newNode = (LinkStack)malloc(sizeof(LNode));
	if(!newNode)
		return ERROR;
	newNode->data = e;
	newNode->next = S->next;
	S->next = newNode;
	return OK;
}

Status Pop(LinkStack &S, SElemType &e)
{
	LinkStack p = S->next;
	S->next = p->next;
	e = p->data;
	free(p);
	return OK;
}

void PrintStack(LinkStack S)
{
	LinkStack p = S->next;
	while (p)
	{
		printf("%d ",p->data);
		p = p->next;
	}
	printf("\n");
}


int main(void)
{
	LinkStack LS;
	int i = 0;
	SElemType e;
	InitStack(LS);
	for(i = 0; i < 6; ++i)
	{
		Push(LS, (i + 1)*11);
		PrintStack(LS);
	}
	Pop(LS, e);
	printf("%d \n", e);
	PrintStack(LS);



	return 0;
}