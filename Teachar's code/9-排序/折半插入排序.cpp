#include <stdio.h>
#include <windows.h>
#define  EQ(a, b)	((a)==(b))	//a,b为数值型
#define  LT(a, b)	((a)< (b))
#define  LQ(a, b)	((a)<=(b))
#define MAXSIZE 20
typedef int KeyType;

typedef struct
{
	KeyType key;
}RedType;

typedef struct 
{
	RedType r[MAXSIZE+1];
	int length;
}SqList;

void printData(SqList L);
void PrintHL(SqList L,int low ,int high,int mid);
void PrintStep(SqList L,int low ,int high,int mid);
//注意:因为拍完序的部分是有序的，因此可对有序部分进行折半查找！！
void BInsertSort(SqList &L)
	//对顺序表L作折半插入排序。
{
	int i,j;
	for(i = 2;i <= L.length; ++i)
	{
		int low = 1, high = i - 1, mid;		//设置折半查找的区间
		L.r[0] = L.r[i];					//将L.r[i]暂存到L.r[0]，不是哨兵
		while(low <= high)
		{
			mid = (low + high)/2;			//折半查找的中间比较位置
			PrintStep(L, low , high, mid);
			if(LT(L.r[0].key,L.r[mid].key))	//若插入的数据key值比中间位置key值小
			{
				high = mid - 1;				//去区间的前半部分查找
				PrintStep(L, low , high, mid);
			}
			else
			{
				low = mid + 1;				//否则，就去区间的后半部分查找
				PrintStep(L, low , high, mid);
			}
		}//while
		for(j = i - 1; j >= low; --j)
			L.r[j+1] = L.r[j];				//从第i-1的位置记录后移
		PrintStep(L, low , high, mid);
		L.r[low] = L.r[0];					//将L.r[0]插入到high+1的位置
											//或者说是low的位置，不可用mid因为分奇偶
		PrintStep(L, low , high, mid);
	}//for
}


void printData(SqList L)
{
	for (int i = 0; i <= L.length; i++)
		printf("%2d ", L.r[i].key);
	printf("\n");
}

void PrintHL(SqList L,int low ,int high,int mid)
{
	int i;
	printData(L);
	for(i = 0; i < L.length + 1; ++i)
	{
		if(i == low && i == high)
			printf("|| ");
		else if(i == low)
			printf("|L ");
		else if(i == high)
			printf("H| ");
		else
			printf("   ");
	}
	printf("\n");
	for(i = 0; i < L.length + 1; ++i)
	{
		if(i == mid)
			printf("%2d ",L.r[mid].key);
		else
			printf("   ");
	}
	printf("\n");
}


void PrintStep(SqList L,int low ,int high,int mid)
{
	system("cls");
	PrintHL(L, low , high, mid);
	system("pause");
}


int main(void)
{
	int arr[8] = {30, 13, 70, 85, 39, 42, 6, 20 };
	SqList L;
	L.length = 0;
	for (int i = 1; i <= 8; i++)
	{
		L.r[i].key = arr[i-1];
		++L.length;
	}
	printData(L);
	BInsertSort(L);
	printData(L);
	return 0;
}
