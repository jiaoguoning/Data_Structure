#include <stdio.h>
#include <stdlib.h>
#define ElemType    int
#define Status      int
#define ERROR       0
#define OK          1

// ---------  双向循环链表  -------- //
typedef struct DuLNode
{
	ElemType data;
	struct DuLNode *prior;
	struct DuLNode *next;
}DuLNode, *DuLinkList;

Status InitDuLinkList(DuLinkList &L)
{
	L = (DuLinkList)malloc(sizeof(DuLNode));
	if(!L)
		return ERROR;
	L->next = L;
	L->prior = L;
	return OK;
}

DuLinkList GetElemP_DuL(DuLinkList L, int i)
{
	DuLinkList p = L->next;
	int j = 1;
	while ( p && j < i)
	{
		p = p->next;
		++j;
	}
	return p;
}


// 算法2.18 
Status ListInsert(DuLinkList &L, int i, ElemType e)
	//在带头结点的双链循环线性表L中第i个位置之前插入元素e
	//i的合法值为 1 ≤ i ≤ 表长 + 1。
{
	DuLinkList p, s;
	if(!(p = GetElemP_DuL(L, i)))
		return ERROR;

	if(!(s = (DuLinkList)malloc(sizeof(DuLNode))))
		return ERROR;

	s->data = e;			
    
    s->prior = p->prior;
	p->prior->next = s;		
    s->next = p;
	p->prior = s;

	return OK;
}


//  算法2.19
Status ListDelete(DuLinkList &L, int i, ElemType &e)
	//删除带头结点的双链循环线性表L的第i个元素，i的合法值为 1 ≤ i ≤ 表长
{
	DuLinkList p;
	if(!(p = GetElemP_DuL(L , i)))
		return ERROR;
	e = p->data;
	p->prior->next = p->next;    // 此行和下面一行等效，可以交换次序
	p->next->prior = p->prior;
	free(p);

	return OK;
}

void PrintData(DuLinkList DL)
{
	DuLinkList p = DL->next;
	while (p != DL)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}


int main(void)
{
	DuLinkList DL;
	ElemType e;
    int i;
	InitDuLinkList(DL);
	for (i = 1; i <= 7; i++)
		ListInsert(DL, i , i * 11);
	PrintData(DL);
	ListDelete(DL, 2, e);
	PrintData(DL);



	return 0;
}



