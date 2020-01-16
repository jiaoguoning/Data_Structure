#include <stdio.h>
#include <stdlib.h>
#define QElemType int

//---�������С������е���ʽ�洢�ṹ(��ͷ���)---
typedef struct QNode
{
	QElemType data;
	struct QNode *next;
}QNode, *QueuePtr;

typedef struct
{
	QueuePtr front;	//��ͷָ��
	QueuePtr rear;	//��βָ��
}LinkQueue;

int InitQueue(LinkQueue &Q)	//��ͷ���Ķ���
{
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));	//��ͷ���Ķ���
	if(!Q.front)	//�洢����ʧ��
		exit(-1);
	Q.front->next = NULL;
	return 1;
}

int DestroyQueue(LinkQueue &Q)
	//���ٶ���Q
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
	//����Ԫ��eΪQ���µĶ�βԪ��
{
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if(!p)		//�洢����ʧ��
		exit(-1);
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	return 1;
}

int DeQueue(LinkQueue &Q, QElemType &e)
	//�����в��գ���ɾ��Q�Ķ�ͷԪ�أ���e������ֵ��������1
	//���򷵻�0
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