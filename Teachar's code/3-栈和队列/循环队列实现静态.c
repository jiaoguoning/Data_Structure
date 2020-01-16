//��̣�����������Q[m]���ѭ�������е�Ԫ�أ�ͬʱ��rear��length�ֱ�ָʾ�����еĶ�β
//λ�úͶ���������Ԫ�صĸ������Ը�����ѭ�����еĶӿ������Ͷ�����������д����Ӧ�ĳ�ʼ
//�������롢ɾ��Ԫ�صĲ���  ��
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
//����һ���ն���Q
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
//����Q��Ԫ�ظ����������г���
{
	return Sq.length;
}
Status EnQueue(SqQueue *Sq,QElemType e)
//����Ԫ��eΪQ���¶���Ԫ��
{
	if(Sq->length == m)
	{
		printf("�����������޷����%d��\n",e);
		return 0;//������
	}
	Sq->Q[Sq->rear] = e;
	Sq->rear = (Sq->rear + 1) % m;
	Sq->length = (Sq->length + 1);
	printf("%d�ѳɹ���ӣ�\n",e);
	return 1;
}
Status DeQueue(SqQueue *Sq,QElemType *e)
//�����в��գ���ɾ��Q�Ķ�ͷԪ�أ���e������ֵ��������OK
//���򷵻�ERROR
{
	if (Sq->length == 0)
	{
		printf("���г���Ϊ0,����ɾ����\n");
		return 0;
	}
	int front = (Sq->rear - Sq->length + m) % m;
	e = Sq->Q[front];
	Sq->length--;
	printf("%d�ѳɹ����ӣ�\n",e);
	return 1;
}

Status TraQueue(SqQueue Sq)
//����������е�ÿ��Ԫ��
{
	int i = 0,j = 0;
	if (Sq.length == 0) 
	{
		printf("���г���Ϊ0!\n");
		return 0;
	}
	int front = (Sq.rear - Sq.length + m) % m;
	printf("���г���Ϊ%d��Ԫ�����£�\n",Sq.length);
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
	printf("�������ս�����£�\n");
	TraQueue(Squeue);
	return 0;
}





