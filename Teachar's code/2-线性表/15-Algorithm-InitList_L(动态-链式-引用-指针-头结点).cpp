#include <stdio.h>
#include <stdlib.h>
#define Status          int //״̬
#define OVERFLOW        -1  //���
#define OK              1   //��ȷ
#define ERROR           0   //����

typedef int ElemType;

typedef struct LNode
{
	ElemType data;
	struct LNode *next;		//��������struct
}LNode, *LinkList;


// InitList_L���������ó�ʼ��
Status InitList_L(LinkList &L)
{
	L = (LinkList)malloc(sizeof(LNode));
	L->data = 0;
	L->next = NULL;
	return OK;
}


// InitList_L1�����ݵ�ַ��ʼ��
Status InitList_L1(LinkList *L)
{
	(*L) = (LinkList)malloc(sizeof(LNode));
	(*L)->data = 0;
	(*L)->next = NULL;
	return OK;
}

// InitList_L2����ֵ���ݳ�ʼ����ERROR����
Status InitList_L2(LinkList L)
{
	L = (LinkList)malloc(sizeof(LNode));
	L->data = 0;
	L->next = NULL;
	return OK;
}

// InitList_L3������ͷ����ʼ��-������
Status InitList_L3(LinkList &L)
{
	L = NULL;
	return OK;
}

// InitList_L4������ͷ����ʼ��-����ַ
Status InitList_L4(LinkList *L)
{
	*L = NULL;
	return OK;
}

// InitList_L5������ͷ����ʼ��-��ֵ����
Status InitList_L5(LinkList L)
{
	L = NULL;
	return OK;
}


int main(void)
{
	LinkList L;
	/*InitList_L(L);
    printf("L->data = %d\n", L->data);
    printf("L->next = %p\n", L->next);*/

    InitList_L5(L);
    printf("L = %p\n", L);
    



	return 0;
}

