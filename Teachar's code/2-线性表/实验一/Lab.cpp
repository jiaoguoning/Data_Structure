#include <stdio.h>
#include "DynaLnkList.h"

void myvisit(ElemType c)
{
	printf("%d\n",c);
}

int myadd(int a,int b,void (*pv)(int c))
{
	pv(a+b);
	return a+b;
}

int main(void)
{
	// TODO: Place your test code here
	LinkList L;
	int k;
	ElemType e ;
	int i, arr[9] = {11,-22,33,-3,-88,21,77,0,-9};
	InitList(&L);
	for(i = 1; i <= 9; ++i)
	{
		ListInsert(L, i, arr[i-1]);
	}

	printf("���β���Ԫ�غ�����L����Ϊ�� %d \n", ListLength(L));
	printf("���β���Ԫ�غ�����LΪ��\n");
	ListTraverse(L, visit);

	printf("������ɾ�������ڼ�����㣺\n");
	scanf("%d",&k);
	Inverse(L);
	ListDelete(L,k,&e);
	Inverse(L);
	printf("ɾ�����LΪ��\n");
	ListTraverse(L, visit);
	
	DestroyList(&L);

	return 0;
}
