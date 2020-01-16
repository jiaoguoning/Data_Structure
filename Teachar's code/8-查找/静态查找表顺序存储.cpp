#include <stdio.h>
#include <stdlib.h>
#define  EQ(a, b)	((a)==(b))	//a,b为数值型
#define  LT(a, b)	((a)< (b))
#define  LQ(a, b)	((a)<=(b))

#define KeyType int
#define InfoType char

typedef struct
{
	KeyType key;	//数据元素中查找的关键字
	InfoType* info;	//数据元素中的其他信息
}ElemType;

typedef struct
{
	ElemType *elem;	//数据元素存储空间基址，建表时按实际长度分配，0号单元留空
	int length;		//表长度
}SSTable;

//构造PPT上的已知数据
#define ELENGTH 11
int KeyArr[ELENGTH] = {5, 37, 19, 21, 13, 56, 64, 92, 88, 80, 75};	

int Search_Seq(SSTable ST, KeyType key)
	//在顺序表ST中顺序查找其关键字等于key的数据元素。若找到，则函数值为该元素在表中的位置，否则返回0.
{
	int i;
	ST.elem[0].key = key;
	for(i = ST.length; !EQ(ST.elem[i].key,key); --i);
	return i;
}

void PrintSStable(SSTable ST)
{
	int i;
	for(i = 1;i <= ST.length; ++i)
		printf("%d ",ST.elem[i].key);
	printf("\n");
}

int main(void)
{
	int i ;		SSTable ST;
	ST.elem = (ElemType *)malloc(sizeof(ElemType) * ELENGTH + 1);
	ST.length = ELENGTH;
	for(i = 1;i <= ST.length; ++i)
		ST.elem[i].key = KeyArr[i-1];
	PrintSStable(ST);
	printf("%d\n",Search_Seq(ST, 64));

	return 0;
}