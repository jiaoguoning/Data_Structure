#include <stdio.h>
#include <stdlib.h>

#define Status      int
#define OVERFLOW    -2
#define OK          1
#define ERROR       0

//------------- 循环队列————队列的动态顺序存储结构 -------------
#define MAXQSIZE    6	//最大队列长度
#define QElemType   char

typedef struct
{
	QElemType *base;	//初始化的动态分配存储空间
	int front;			//头指针，若队列不空，指向队列头元素
	int rear;			//若队列不空，指向队列元素的下一个元素
}SqQueue;

//------------- 循环队列基本操作 ---------------
// 初始化
Status InitQueue(SqQueue *Q)
	//构造一个空队列Q
{
	(*Q).base = (QElemType *)malloc(MAXQSIZE * sizeof(QElemType));
	if(!(*Q).base)
		exit(OVERFLOW);	//存储分配失败
	(*Q).front = (*Q).rear = 0;

	return OK;
}

// 求元素个数
int QueueLength(SqQueue Q)
	//返回Q的元素个数，即队列的长度
{
	return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}

// 入队
Status EnQueue(SqQueue *Q, QElemType e)
	//插入元素e为Q的新的队尾元素
{
	if(((*Q).rear + 1) % MAXQSIZE == (*Q).front)	//队列满
		return ERROR;
	(*Q).base[(*Q).rear] = e;
	(*Q).rear = ((*Q).rear + 1) % MAXQSIZE;

	return OK;
}

// 出队
Status DeQueue(SqQueue *Q,QElemType *e)
	//若队列不空，则删除Q的对头元素，用e返回其值，并返回OK
	//否则返回ERROR
{
	if((*Q).front == (*Q).rear)
		return ERROR;
	*e = (*Q).base[(*Q).front];
	(*Q).front = ((*Q).front+1) % MAXQSIZE;

	return OK;
}

// 打印循环队列
void PrintSqQueue(SqQueue Q)
{
    int i;
    for (i = Q.front; i != Q.rear; i = (i + 1) % MAXQSIZE)
        printf("%c ", Q.base[i]);
    printf("\n");
}

Status DestroyQueue(SqQueue *Q){
    free((*Q).base);
    (*Q).base = NULL;
    (*Q).front = (*Q).rear = 0;
    return OK;
}




int main(void)
{
    SqQueue Q;
    int i;	
    QElemType e = 'A';
    InitQueue(&Q);
    for (i = 0; i < 7; i++){
        if(!EnQueue(&Q, e++))
            printf("队列已满, 不能入队\n");
    }
    PrintSqQueue(Q);

    DeQueue(&Q, &e);
    PrintSqQueue(Q);
    e = 'w';
    EnQueue(&Q, e );
    PrintSqQueue(Q);
    DeQueue(&Q, &e);
    DeQueue(&Q, &e);
    PrintSqQueue(Q);
    e = 'x';
    EnQueue(&Q, e++ );
    EnQueue(&Q, e++ );
    EnQueue(&Q, e++ );
    PrintSqQueue(Q);
    return 0;
}
