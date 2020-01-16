#include <stdio.h>
#include <stdlib.h>

#define Status          int //状态
#define OVERFLOW        -1  //溢出
#define OK              1   //正确
#define ERROR           0   //错误


//----- 线性表的动态分配顺序存储结构 -----
#define LIST_INIT_SIZE  100 //线性表存储空间的初始分配量
#define LISTINCREMENT   10  //线性表存储空间的分配增量

#define ElemType int        //ElemType设置为int类型
typedef struct
{
	ElemType * elem;    //存储空间基址
	int length;         //当前长度
	int listsize;       //当前分配的存储容量大小：listsize * sizeof(ElemType)字节
}SqList;

//算法2.3
Status InitList_Sq(SqList &L){
    // 构造一个空的线性表
	L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if(!L.elem)
		exit(OVERFLOW);         //存储分配失败
	L.length = 0;               //空表长度为0
	L.listsize = LIST_INIT_SIZE;//初始存储容量
	return OK;
}//InitList_Sq

//算法2.4
Status ListInsert_Sq(SqList &L, int i,ElemType e){
    //在顺序线性表L中第i个位置之前插入新的元素e，
    //i的合法值为 [1, ListLength_Sq(L)+1]
	ElemType *p, *q, *newbase;
	if(i < 1 || i > L.length + 1)   //i值合法性
	{
		printf("i不合法，不能插入！\n");
		return ERROR;
	}
	if(L.length >= L.listsize)      //判断是否要追加空间
	{
		newbase = (ElemType *)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
		if(!newbase)                //存储分配失败
			exit(OVERFLOW);         	//return ERROR;都可以
		L.elem = newbase;           //获取新基址
		L.listsize += LISTINCREMENT;//增加存储容量
	}
	q = &L.elem[i-1];
	for(p = &(L.elem[L.length-1]); p >= q; --p)
		*(p+1) = *p;    //插入位置及之后元素后移1位
	*q = e;             //插入e
	++L.length;         //表长增1
	return OK;
}

//算法2.5
Status ListDelete_Sq(SqList &L,int i,ElemType &e){
    //在顺序线性表L中删除第i个元素，并用e返回其值
    //i的合法值为：[1, ListLength_Sq(L)]
	ElemType *p, *q;
	if(i < 1 || i > L.length)           //i值合法性
	{
		printf("删除位置有误!\n");
		return ERROR;
	}
	p = &(L.elem[i-1]);         //要删除的元素位置
    e = *p;
    q = L.elem + L.length - 1;  //最后1个元素的位置 q = &(L.elem[L.length-1]);
    for (++p; p <= q; ++p)      //被删除元素之后元素前移1位
        *(p-1) = *p;
	--L.length;
	return OK;
}


int ListLength_Sq(SqList L)
{
    return L.length;
}

//等于
Status equal(ElemType e1,ElemType e2)
{
    if(e1 == e2)
        return OK;
    else
        return ERROR;
}
//小于
Status lessthan(ElemType e1,ElemType e2)
{
    if(e1 < e2)
        return OK;
    else
        return ERROR;
}
//小于等于
Status lessequal(ElemType e1,ElemType e2)
{
    if(e1 <= e2)
        return OK;
    else
        return ERROR;
}

Status GetElem(SqList L,int i,ElemType &e)
{
    if(i < 1 || i > L.length)
        return ERROR;
    e = L.elem[i-1];
    return OK;
}

//算法2.6.0
int LocateElem_Sq(SqList L,ElemType e,Status (*compare)(ElemType ,ElemType )){
    //在顺序线性表L中找到第1个与e满足compare()的元素位序
    //若找到，则返回其在L中的位序，否则返回0
	int i = 1;                  //i的初值为第1个元素的位序
    ElemType *p = L.elem;       //p的初值为第1个元素的存储位置
    while (i <= L.length && !(*compare)(*p++, e))
        ++i;
    if(i <= L.length)
        return i;
    else
        return 0;
}

//算法2.6.1
int LocateElem_Sq1(SqList L,ElemType e,Status (*compare)(ElemType ,ElemType )){
    //在顺序线性表L中找到第1个与e满足compare()的元素位序
    //若找到，则返回其在L中的位序，否则返回0
	int i;
    ElemType e1;
	for(i = 1;i <= L.length;i++)
	{
		GetElem(L, i, e1);
        if(compare(e1, e))
			return i;
	}
	return 0;
}



void visit(ElemType e)
{
	printf("%d ",e);
}

void TraverseList(SqList La, void (*pvist)(ElemType ))
{
	int i;
    ElemType e;
	for(i = 1; i <= La.length; ++i)
	{
        GetElem(La, i, e);
		pvist(e);
	}
	printf("\n");
}



////测试LocateElem
int main(void)
{
	SqList La;
    int i, pos;
	ElemType data[9] = {1 ,2 ,2 ,3 ,4 ,5 ,6 ,7 , 10}; 
	InitList_Sq(La);
	for (i = 1; i <= 9; i++)
		ListInsert_Sq(La,i,data[i-1]);
    TraverseList(La, visit);
    
    if(pos = LocateElem_Sq(La, 2, equal))
        printf("La中有元素7,第一个是7的元素是第%d个元素。\n", pos);
    else
        printf("La中有元素7\n");

	return 0;
}