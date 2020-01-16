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
		*(p+1) = *p;    //插入位置及之后元素后移1位
	*q = e;             //插入e
	++L.length;          
	return OK;
}

//算法2.5.0
Status ListDelete_Sq(SqList &L,int i,ElemType &e){
	ElemType *p, *q;
	if(i < 1 || i > L.length)           
	{
		printf("删除位置有误!\n");
		return ERROR;
	}
	p = &(L.elem[i-1]);         
    e = *p;
    q = L.elem + L.length - 1;  
    for (++p; p <= q; ++p)      
        *(p-1) = *p;
	--L.length;
	return OK;
}

//算法2.5.1
Status ListDelete_Sq1(SqList &L,int i,ElemType &e){
    //在顺序线性表L中删除第i个元素，并用e返回其值
    //i的合法值为：[1, ListLength_Sq(L)]
	ElemType *p, *q;
	if(i < 1 || i > L.length)            
	{
		printf("删除位置有误!\n");
		return ERROR;
	}
    p = L.elem + i - 1;
    e = *p;
	q = &(L.elem[L.length - 1]);  
    for (; p < q; ++p)      
        *p = *(p+1);

	--L.length;
	return OK;
}


//算法2.5.2
Status ListDelete_Sq2(SqList &L,int i,ElemType &e){
    //在顺序线性表L中删除第i个元素，并用e返回其值
    //i的合法值为：[1, ListLength_Sq(L)]
	int k = 0;
	if(i < 1 || i > L.length)            
	{
		printf("删除位置有误!\n");
		return ERROR;
	}
	e = L.elem[i-1];
    //时刻记住第i个元素对应下标是i-1
	for(k = i; k <= L.length-1; ++k)
		L.elem[k-1] = L.elem[k];
	
	--L.length;
	return OK;
}


//算法2.5.3
Status ListDelete_Sq3(SqList &L,int i,ElemType &e){
    //在顺序线性表L中删除第i个元素，并用e返回其值
    //i的合法值为：[1, ListLength_Sq(L)]
	int k = 0;
	if(i < 1 || i > L.length)            
	{
		printf("删除位置有误!\n");
		return ERROR;
	}
	e = L.elem[i-1];
	for(k = i-1; k <= L.length-2; ++k)
		L.elem[k] = L.elem[k+1];
	
	--L.length;
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

// 测试Delete
int main(void)
{
	SqList La, Lb;
	int i;
	ElemType e;
	ElemType data[9] = {11,-22,-33,3,-88,21,77,0,-9}; 
   
	InitList_Sq(La);
    
	for (i = 1; i <= 9; i++)
		ListInsert_Sq(La,i,data[i-1]);
    TraverseList(La, visit);

    ListDelete_Sq3(La, 1, e);
    TraverseList(La, visit);
   
	return 0;
}


