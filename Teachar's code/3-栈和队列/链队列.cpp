#include <stdio.h>
#include <stdlib.h>
#define QElemType int

//---单链队列——队列的链式存储结构(带头结点)---
typedef struct QNode
{
	QElemType data;
	struct QNode *next;
}QNode, *QueuePtr;

typedef struct
{
	QueuePtr front;	//队头指针
	QueuePtr rear;	//队尾指针
}LinkQueue;

int InitQueue(LinkQueue &Q)	//带头结点的队列
{
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));	//带头结点的队列
	if(!Q.front)	//存储分配失败
		exit(-1);
	Q.front->next = NULL;
	return 1;
}

int DestroyQueue(LinkQueue &Q)
	//销毁队列Q
{
	while(Q.front)
	{
		Q.rear = Q.front->next;
		free(Q.front);
		Q.front = Q.rear;
	}
	return 1;
}

int EnQueue(LinkQueue &Q, QElemType e)
	//插入元素e为Q的新的队尾元素
{
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if(!p)		//存储分配失败
		exit(-1);
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	return 1;
}

int DeQueue(LinkQueue &Q, QElemType &e)
	//若队列不空，则删除Q的对头元素，用e返回其值，并返回1
	//否则返回0
{
	QueuePtr p;
	if(Q.front == Q.rear)
		return 0;
	p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;
	if(Q.rear == p)
		Q.rear = Q.front;
	free(p);
	return 1;
}

void PrintQueue(LinkQueue Q)
{
	QueuePtr p = Q.front->next;
	while (p)
	{
		printf("%d\n",p->data);
		p = p->next;
	}
}


int main(void)
{
	LinkQueue Q;
	QElemType e;
	InitQueue(Q);
	EnQueue(Q,11);
	EnQueue(Q,22);
	EnQueue(Q,33);
	EnQueue(Q,44);
	PrintQueue(Q);
	DeQueue(Q,e);
	PrintQueue(Q);

	return 0;
}