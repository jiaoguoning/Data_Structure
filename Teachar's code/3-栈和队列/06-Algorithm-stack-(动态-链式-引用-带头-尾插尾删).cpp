#include <stdio.h>
#include <stdlib.h>
#define OK			1
#define ERROR		0
#define Status		int
#define SElemType	int
//只在尾部进行插入和删除
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
	LinkStack p = S;
	if(!S->next)
		return ERROR;
	while (p->next)
		p = p->next;
	e = p->data;
	return OK;
}

Status Push(LinkStack &S, SElemType e)
{
	LinkStack p = S;
	LinkStack newNode = (LinkStack)malloc(sizeof(LNode));
	if(!newNode)
		return ERROR;
	while (p->next)
		p = p->next;
	newNode->data = e;
	newNode->next = p->next;
	p->next = newNode;
	return OK;
}

Status Pop(LinkStack &S, SElemType &e)
{
	LinkStack pre, p = S;
	while (p->next)
	{
		pre = p;
		p = p->next;
	}
	pre->next = p->next;
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
	GetTop(LS,e);
	printf("%d\n",e);



	return 0;
}