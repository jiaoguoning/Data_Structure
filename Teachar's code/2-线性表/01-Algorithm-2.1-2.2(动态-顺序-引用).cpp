#include <stdio.h>
#include <stdlib.h>

#define LIST_INIT_SIZE  100
#define LISTINCREMENT   10
#define Status          int
#define OVERFLOW        -1
#define OK              1
#define ERROR           0


#define ElemType int
typedef struct
{
	ElemType * elem;
	int length;
	int listsize;
}SqList;

Status InitList(SqList &L)
{
	L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if(!L.elem)
		exit(OVERFLOW);
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return OK;
}

void Destroy(SqList &L)
{
	free(L.elem);  
	L.elem = NULL;
	L.length = 0;
	L.listsize = 0;
}


Status equal(ElemType e1,ElemType e2)
{
    if(e1 == e2)
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


int LocateElem(SqList L,ElemType e,Status (*compare)(ElemType ,ElemType ))
{
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

Status ListInsert(SqList &L, int i,ElemType e)
{
	ElemType *p, *q, *newbase;
	if(i < 1 || i > L.length + 1)
	{
		printf("i不合法，不能插入！\n");
		return ERROR;
	}
	if(L.length >= L.listsize)
	{
		newbase = (ElemType *)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
		if(!newbase)
			return ERROR;
		L.elem = newbase;
		L.listsize += LISTINCREMENT;
	}
	p = &L.elem[i-1];
	for(q = &L.elem[L.length-1]; q >= p; --q)
		*(q+1) = *q;
	*p = e;
	++L.length;
	return OK;
}

//算法2.1
void UnionList(SqList &La,SqList Lb)
    // 将所有在线性表Lb中但不在La中的数据元素插入到La中
{
	int La_len = La.length;
	int Lb_len = Lb.length;
	int i;
	for(i = 1;i <= Lb_len ;i++)
	{
		ElemType e;
        GetElem(Lb, i, e);
		if(!LocateElem(La ,e ,equal))
		    ListInsert(La, ++La_len, e);
	}
}
//算法2.2
void MergeList(SqList La,SqList Lb,SqList &Lc){
    //已知线性表La和Lb中的数据元素按值非递减排列。
    //归并La和Lb得到新的线性表Lc，Lc的数据元素也按值非递减排列。
    InitList(Lc);
    int i = 1, j = 1, k = 0;
    int La_len = La.length, Lb_len = Lb.length;
    ElemType ai, bj;
    while (i <= La_len && j <= Lb_len)
    {
        GetElem(La, i, ai);    GetElem(Lb, j, bj);
        if(ai <= bj){
            ListInsert(Lc,++k,ai); 
            ++i;
        }else{
            ListInsert(Lc,++k,bj); 
            ++j;
        }
    }
    while (i <= La_len)
    {
        GetElem(La, i, ai);
        ListInsert(Lc,++k,ai); 
        ++i;
    }
    while (j <= Lb_len)
    {
        GetElem(Lb, j, bj);
        ListInsert(Lc,++k,bj); 
        ++j;
    }
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






//测试MergeList
int main(void)
{
	SqList La, Lb, Lc;
	int i;
	ElemType e;
	ElemType data[9] = {1 ,2 ,2 ,3 ,4 ,5 ,6 ,7 , 10}; 
    ElemType data1[6] = {1 ,3 ,4 ,4 ,88, 99}; 
	InitList(La);
    InitList(Lb);
    InitList(Lc);
	for (i = 1; i <= 9; i++)
		ListInsert(La,i,data[i-1]);
    TraverseList(La, visit);
    for (i = 1; i <= 6; i++)
		ListInsert(Lb,i,data1[i-1]);
    TraverseList(Lb, visit);

    MergeList(La, Lb, Lc);

    TraverseList(Lc, visit);

	return 0;
}



//测试UnionList
//int main(void)
//{
//	SqList La, Lb;
//	int i;
//	ElemType e;
//	ElemType data[9] = {11,-22,-33,3,-88,21,77,0,-9}; 
//    ElemType data1[5] = {1,-2,3,33,-88}; 
//	InitList(La);
//    InitList(Lb);
//	for (i = 1; i <= 9; i++)
//		ListInsert(La,i,data[i-1]);
//    TraverseList(La, visit);
//    for (i = 1; i <= 5; i++)
//		ListInsert(Lb,i,data1[i-1]);
//    TraverseList(Lb, visit);
//
//    UnionList(La,Lb);
//    TraverseList(La, visit);
//
//	return 0;
//}



