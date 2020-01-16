#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0

typedef int Status;
typedef int ElemType;

typedef struct Node
{
	ElemType data;
	struct Node * Next;		//不能少了struct
}LNode,*LinkList;

Status Init(LinkList *pL)
{
	*pL = NULL;
	return OK;
}

Status GetElemt_L(LinkList L,int i,ElemType *e)
	//当我们进行的操作要进行，写操作时，传递引用或地址
{
	LinkList p = L;	//指向第j个结点
	int j = 1;				//从第一个开始往后找
	while ( p && j < i )	//p不为空且j < i
	{
		p = p->Next;
		++j;
	}						//p为空，说明链表循环结束，也没有到第i个结点   j==i
	if (!p || j > i)		//因为此处对i   没有做判断   如果 i==0  或 负数  条件成立
							//对于 i == j == 1 的情况则不用循环正好  返回
	{
		return ERROR;
	}
	*e = p->data;			//通过寻址改变了 该地址内存中元素的值
	return OK;
}
//链表中可以是 *L   也可以是&L，不带头结点的话不能是L
Status ListInsert_L(LinkList &L,int i,ElemType e)	//这样修改应该不对 p = *L出错
													//这样写没有问题，因为p指向当前节点，可以修改值
							//头结点的next域可能会改变，因此传递头指针的地址
{
	LinkList p = L;
	int j = 1;				//因为我们寻找的是插入结点的前驱，因此从头结点开始
	LinkList s;
	
	while (p && j < i - 1)	//寻找第i-1个结点
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
	p->Next = s;				//对于以上三步：第一步位置任意；但是第二步一定要在第三步前面
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

