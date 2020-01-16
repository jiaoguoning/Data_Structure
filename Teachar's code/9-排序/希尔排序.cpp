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

void printData(SqList L,int dk);
void PrintStep(SqList L,int dk);
void ShellInsert(SqList &L,int dk)
	//对顺序表L作一趟希尔插入排序。本算法是和一趟直接插入排序相比，做了以下修改
	//1. 前后记录位置的增量是dk，而不是1;
	//2. r[0]只是暂存单元，不是哨兵。当j <= 0时，插入位置已找到。
{
	int i, j;
	PrintStep(L, dk);
	for(i = dk+1; i <= L.length; ++i)
	{
		if(LT(L.r[i].key, L.r[i-dk].key))	//需将L.r[i]插入有序增量子表
		{									//如果要插入的L.r[i]比L.r[i-dk].key小，插入前面(即判断后一个小于前一个是否成立)
			L.r[0] = L.r[i];				//将L.r[i]暂存在L.r[0]
			PrintStep(L, dk);
			for(j = i-dk; j > 0 && LT(L.r[0].key, L.r[j].key); j -= dk)
				L.r[j + dk] = L.r[j];		//记录后移，查找插入的位置
			PrintStep(L, dk);
			L.r[j+dk] = L.r[0];				//插入L.r[0]
			PrintStep(L, dk);
		}
	}
}

void ShellSort(SqList &L,int dlta[],int t)
	//按增量序列dlta[0...t-1]对顺序表L作希尔排序。
{
	int k;
	for(k = 0; k < t; ++k)
		ShellInsert(L, dlta[k]);	//一趟增量为dlta[k]的插入排序
}

void printData(SqList L,int dk)
{
	int i, j;
	for(i = 1 ; i <= L.length; ++i)
		L.r[i].info = 'A' + (i-1) % (dk)  ;
	for (i = 0; i <= L.length; i++)
		printf("%2d  ", L.r[i].key);
	printf("\n");
	for (i = 0; i <= L.length; i++)
		printf(" %c  ", L.r[i].info);
	printf("\n");

}



void PrintStep(SqList L,int dk)
{
	system("cls");
	printData(L, dk);
	system("pause");
}


int main(void)
{
	int arr[10] = {49, 38, 65, 97, 76, 13, 27, 49, 55, 4};
	int dlta[] = {5,3,1};
	SqList L;
	L.r[0].info = ' ';
	L.r[0].key = 0;
	L.length = 0;
	for (int i = 1; i <= 10; i++)
	{
		L.r[i].key = arr[i-1];
		L.r[i].info = ' ';
		++L.length;
	}
	ShellSort(L, dlta, 3);


	return 0;
} 