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


// 初始化：带头结点
Status InitList_L(LinkList &L)
{
	L = (LinkList)malloc(sizeof(LNode));
	L->data = 0;
	L->next = NULL;
	return OK;
}


// 算法2.8.0 引用型操作：不需要传递引用，也不需要传递指针
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


// 测试GetElem_L
int main(void)
{
    LinkList L;
    ElemType e;
    int i;
    InitList_L(L);
    printf("%d\n",ListInsert_L(L,1,11));
    printf("%d\n",ListInsert_L(L,2,22));
    printf("%d\n",ListInsert_L(L,3,33));
    printf("%d\n",ListInsert_L(L,4,44));
    for(i = 1; i <= 4; ++i)
    {
        GetElemt_L(L ,i ,e);
        printf("第%d个元素是 %d\n",i , e);
    }

    return 0;
}

