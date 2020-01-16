#include <stdio.h>
#define MAXSIZE     10
#define ElemType    char
#define Status      int
#define ERROR       0
#define OK          1

typedef struct
{
    ElemType data;
    int cur;
}component, SLinkList[MAXSIZE];

typedef int LinkList;   //用下标指向每个结点的位置

SLinkList space;        // 备用链表space要么在全局区，要么在main函数中，

//1. 申请一个可容纳MAXSIZE个结点的静态链表
//2. 每个结点包括一个数据域和一个游标域
//3. 为了合理管理静态链表数据元素，设置一个备用链表，备用
//   链表头结点为L[0],备用链表尾结点为L[MAXSIZE-1]，游标cur=0为空
//4. 初始化时，所有元素组成备用链表，备用链表最后一个元素置为空。

//特点: 
//  1. space是备用链表，也是一个内存空间； 
//  2. 下标就是指针;
//  3. 头指针就是int类型的下标，可以用来给静态链表起名字。


//算法2.13 
int LocateElem_SL(LinkList &S, ElemType e)
    //在静态单链线性表查找第1个值为e的元素。
    //若找到，则返回它在L中的位序，否则返回0.
{
    LinkList p = space[S].cur;			    //存放着正用链表第一个结点的下标
    while (p && space[p].data != e)	
        p = space[p].cur;                   //类似于 p = p->next
    return p;
}

//算法2.14 
void InitSpace_SL(SLinkList &space)
    //将SL中各分量链成一个备用链表，space[0].cur为备用链表头指针，
{
    int i;
    for(i = 0; i < MAXSIZE - 1; ++i)	//其余链表构成备用链表
        space[i].cur = i + 1;
    space[MAXSIZE-1].cur = 0;		    //备用链表最后一个元素置空
}



// 算法2.15
int Malloc_SL(SLinkList &space)
    //若备用空间链表非空，则返回分配的结点下标，否则返回0
{
    int i = space[0].cur;
    if(i)						//如果i不为0，说明还有空间
        space[0].cur = space[i].cur;  //0->next = i->next
    return i;
}

// 算法2.16  
void Free_SL(SLinkList &space, LinkList k)
    //将下标为k的空闲结点回收到备用链表
{
    space[k].cur = space[0].cur; // k->next = 0->next
    space[0].cur = k;            // 0->next = k
}

Status InitLinkList_SL(LinkList &L)
{
    L = Malloc_SL(space);//创建S的头结点
    if(!L)
        return ERROR;
    space[L].cur = 0;   //既然将第i个结点给出去，那么就将它的Cur域置为0
                        //如果没这一步，创建头结点会出错
    return OK;
}

Status ListInsert_SL(LinkList &SL ,int i,ElemType e)
{
    LinkList p = SL, s = 0;
    int j = 0;
    while (p && j < i-1)
    {
        p = space[p].cur;
        ++j;
    }
    if(!p || j > i - 1)
        return ERROR;

    s = Malloc_SL(space);
    if(!s)
    {
        printf("空间已经用完！\n");
        return ERROR;
    }
    space[s].data = e;
    space[s].cur = space[p].cur;
    space[p].cur = s;
    return OK;
}

int ListLength_SL(LinkList &L) 
{ 
    int j = 0;
    LinkList p = space[L].cur;
    while(p != 0) 
    { 
        p = space[p].cur;
        ++j; 
    } 
    return j; 
}

Status ListDelete_SL(LinkList &SL, int i,ElemType &e)  
{     
    LinkList q = 0, p = SL;
    int j = 0;
    while (space[p].cur && j < i - 1)
    {
        p = space[p].cur;
        ++j;
    }
    if(!space[p].cur || j > i - 1)
        return ERROR;
    q = space[p].cur;
    space[p].cur = space[q].cur;
    e = space[q].data;
    Free_SL(space, q);
    return OK;  
}

void ListPrint_SL(LinkList SL)
{
    LinkList p = space[SL].cur;
    while (p)
    {
        printf("%c  ", space[p].data);
        p = space[p].cur;
    }
    printf("\n");
}



// 算法2.17   
void difference(SLinkList &space, LinkList &S) {  
    // 依次输入集合A和B的元素，在一维数组space中建立表示集合(A-B)∪(B-A)
    // 的静态链表, S为头指针。假设备用空间足够大，space[0].cur为头指针。
    int j, m, n;
    LinkList p, k, r, s = 0;
    ElemType dataA = 'a', dataB = 'c';
    InitSpace_SL(space);          // 初始化备用空间
    InitLinkList_SL(S);           // 生成S的头结点
    r = S;                        // r指向S的当前最后结点
    m = 4;                        // 输入A的元素个数 4
    n = 3;                        // 输入B的元素个数 3

    printf("集合A：");
    for (j = 1; j <= m; ++j) {      // 建立集合A的链表
        s = Malloc_SL(space);       // 分配结点
        space[s].data = dataA++;    // 输入A的元素值
        printf("%c ", space[s].data);   // 输出A的元素
        space[r].cur = s;  
        r = s;  // 插入到表尾       //r相当于一直指向链表S表尾的指针
    }
    space[r].cur = 0;             // 尾结点的指针为空
    printf("\n集合B：");
    for (j = 1; j <= n; ++j) {
        // 依次输入B的元素,若不在当前表中,则插入,否则删除
        printf("%c ", dataB);       // 输出B的元素
        p = S;   k = space[S].cur;  // k指向集合A中第一个结点
        while (k!=space[r].cur && space[k].data != dataB) {// 在当前表中查找
            p = k;    
            k = space[k].cur;
        }
        if (k == space[r].cur) {
            // 当前表中不存在该元素,插入在r所指结点之后，且r的位置不变
            s = Malloc_SL(space);
            space[s].data = dataB;
            space[s].cur = space[r].cur;
            space[r].cur = s;
        } else {                     // 该元素已在表中,删除之
            space[p].cur = space[k].cur;
            Free_SL(space, k);
            if (r == k)  
                r = p;      // 若删除的是尾元素，则需修改尾指针
        }
        ++dataB;
    }
    printf("\n");
} // difference


//测试2.17
int main(void)
{
    LinkList S;               // 可用链表S
    difference(space, S);

    printf("集合(A-B)∪(B-A)：");
    ListPrint_SL(S);

    return 0;
}



////测试2.14-2.16+Insert+Delete
//int main(void)
//{
//    LinkList S;               // 可用链表S
//    ElemType e = 'a';
//    int i = 0;
//    InitSpace_SL(space);
//    InitLinkList_SL(S);
//    ListInsert_SL(S, ++i, e++);
//    ListInsert_SL(S, ++i, e++);
//    ListInsert_SL(S, ++i, e++);
//    ListInsert_SL(S, ++i, e++);
//    ListInsert_SL(S, ++i, e++);
//    ListPrint_SL(S);
//    ListDelete_SL(S, 3, e);
//
//
//    ListPrint_SL(S);
//
//    i = ListLength_SL(S);
//    printf("%d\n",i );
//
//    return 0;
//}
