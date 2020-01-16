#include <stdio.h>

#include <stdlib.h>
#define Status int
#define OVERFLOW -1
#define OK 1
#define ERROR 0

//------------- ѭ�����С����������е�˳��洢�ṹ -------------
#define MAXQSIZE 6	//�����г���
#define QElemType char

typedef struct
{
	QElemType *base;	//��ʼ���Ķ�̬����洢�ռ�
	int front;			//ͷָ�룬�����в��գ�ָ�����ͷԪ��
	int rear;			//�����в��գ�ָ�����Ԫ�ص���һ��Ԫ��
}SqQueue;
void PrintSqQueue(SqQueue Q);
//------------- ѭ�����л������� ---------------
Status InitQueue(SqQueue &Q)
	//����һ���ն���Q
{
	Q.base = (QElemType *)malloc(MAXQSIZE * sizeof(QElemType));
	if(!Q.base)
		exit(OVERFLOW);	//�洢����ʧ��
	Q.front = Q.rear = 0;
	PrintSqQueue(Q);
	return OK;
}

int QueueLength(SqQueue Q)
	//����Q��Ԫ�ظ����������еĳ���
{
	return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}

Status EnQueue(SqQueue &Q, QElemType e)
	//����Ԫ��eΪQ���µĶ�βԪ��
{
	if((Q.rear + 1) % MAXQSIZE == Q.front)	//������
		return ERROR;
	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1) % MAXQSIZE;
	PrintSqQueue(Q);
	return OK;
}

Status DeQueue(SqQueue &Q,QElemType &e)
	//�����в��գ���ɾ��Q�Ķ�ͷԪ�أ���e������ֵ��������OK
	//���򷵻�ERROR
{
	if(Q.front == Q.rear)
		return ERROR;
	e = Q.base[Q.front];
	Q.front = (Q.front+1) % MAXQSIZE;
	PrintSqQueue(Q);
	return OK;
}

void PrintSqQueue(SqQueue Q)
{
	int i;
	for(i = 0; i < MAXQSIZE; ++i)
	{
		printf("%2c  ",Q.base[i]);
	}
	printf("  len = %d\n",QueueLength(Q));
	for(i = 0; i < MAXQSIZE; ++i)
	{
		if(i == Q.front && i == Q.rear)
			printf("||%1d ",Q.front);
		else if(i == Q.front)
			printf("|f%1d ",Q.front);
		else if(i == Q.rear)
			printf("%1dr| ",Q.rear);
		else
			printf("    ");
	}
	printf("\n");
}


int main(void)
{
	SqQueue Q;
	int i;	char e;
	InitQueue(Q);
	for(i = 0; i < 7; ++i)
		if(!EnQueue(Q,'A'+i))
			printf("����������\n");
	DeQueue(Q,e);
	DeQueue(Q,e);
	for( ;i < 11; ++i)
		if(!EnQueue(Q,'A' + i))
			printf("����������\n");
	for(i = 0; i < 7; ++i)
		if(!DeQueue(Q,e))
			printf("�����ѿգ�\n");




	return 0;
}
