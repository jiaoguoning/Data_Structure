#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0

typedef int Status;
typedef int ElemType;

typedef struct Node
{
	ElemType data;
	struct Node * Next;		//��������struct
}LNode,*LinkList;

Status Init(LinkList *pL)
{
	*pL = NULL;
	return OK;
}

Status GetElemt_L(LinkList L,int i,ElemType *e)
	//�����ǽ��еĲ���Ҫ���У�д����ʱ���������û��ַ
{
	LinkList p = L;	//ָ���j�����
	int j = 1;				//�ӵ�һ����ʼ������
	while ( p && j < i )	//p��Ϊ����j < i
	{
		p = p->Next;
		++j;
	}						//pΪ�գ�˵������ѭ��������Ҳû�е���i�����   j==i
	if (!p || j > i)		//��Ϊ�˴���i   û�����ж�   ��� i==0  �� ����  ��������
							//���� i == j == 1 ���������ѭ������  ����
	{
		return ERROR;
	}
	*e = p->data;			//ͨ��Ѱַ�ı��� �õ�ַ�ڴ���Ԫ�ص�ֵ
	return OK;
}
//�����п����� *L   Ҳ������&L������ͷ���Ļ�������L
Status ListInsert_L(LinkList &L,int i,ElemType e)	//�����޸�Ӧ�ò��� p = *L����
													//����дû�����⣬��Ϊpָ��ǰ�ڵ㣬�����޸�ֵ
							//ͷ����next����ܻ�ı䣬��˴���ͷָ��ĵ�ַ
{
	LinkList p = L;
	int j = 1;				//��Ϊ����Ѱ�ҵ��ǲ������ǰ������˴�ͷ��㿪ʼ
	LinkList s;
	
	while (p && j < i - 1)	//Ѱ�ҵ�i-1�����
	{
		p = p->Next;
		++j;
	}	
	if(i == 1)
	{
		s = (LinkList)malloc(sizeof(LNode));
		s->data = e;
		s->Next = L;
		L = s;		
		return OK;
	}
	if (!p || j > i - 1)
	{
		return ERROR;
	}
	s = (LinkList)malloc(sizeof(LNode));
	s->data = e;
	s->Next = p->Next;
	p->Next = s;				//����������������һ��λ�����⣻���ǵڶ���һ��Ҫ�ڵ�����ǰ��
	return OK;
}

void PrintList(LinkList L)
{
	Node * p = L;
	while ( p != NULL)
	{
		printf("%d ", p->data);
		p = p->Next;
	}
	printf("\n");
}

int main(void)
{
	LinkList L1;	int e;
	Init(&L1);
	ListInsert_L(L1 , 1, 11);
	PrintList(L1 );
	ListInsert_L(L1 , 1, 22);
	ListInsert_L(L1 , 1, 33);
	PrintList(L1 );
	ListInsert_L(L1 , 1, 44);
	PrintList(L1 );
	
	

	return 0;
}

