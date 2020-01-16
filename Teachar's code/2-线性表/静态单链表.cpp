#include <stdio.h>
#define MAXSIZE 10
#define ElemType char
#define Status  int
#define ERROR 0
#define OK  1

typedef struct
{
	ElemType data;
	int cur;
}component, SLinkList[MAXSIZE];

//1. ����һ��������MAXSIZE�����ľ�̬����
//2. ÿ��������һ���������һ���α���
//3. Ϊ�˺������̬��������Ԫ�أ�����һ��������������
//   ����ͷ���ΪL[0],����ͷ���ΪL[MAXSIZE-1]���α�cur=0Ϊ��
//4. ��ʼ��ʱ��������ͷ���Ϊ�գ�����Ԫ����ɱ�������
//   �����������һ��Ԫ����Ϊ�ա�

//˼·�������Ͼ�̬�����ǽ�SLinkList����ֳ�����������������ͱ�������
//���������ͷ���������ռ�����һ�����(length-1���±�)
//��������ͷ���������ռ�ĵ�һ�����(0���±�)



int LocateElem_SL(SLinkList &SL, ElemType e)
	//�ھ�̬�������Ա���ҵ�1��ֵΪe��Ԫ�ء�
	//���ҵ����򷵻�����L�е�λ�򣬷��򷵻�0.

{
	int i = SL[MAXSIZE-1].cur;			//��������������һ�������±�
	while (i && SL[i].data != e)	//
		i = SL[i].cur;
	return i;
}


void InitSpace_SL(SLinkList &SL)
	//��SL�и���������һ����������SL[0].curΪ��������ͷָ�룬
	//SL[MAXSIZE-1].cur��ʾ���������ͷָ��
	//SL[MAXSIZE-2].cur��ʾ�������������β;
{
	int i;
	SL[MAXSIZE-1].cur = 0;				//��������ͷ���Ϊ��
	for(i = 0; i < MAXSIZE - 2; ++i)	//���������ɱ�������
		SL[i].cur = i + 1;
	SL[MAXSIZE-2].cur = 0;				//�����������һ��Ԫ���ÿ�
}

int Malloc_SL(SLinkList &SL)
	//�����ÿռ�����ǿգ��򷵻ط���Ľ���±꣬���򷵻�0
{
	int i = SL[0].cur;
	if(i)						//���i��Ϊ0��˵�����пռ�
		SL[0].cur = SL[i].cur;
	return i;
}

void Free_SL(SLinkList &SL, int k)
	//���±�Ϊk�Ŀ��н����յ���������
{
	SL[k].cur = SL[0].cur;
	SL[0].cur = k;
}

Status ListInsert_SL(SLinkList &SL,int i,ElemType e)
{
	int s;
	int p = MAXSIZE - 1 ;
	int j = 0;
	while (p && j < i-1)
	{
		p = SL[p].cur;
		++j;
	}
	if(!p || j > i - 1)
		return ERROR;

	s = Malloc_SL(SL);
	if(!s)
	{
		printf("�ռ��Ѿ����꣡\n");
		return ERROR;
	}
	SL[s].data = e;
	SL[s].cur = SL[p].cur;
	SL[p].cur = s;
	return OK;
}

int ListLength_SL(SLinkList &L) 
{ 
	int j = 0;
	int i = L[MAXSIZE - 1].cur; 
	while(i != 0) 
	{ 
		i = L[i].cur;
		++j; 
	} 
	return j; 
}

Status ListDelete_SL(SLinkList &SL, int i,ElemType &e)  
{     
	int q = 0;
	int p = MAXSIZE - 1;
	int j = 0;
	while (SL[p].cur && j < i - 1)
	{
		p = SL[p].cur;
		++j;
	}
	if(!SL[p].cur || j > i - 1)
		return ERROR;
	q = SL[p].cur;
	SL[p].cur = SL[q].cur;
	e = SL[q].data;
	Free_SL(SL, q);
	return OK;  
}

void ListPrint_SL(SLinkList SL)
{
	int p = SL[MAXSIZE-1].cur;
	while (p)
	{
		printf("%c  ", SL[p].data);
		p = SL[p].cur;
	}
	printf("\n");
}



int main(void)
{
	SLinkList SL;
	int i;
	char e;
	InitSpace_SL(SL);
	for (i = 0; i < 12; i++)
	{
		ListInsert_SL(SL, 1, 'A' + i);
		e = ListLength_SL(SL);
	}
	printf("����Ϊ�� %d\n",e);
	ListPrint_SL(SL);
	
	for (i = 0; i < 2; i++)
	{
		ListDelete_SL(SL, i+1, e);
		printf("ɾ����%d����Ϊ�� \n", i+1);
		ListPrint_SL(SL);
	}
	printf("��A��ͬ�Ĵ����SL�����±��ǣ�%d \n",LocateElem_SL(SL , 'A'));

	return 0;
}

