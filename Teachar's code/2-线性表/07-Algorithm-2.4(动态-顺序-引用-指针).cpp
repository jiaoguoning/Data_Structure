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

//算法2.3.0
Status InitList_Sq(SqList &L){
    // 构造一个空的线性表
	L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if(!L.elem)
		exit(OVERFLOW);         //存储分配失败
	L.length = 0;               //空表长度为0
	L.listsize = LIST_INIT_SIZE;//初始存储容量
	return OK;
}//InitList_Sq


//算法2.4.0
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
			exit(OVERFLOW);         //return ERROR;
		L.elem = newbase;           //获取新基址
		L.listsize += LISTINCREMENT;//增加存储容量
	}
	q = &L.elem[i-1];   //插入的位置
	for(p = &(L.elem[L.length-1]); p >= q; --p)
		*(p+1) = *p;    	//插入位置及之后元素后移1位
	*q = e;             //插入e
	++L.length;         //表长增1
	return OK;
}

//算法2.4.1
Status ListInsert_Sq1(SqList &L, int i,ElemType e){
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
			exit(OVERFLOW);         //return ERROR;
		L.elem = newbase;           //获取新基址
		L.listsize += LISTINCREMENT;//增加存储容量
	}
	q = &L.elem[i-1];    //插入的位置
	for(p = &(L.elem[L.length]); p > q; --p)
		*p = *(p-1);    	//插入位置及之后元素后移1位
	*q = e;             //插入e
	++L.length;         //表长增1
	return OK;
}

//算法2.4.2
Status ListInsert_Sq2(SqList &L, int i,ElemType e){
    //在顺序线性表L中第i个位置之前插入新的元素e，
    //i的合法值为 [1, ListLength_Sq(L)+1]
	ElemType *p, *q, *newbase;
    int j;
	if(i < 1 || i > L.length + 1)   //i值合法性
	{
		printf("i不合法，不能插入！\n");
		return ERROR;
	}
	if(L.length >= L.listsize)      //判断是否要追加空间
	{
		newbase = (ElemType *)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
		if(!newbase)                //存储分配失败
			exit(OVERFLOW);         //return ERROR;
		L.elem = newbase;           //获取新基址
		L.listsize += LISTINCREMENT;//增加存储容量
	}
    for (j = L.length; j >= i; --j)
    {
        L.elem[j] = L.elem[j-1];
    }
	L.elem[i-1] = e;    //插入e
	++L.length;         //表长增1
	return OK;
}


//算法2.4.3
Status ListInsert_Sq3(SqList &L, int i,ElemType e){
    //在顺序线性表L中第i个位置之前插入新的元素e，
    //i的合法值为 [1, ListLength_Sq(L)+1]
	ElemType *p, *q, *newbase;
    int j;
	if(i < 1 || i > L.length + 1)   //i值合法性
	{
		printf("i不合法，不能插入！\n");
		return ERROR;
	}
	if(L.length >= L.listsize)      //判断是否要追加空间
	{
		newbase = (ElemType *)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
		if(!newbase)                //存储分配失败
			exit(OVERFLOW);         //return ERROR;
		L.elem = newbase;           //获取新基址
		L.listsize += LISTINCREMENT;//增加存储容量
	}
    for (j = L.length-1; j >= i-1; --j)
    {
        L.elem[j+1] = L.elem[j];
    }
	L.elem[i-1] = e;    //插入e
	++L.length;         //表长增1
	return OK;
}

Status GetElem(SqList L,int i,ElemType &e)
{
    if(i < 1 || i > L.length)
        return ERROR;
    e = L.elem[i-1];
    return OK;
}

void visit(ElemType e)
{
	printf("%4d ",e);
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

// 测试Insert
int main(void)
{
	SqList La;
	int i;
	ElemType data[9] = {11,-22,-33,3,-88,21,77,0,-9}; 
   
	InitList_Sq(La);
	for (i = 1; i <= 9; i++)
		ListInsert_Sq3(La,i,data[i-1]);
    TraverseList(La, visit);
    ListInsert_Sq3(La,4,999);
    TraverseList(La, visit);

	return 0;
}
