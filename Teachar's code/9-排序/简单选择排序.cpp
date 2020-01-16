#include <stdio.h>
#include <windows.h>
#define  EQ(a, b)	((a)==(b))	//a,b为数值型
#define  LT(a, b)	((a)< (b))
#define  LQ(a, b)	((a)<=(b))
#define MAXSIZE 20
typedef int KeyType;
typedef char InfoType;

typedef struct
{
	KeyType key;
	InfoType info;
}RedType;

typedef struct 
{
	RedType r[MAXSIZE+1];
	int length;
}SqList;

void printData(SqList L,int k,int j);
void printBound(int i);

int SelectMinKey(SqList L,int i)
{
	int j, k = i;
	RedType min = L.r[i];
	for(j = i + 1; j <= L.length; ++j)
	{
		printData(L ,k ,j);
		if(L.r[j].key < min.key)
		{
			k = j;
			min = L.r[j];
			printData(L ,k ,j);
		}
	}
	return k;
}

void SelectSort(SqList &L)
	//对顺序表L作简单选择排序。
{
	int i, j;
	RedType temp;
	for(i = 1; i < L.length; ++i)	//选择第i小的记录，并交换到位
	{
		j = SelectMinKey(L,i);		//在L.r[i...L.length]中选择key值最小的记录
		if(i != j)
		{
			temp = L.r[i];			//与第i个记录交换
			L.r[i] = L.r[j];
			L.r[j] = temp;
		}
		printBound(i);
	}
	printData(L ,-1 ,-1);
}


void printData(SqList L,int k,int j)
{
	int i;
	for (i = 0; i <= L.length; ++i)
		printf("%2d  ", L.r[i].key);
	printf("\n");
	for (i = 0; i <= L.length; ++i)
	{
		if(i == k && i == j )
			printf("||  ");
		else if(i == k)
			printf("|k  ");
		else if(i == j)
			printf("j|  ");
		else
			printf("    ");
	}
	printf("\n");




}

void printBound(int i)
{
	int k;
	for (k = 0; k <= i; k++)
		printf("----");
	printf("\b|\n");

}



int main(void)
{
	int arr[8] = {49, 38, 65, 97, 76, 13, 27, 49};
	SqList L;
	L.r[0].key = 0;
	L.length = 0;
	for (int i = 1; i <= 8; i++)
	{
		L.r[i].key = arr[i-1];
		++L.length;
	}
	SelectSort(L);

	return 0;
} 