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

Status InitList_L(LinkList &L)
{
	L = (LinkList)malloc(sizeof(LNode));
	L->data = 0;
	L->next = NULL;
	return OK;
}


// 算法2.8.0
Status GetElemt_L(LinkList L,int i,ElemType &e)
	// L为带头结点的单链表的头指针
    // 当第i个元素存在时，其值赋给e并返回OK，否则返回ERROR
{
	LNode *p = L->next;	//指向第j个结点
	int j = 1;				//从第一个开始往后找
	while ( p && j < i ){	//p不为空且j < i
		p = p->next;
		++j;
	}						//p为空，说明链表循环结束，也没有到第i个结点   j==i
	if (!p || j > i){		//因为此处对i   没有做判断   如果 i==0  或 负数  条件成立
							//对于 i == j == 1 的情况则不用循环正好  返回
		return ERROR;
	}
	e = p->data;			//通过别名方式改变内存中元素的值
	return OK;
}


//算法2.9.0
//链表中既可以传递L，也可以是 *L   也可以是&L
Status ListInsert_L(LinkList &L,int i,ElemType e)	//这样修改应该不对 p = *L出错
													//这样写没有问题，因为p指向当前节点，可以修改值
							//头结点的next域可能会改变，因此传递头指针的地址
{
	LinkList p = L;
	int j = 0;				//因为我们寻找的是插入结点的前驱，因此从头结点开始
	LinkList s;
	while (p && j < i - 1){	//寻找第i-1个结点
		p = p->next;
		++j;
	}						
	if (!p || j > i - 1){
		return ERROR;
	}
	s = (LinkList)malloc(sizeof(LNode));
	s->data = e;
	s->next = p->next;
	p->next = s;				//对于以上三步：第一步位置任意；但是第二步一定要在第三步前面
	return OK;
}

//算法2.9.1
//链表中既可以传递L，也可以是 *L   也可以是&L
Status ListInsert_L1(LinkList L,int i,ElemType e)	//这样修改应该不对 p = *L出错
													//这样写没有问题，因为p指向当前节点，可以修改值
							//头结点的next域可能会改变，因此传递头指针的地址
{
	LinkList p = L;
	int j = 0;				//因为我们寻找的是插入结点的前驱，因此从头结点开始
	LinkList s;
	while (p && j < i - 1){	//寻找第i-1个结点
		p = p->next;
		++j;
	}						
	if (!p || j > i - 1){
		return ERROR;
	}
	s = (LinkList)malloc(sizeof(LNode));
	s->data = e;
	s->next = p->next;
	p->next = s;				//对于以上三步：第一步位置任意；但是第二步一定要在第三步前面
	return OK;
}

//算法2.9.2
//链表中既可以传递L，也可以是 *L   也可以是&L
Status ListInsert_L2(LinkList *L,int i,ElemType e)	//这样修改应该不对 p = *L出错
													//这样写没有问题，因为p指向当前节点，可以修改值
							//头结点的next域可能会改变，因此传递头指针的地址
{
	LinkList p = (*L);
	int j = 0;				//因为我们寻找的是插入结点的前驱，因此从头结点开始
	LinkList s;
	while (p && j < i - 1){	//寻找第i-1个结点
		p = p->next;
		++j;
	}						
	if (!p || j > i - 1){
		return ERROR;
	}
	s = (LinkList)malloc(sizeof(LNode));
	s->data = e;
	s->next = p->next;
	p->next = s;				//对于以上三步：第一步位置任意；但是第二步一定要在第三步前面
	return OK;
}


Status visit(ElemType e) {
    if(printf("%d   ", e))
        return OK;
    return ERROR;
}

Status visit1(ElemType e) {
    if(printf("%d\n", e))
        return OK;
    return ERROR;
}

// 遍历
Status ListTraverse_L(LinkList L, Status (*pvisit)(ElemType)) {
    LNode *p = L->next;
    while (p) {
        if(!pvisit(p->data))
            return ERROR;
        p = p->next;
    }
    printf("\n");
    return OK;
}


//测试Insert_L
int main(void)
{
	LinkList L;
    ElemType e;
    int i;
	InitList_L(L);
	ListInsert_L(L, 1, 11);
	ListInsert_L(L, 2, 22);
	ListInsert_L(L, 3, 33);
	ListInsert_L(L, 4, 44);
   ListInsert_L1(L, 5, 55);
	ListInsert_L1(L, 6, 66);
	ListInsert_L2(&L, 7, 77);
	ListInsert_L2(&L, 8, 88);
	ListTraverse_L( L, visit);

	return 0;
}

