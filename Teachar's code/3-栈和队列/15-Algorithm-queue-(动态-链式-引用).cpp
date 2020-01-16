#include <stdio.h>
#include <stdlib.h>
#define Status          int
#define OK              1
#define ERROR           0
#define OVERFLOW        -2
#define QElemType       int

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

// 链队列初始化
Status InitQueue(LinkQueue &Q)	//带头结点的队列
{
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));	//带头结点的队列
	if(!Q.front)	//存储分配失败
		exit(OVERFLOW);
	Q.front->next = NULL;
	return OK;
}

// 链队列销毁
Status DestroyQueue(LinkQueue &Q)
{
	while(Q.front)
	{
		Q.rear = Q.front->next;
		free(Q.front);
		Q.front = Q.rear;
	}
	return OK;
}

// 入队（	插入元素e为Q的新的队尾元素）
Status EnQueue(LinkQueue &Q, QElemType e)
{
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if(!p)		//存储分配失败
		exit(OVERFLOW);
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	return OK;
}

// 出队（删除Q的队头元素）
Status DeQueue(LinkQueue &Q, QElemType &e)
	//若队列不空，则删除Q的队头元素，用e返回其值，并返回OK
	//否则返回ERROR
{
	QueuePtr p;
	if(Q.front == Q.rear)
		return ERROR;
	p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;
	if(Q.rear == p)
		Q.rear = Q.front;
	free(p);
	return OK;
}

// 打印（队列元素从头到尾输出）
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