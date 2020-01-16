/***
*DynaLnkList.cpp - ��̬������˳���Ķ�̬��ʽ�洢ʵ��
*
*
*��Ŀ��ʵ��2-2 ���Ա�Ķ�̬��ʽ�洢ʵ��
*
*�༶��
*
*������
*
*ѧ�ţ�
*	
****/

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <assert.h>
#include "DynaLnkList.h"

/*------------------------------------------------------------
����Ŀ�ģ�	��ʼ������
��ʼ������	��
���������	����һ���յ����Ա�
����������
		LinkList *L	����ʼ�������Ա�
����ֵ��
		bool		�����Ƿ�ɹ�
------------------------------------------------------------*/
bool InitList(LinkList *L)
{
	*L = (LinkList)malloc(sizeof(LNode));
	if(!(*L))
		return false;
	(*L)->next = NULL;
	return true;
}

/*------------------------------------------------------------
����Ŀ�ģ�	��������
��ʼ������	���Ա�L�Ѵ���
���������	�������Ա�L
����������
		LinkList *L	�����ٵ����Ա�
����ֵ��
		��
------------------------------------------------------------*/
void DestroyList(LinkList *L)
{
	LinkList q ,p = *L;
	while (p)
	{
		q = p->next;
		free(p);
		p = q;
	}
	*L = NULL;
}

/*------------------------------------------------------------
����Ŀ�ģ�	��������
��ʼ������	���Ա�L�Ѵ���
���������	���ζ�L��ÿ��Ԫ�ص��ú���fp
����������
		LinkList L		���Ա�L
		void (*fp)()	����ÿ������Ԫ�صĺ���ָ��
����ֵ��
		��
------------------------------------------------------------*/
void ListTraverse(LinkList L, void (*fp)(ElemType))
{
	LinkList p = L->next;
	while (p)
	{
		fp(p->data);
		p = p->next;
	}

}



/*------------------------------------------------------------
����Ŀ�ģ�	�������ָ��λ�ò����㣬����λ��i��ʾ�ڵ�i��
			Ԫ��֮ǰ����
��ʼ������	���Ա�L�Ѵ��ڣ�1<=i<=ListLength(L) + 1
���������	��L�е�i��λ��֮ǰ�����µ�����Ԫ��e��L�ĳ��ȼ�1
����������
		LinkList L	���Ա�L
		int i		����λ��
		ElemType e	�����������Ԫ��
����ֵ��
		bool		�����Ƿ�ɹ�
------------------------------------------------------------*/
//��ͷ���ĵ������������У�ͷָ�벻��Ҫ�޸�,��˴��ݱ�������
bool ListInsert(LinkList L, int i, ElemType e)
{
	LinkList p = L;
	LinkList s;
	int j = 0;
	while (p && j < i-1)
	{
		p = p->next;
		++j;
	}
	if(!p || j > i-1)
		return false;
	s = (LinkList)malloc(sizeof(LNode));
	if(!s)
		return false;
	s->data = e;
	s->next = p->next;
	p->next = s;
	return true;
}

/*------------------------------------------------------------
����Ŀ�ģ�	ɾ������ĵ�i�����
��ʼ������	���Ա�L�Ѵ����ҷǿգ�1<=i<=ListLength(L)
���������	ɾ��L�ĵ�i������Ԫ�أ�����e������ֵ��L�ĳ��ȼ�1
����������
		LinkList L	���Ա�L
		int i		ɾ��λ��
		ElemType *e	��ɾ��������Ԫ��ֵ
����ֵ��
		bool		�����Ƿ�ɹ�
------------------------------------------------------------*/
//��ͷ���ĵ�����ɾ�������У�ͷָ�벻��Ҫ�޸�,��˴��ݱ�������
bool ListDelete(LinkList L, int i, ElemType *e)
{
	int j = 0;
	LinkList p = L;
	LinkList q;
	while(p->next && j < i-1)
	{
		p = p->next;
		++j;
	}
	if(!(p->next) || j > i-1)
		return false;
	
	q = p->next;
	p->next = p->next->next;
	*e = q->data;
	free(q);

	return true;
}

/*------------------------------------------------------------
����Ŀ�ģ�	�õ�����ĳ���
��ʼ������	���Ա�L�Ѵ���
���������	����L������Ԫ�صĸ���
����������
		LinkList L	���Ա�L
����ֵ��
		int			����Ԫ�صĸ���
------------------------------------------------------------*/
int ListLength(LinkList L)
{
	LinkList p = L->next;
	int j = 1;
	while (p->next)
	{
		p = p->next;
		++j;
	}
	return j;
}


/*------------------------------------------------------------
����Ŀ�ģ�	�����Ա���Ԫ������
��ʼ������	���Ա�L�Ѵ����ҷǿ�
���������	ԭ�����Ա���Ԫ�����д��������е����Ա���
����������
		LinkList L	���Ա�L
����ֵ��
		bool		�����Ƿ�ɹ�
------------------------------------------------------------*/
bool Inverse(LinkList L)
{
	LinkList cur = L, rear = L->next, front = NULL, first = L->next;
	
    while (rear != NULL)
    {
        cur->next = front;
        front = cur;
        cur = rear;
        rear = cur->next;
    }
    cur->next = front; 
	first->next = NULL;
	L->next = cur;
	return true;
}