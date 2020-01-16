/***
*DynaLnkList.cpp - 动态链表，即顺序表的动态链式存储实现
*
*
*题目：实验2-2 线性表的动态链式存储实现
*
*班级：
*
*姓名：
*
*学号：
*	
****/

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <assert.h>
#include "DynaLnkList.h"

/*------------------------------------------------------------
操作目的：	初始化链表
初始条件：	无
操作结果：	构造一个空的线性表
函数参数：
		LinkList *L	待初始化的线性表
返回值：
		bool		操作是否成功
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
操作目的：	销毁链表
初始条件：	线性表L已存在
操作结果：	销毁线性表L
函数参数：
		LinkList *L	待销毁的线性表
返回值：
		无
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
操作目的：	遍历链表
初始条件：	线性表L已存在
操作结果：	依次对L的每个元素调用函数fp
函数参数：
		LinkList L		线性表L
		void (*fp)()	访问每个数据元素的函数指针
返回值：
		无
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
操作目的：	在链表的指定位置插入结点，插入位置i表示在第i个
			元素之前插入
初始条件：	线性表L已存在，1<=i<=ListLength(L) + 1
操作结果：	在L中第i个位置之前插入新的数据元素e，L的长度加1
函数参数：
		LinkList L	线性表L
		int i		插入位置
		ElemType e	待插入的数据元素
返回值：
		bool		操作是否成功
------------------------------------------------------------*/
//带头结点的单链表插入过程中，头指针不需要修改,因此传递变量即可
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
操作目的：	删除链表的第i个结点
初始条件：	线性表L已存在且非空，1<=i<=ListLength(L)
操作结果：	删除L的第i个数据元素，并用e返回其值，L的长度减1
函数参数：
		LinkList L	线性表L
		int i		删除位置
		ElemType *e	被删除的数据元素值
返回值：
		bool		操作是否成功
------------------------------------------------------------*/
//带头结点的单链表删除过程中，头指针不需要修改,因此传递变量即可
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
操作目的：	得到链表的长度
初始条件：	线性表L已存在
操作结果：	返回L中数据元素的个数
函数参数：
		LinkList L	线性表L
返回值：
		int			数据元素的个数
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
操作目的：	将线性表中元素逆置
初始条件：	线性表L已存在且非空
操作结果：	原来线性表中元素排列次序反向排列到线性表中
函数参数：
		LinkList L	线性表L
返回值：
		bool		操作是否成功
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