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


//算法2.10.0
//链表中既可以传递L，也可以是 *L   也可以是&L
Status ListDelete_L(LinkList &L,int i,ElemType &e)
{
    LinkList p = L;
    LinkList q;
    int j = 0;
    while (p->next && j < i-1){	//找到删除结点的前驱，并且保证这个前驱结点Next域不为空
        //因为如果前驱结点的Next域如果是空，无法完成删除操作
        p = p->next;
        ++j;
    }
    if (!(p->next) || j > i-1)
        return ERROR;
    q = p->next;
    p->next = q->next;
    e = q->data;
    free(q);
    return OK;
}

//算法2.11.0 这里L可以是传递引用&L，也可以是传递地址*L，但是不能是简单L
void CreateList_L(LinkList &L,int n){
    // 逆位序输入n个元素的值(11,22,...,nn)，建立带表头结点的单链线性表L 
    // 头插法
    LinkList p;
    int i; ElemType data = 11;
    L = (LinkList)malloc(sizeof(LNode));
    L->next = NULL;              // 先建立一个带头结点的单链表
    for (i = n; i > 0; --i) {
        p = (LinkList)malloc(sizeof(LNode));  // 生成新结点
        p->data = data;               // 改为一个随机生成的数字
        p->next = L->next;    L->next = p;    // 插入到表头
        data += 11;
    }
} // CreateList_L


//算法2.11.1    尾插法
void CreateList_L1(LinkList &L,int n){
    // 顺位序输入每个结点数据域是20的n个元素的值，建立带表头结点的单链线性表L 
    
    LinkList p, q;
    int i; ElemType data = 11;
    L = (LinkList)malloc(sizeof(LNode));
    L->next = NULL;              // 先建立一个带头结点的单链表
    q = L;
    for (i = n; i > 0; --i) {
        p = (LinkList)malloc(sizeof(LNode));  // 生成新结点
        p->data = data;               // 插入data
        p->next = q->next;    q->next = p;    // 插入到表头
        q = p;
        data += 11;
    }
} // CreateList_L

//算法2.11.2 这里L可以是传递引用&L，也可以是传递地址*L，但是不能是简单L
void CreateList_L2(LinkList *L,int n){
    // 逆位序输入n个元素的值(11,22,...,nn)，建立带表头结点的单链线性表L 
    // 头插法
    LinkList p;
    int i; ElemType data = 11;
    *L = (LinkList)malloc(sizeof(LNode));
    (*L)->next = NULL;              // 先建立一个带头结点的单链表
    for (i = n; i > 0; --i) {
        p = (LinkList)malloc(sizeof(LNode));  // 生成新结点
        p->data = data;               // 改为一个随机生成的数字
        p->next = (*L)->next;    (*L)->next = p;    // 插入到表头
        data += 11;
    }
} // CreateList_L


//算法2.11.3 这里L可以是传递引用&L，也可以是传递地址*L，但是不能是简单L   ERROR!
void CreateList_L3(LinkList L,int n){
    // 逆位序输入n个元素的值(11,22,...,nn)，建立带表头结点的单链线性表L 
    // 头插法
    LinkList p;
    int i; ElemType data = 11;
    L = (LinkList)malloc(sizeof(LNode));
    L->next = NULL;              // 先建立一个带头结点的单链表
    for (i = n; i > 0; --i) {
        p = (LinkList)malloc(sizeof(LNode));  // 生成新结点
        p->data = data;               // 改为一个随机生成的数字
        p->next = L->next;    L->next = p;    // 插入到表头
        data += 11;
    }
} // CreateList_L

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


// 测试算法2.11
int main(void)
{
    LinkList L;
    ElemType e;
    InitList_L(L);
    CreateList_L3(L, 5);
    ListTraverse_L(L, visit);



    return 0;
}



