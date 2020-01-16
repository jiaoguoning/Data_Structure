#include <stdio.h>

#include <stdlib.h>
#define Status int
#define OVERFLOW -1
#define OK 1
#define ERROR 0

//------------- 循环队列————队列的顺序存储结构 -------------
#define MAXQSIZE 6	//最大队列长度
#define QElemType char

typedef struct
{
	QElemType *base;	//初始化的动态分配存储空间
	int front;			//头指针，若队列不空，指向队列头元素
	int rear;			//若队列不空，指向队列元素的下一个元素
}SqQueue;
void PrintSqQueue(SqQueue Q);
//------------- 循环队列基本操作 ---------------
Status InitQueue(SqQueue &Q)
	//构造一个空队列Q
{
	Q.base = (QElemType *)malloc(MAXQSIZE * sizeof(QElemType));
	if(!Q.base)
		exit(OVERFLOW);	//存储分配失败
	Q.front = Q.rear = 0;
	PrintSqQueue(Q);
	return OK;
}

int QueueLength(SqQueue Q)
	//返回Q的元素个数，即队列的长度
{
	return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}

Status EnQueue(SqQueue &Q, QElemType e)
	//插入元素e为Q的新的队尾元素
{
	if((Q.rear + 1) % MAXQSIZE == Q.front)	//队列满
		return ERROR;
	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1) % MAXQSIZE;
	PrintSqQueue(Q);
	return OK;
}

Status DeQueue(SqQueue &Q,QElemType &e)
	//若队列不空，则删除Q的对头元素，用e返回其值，并返回OK
	//否则返回ERROR
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
			printf("队列已满！\n");
	DeQueue(Q,e);
	DeQueue(Q,e);
	for( ;i < 11; ++i)
		if(!EnQueue(Q,'A' + i))
			printf("队列已满！\n");
	for(i = 0; i < 7; ++i)
		if(!DeQueue(Q,e))
			printf("队列已空！\n");




	return 0;
}
