#include <stdio.h>
#include <stdlib.h>
#define Status          int //状态
#define OVERFLOW        -1  //溢出
#define OK              1   //正确
#define ERROR           0   //错误

typedef int ElemType;

typedef struct LNode
{
	ElemType data;
	struct LNode *next;		//不能少了struct
}LNode, *LinkList;


// InitList_L：传递引用初始化
Status InitList_L(LinkList &L)
{
	L = (LinkList)malloc(sizeof(LNode));
	L->data = 0;
	L->next = NULL;
	return OK;
}


// InitList_L1：传递地址初始化
Status InitList_L1(LinkList *L)
{
	(*L) = (LinkList)malloc(sizeof(LNode));
	(*L)->data = 0;
	(*L)->next = NULL;
	return OK;
}

// InitList_L2：简单值传递初始化（ERROR！）
Status InitList_L2(LinkList L)
{
	L = (LinkList)malloc(sizeof(LNode));
	L->data = 0;
	L->next = NULL;
	return OK;
}

// InitList_L3：不带头结点初始化-传引用
Status InitList_L3(LinkList &L)
{
	L = NULL;
	return OK;
}

// InitList_L4：不带头结点初始化-传地址
Status InitList_L4(LinkList *L)
{
	*L = NULL;
	return OK;
}

// InitList_L5：不带头结点初始化-简单值传递
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

