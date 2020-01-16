#include <stdio.h>

#define LIST_INITSIZE 100
#define ElemType int
#define Status int
#define OK     1
#define ERROR  0

//-----���Ա�ľ�̬����˳��洢�ṹ-----
typedef struct
{
	ElemType elem[LIST_INITSIZE];
	int length;
}SqList;


//�㷨2.3
Status InitList_Sq(SqList &L)
{
	L.length = 0;
	return OK;
}

//�㷨2.4
Status ListInsert(SqList &L, int i,ElemType e)
{
	ElemType *p, *q;
	int k;
	if(i < 1 || i > L.length + 1)
	{
		printf("iֵ���Ϸ���\n");
		return ERROR;
	}
	if(L.length >= LIST_INITSIZE)
	{
		printf("Ԫ�����������ܲ��룡\n");
		return ERROR;
	}
	//p = &L.elem[i-1];
	//for(q = &L.elem[L.length-1]; q >= p; --q)
	//	*(q+1) = *q;
	//*p = e;
	for(k = L.length-1; k >= i-1; --k)
	{
		L.elem[k+1] = L.elem[k];
	}
	L.elem[i-1] = e;
	++L.length;
	return OK;
}

//�㷨2.5
Status ListDelete(SqList &L,int i,ElemType &e)
{
	ElemType *p, *q;
	int k = 0;
	if(i < 1 || i > L.length)
	{
		printf("ɾ��λ������!\n");
		return ERROR;
	}
	e = L.elem[i-1];
	//q = &L.elem[L.length-1];
	//for(p = &L.elem[i-1]; p < q; ++p)
	//	*p = *(p + 1);
	for(k = i-1; k < L.length-1; ++k)
	{
		L.elem[k] = L.elem[k+1];
	}

	--L.length;
	return OK;
}

Status GetElem(SqList L, int i ,ElemType &e)
{
	if(i < 1 || i > L.length)
	{
		printf("��ȡԪ��λ������!\n");
		return ERROR;
	}
	e = L.elem[i-1];
	return OK;
}

void visit(ElemType e)
{
    printf("%d ",e);
}

void ListTraverse(SqList L, void (*visit)(ElemType ))
{
	int i;
	ElemType e;
	for(i = 1; i <= L.length; ++i)
	{
		if(GetElem(L, i ,e))
			visit(e);
	}
	printf("\n");
}

int main(void)
{
	SqList L;
	SqList B, C;
	int i;
	ElemType e;
	ElemType data[9] = {11,-22,33,-3,-88,21,77,0,-9}; 
	InitList_Sq(L);
	
	for (i = 1; i <= 9; i++)
	{
		ListInsert(L,i,data[i-1]);
	}
	printf("������ɺ�L = : ");
	ListTraverse(L , visit);
	ListDelete(L,1,e);
	printf("ɾ����1����L = : ");
	ListTraverse(L , visit);
	
	return 0;
}