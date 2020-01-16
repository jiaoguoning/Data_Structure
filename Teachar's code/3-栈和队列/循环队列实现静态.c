//编程：假设以数组Q[m]存放循环队列中的元素，同时以rear和length分别指示队列中的队尾
//位置和队列中所含元素的个数，试给出该循环队列的队空条件和队满条件，并写出相应的初始
//化、插入、删除元素的操作  。
#include <stdio.h>
#define QElemType int
#define Status int
#define m 10

typedef struct{
	QElemType Q[m];
	int length;
	int rear;
}SqQueue;

Status InitQueue(SqQueue *Sq)
//构造一个空队列Q
{
	int i = 0;
	for(i = 0;i < m;i++)
	{
		Sq->Q[i] = i;
	}
	Sq->length = Sq->rear = 0;
	return 1;
}
int QueueLength(SqQueue Sq)
//返回Q的元素个数，即队列长度
{
	return Sq.length;
}
Status EnQueue(SqQueue *Sq,QElemType e)
//插入元素e为Q的新队列元素
{
	if(Sq->length == m)
	{
		printf("队列已满，无法添加%d！\n",e);
		return 0;//队列满
	}
	Sq->Q[Sq->rear] = e;
	Sq->rear = (Sq->rear + 1) % m;
	Sq->length = (Sq->length + 1);
	printf("%d已成功入队！\n",e);
	return 1;
}
Status DeQueue(SqQueue *Sq,QElemType *e)
//若队列不空，则删除Q的队头元素，用e返回其值，并返回OK
//否则返回ERROR
{
	if (Sq->length == 0)
	{
		printf("队列长度为0,不能删除。\n");
		return 0;
	}
	int front = (Sq->rear - Sq->length + m) % m;
	e = Sq->Q[front];
	Sq->length--;
	printf("%d已成功出队！\n",e);
	return 1;
}

Status TraQueue(SqQueue Sq)
//遍历输出队列的每个元素
{
	int i = 0,j = 0;
	if (Sq.length == 0) 
	{
		printf("队列长度为0!\n");
		return 0;
	}
	int front = (Sq.rear - Sq.length + m) % m;
	printf("队列长度为%d其元素如下：\n",Sq.length);
	for(i = front;j < Sq.length; i++)
	{
		if(i == m) i = 0;
		printf("%d	",Sq.Q[i]);
		j++;
	}
	printf("\n");
	return 1;
}

int main(void)
{
	SqQueue Squeue;
	int e = -1;
	InitQueue(&Squeue);
	DeQueue(&Squeue,&e);
	
	for(int i = 0;i < 10; i++)
	{
		EnQueue(&Squeue,i+10);
		EnQueue(&Squeue,i+20);
		TraQueue(Squeue);
		DeQueue(&Squeue,&e);
		TraQueue(Squeue);
	}
	printf("队列最终结果如下：\n");
	TraQueue(Squeue);
	return 0;
}





