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
int KeyArr[ELENGTH] = {5, 13, 19, 21, 37, 56, 64, 75, 80, 88, 92};	
void PrintHL(SSTable ST,int low ,int high,int mid);

// 算法9.2
int Search_Bin(SSTable ST, KeyType key)
{	// 在有序表ST中折半查找其关键字等于key的数据元素。
    // 若找到，则函数值为该元素在表中的位置，否则返回0。

	int low = 1, high = ST.length;			//置区间初值
	while (low <= high)
	{
		int mid = (low + high) / 2;
		PrintHL(ST,low ,high,mid);
		if(EQ(key,ST.elem[mid].key))		//找到待查元素
		{
			PrintHL(ST,low ,high,mid);
			return mid;
		}
		else if(LT(key, ST.elem[mid].key))	//继续在前半区进行查找
		{
			high = mid - 1;
			PrintHL(ST,low ,high,mid);
		}
		else								//在后半区进行查找
		{
			low = mid + 1;
			PrintHL(ST,low ,high,mid);
		}
	}
	return 0;								//顺序表中不存在待查元素
}

void PrintSStable(SSTable ST)
{
	int i;
	for(i = 1;i <= ST.length; ++i)
		printf("%2d ",ST.elem[i].key);
	printf("\n");
}

void PrintHL(SSTable ST,int low ,int high,int mid)
{
	int i;
	PrintSStable(ST);
	for(i = 1; i < ST.length + 1; ++i)
	{
		if(i == low && i == high)
			printf("|| ");
		else if(i == low)
			printf("|_ ");
		else if(i == high)
			printf("_| ");
		else
			printf("   ");
	}
	printf("\n");
	for(i = 1; i < ST.length + 1; ++i)
	{
		if(i == mid)
			printf("%2d ",ST.elem[mid].key);
		else
			printf("   ");
	}
	printf("\n");
}



// 折半查找
int main(void)
{
	int i ;		
	SSTable ST;
	ST.elem = (ElemType *)malloc(sizeof(ElemType) * ELENGTH + 1);
	ST.length = ELENGTH;
	for(i = 1;i <= ST.length; ++i)
		ST.elem[i].key = KeyArr[i-1];
	PrintSStable(ST);
	printf("%d\n",Search_Bin(ST, 36));

	return 0;
}