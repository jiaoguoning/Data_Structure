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

void printData(SqList L,int low,int high);

int Partition1(SqList &L, int low,int high)
	//交换顺序表L中子表L.r[low...high]的记录，使枢轴记录到位，并返回其所在位置
	//此时在它之前（后）得到记录均不大（小）于它。
{
	RedType temp;
	KeyType pivotkey = L.r[low].key;	//用子表第一个记录作枢轴记录
	while (low < high)					//从表的两端交替地向中间扫描
	{
		while (low < high && L.r[high].key >= pivotkey)	//为什么取等号？因为对于相等的情况
			--high;										//不交换，可以减少交换次数，提高效率
		temp = L.r[high];				//将比枢轴记录小的记录交换到低端
		L.r[high] = L.r[low];
		L.r[low] = temp;
		while (low < high && L.r[low].key <= pivotkey)
			++low;
		temp = L.r[high];				//将比枢轴记录大的的记录交换到高端
		L.r[high] = L.r[low];
		L.r[low] = temp;
	}
	return low;							//返回枢轴所在位置
}


int Partition2(SqList &L, int low,int high)
{
	KeyType pivotkey;
	L.r[0] = L.r[low];					//用子表的第一个记录作枢轴记录
	pivotkey = L.r[low].key;			//枢轴记录关键字
	printData(L,low,high);
	while(low < high)
	{
		while (low < high && L.r[high].key >= pivotkey)	//为什么取等号？因为对于相等的情况
		{												//不交换，可以减少交换次数，提高效率
			--high;
			printData(L,low,high);
		}
		L.r[low] = L.r[high];
		while (low < high && L.r[low].key <= pivotkey)
		{
			++low;
			printData(L,low,high);
		}
		L.r[high] = L.r[low];
	}
	L.r[low] = L.r[0];					//枢轴记录到位
	printData(L,low,high);
	return low;							//返回枢轴位置
}

void QSort(SqList &L,int low,int high)
	//对顺序表L中的子序列L.r[low...high]作快速排序
{
	int pivotloc;							//用于存储返回的枢轴位置
	if(low < high)							//长度大于1
	{
		pivotloc = Partition2(L,low,high);	//将L.r[low...high]一分为二
		QSort(L, low,pivotloc - 1);			//低子表递归排序，pivotloc是一分为二的枢轴位置
		QSort(L, pivotloc + 1,high);		//对高子表递归排序
	}
}

void QuickSort(SqList &L)
	//对顺序表L作快速排序
{
	QSort(L,1,L.length);
}


void printData(SqList L,int low,int high)
{
	int i;
	for (i = 0; i <= L.length; ++i)
		printf("%2d  ", L.r[i].key);
	printf("\n");
	for (i = 0; i <= L.length; ++i)
	{
		if(i == low && i == high )
			printf("||  ");
		else if(i == low)
			printf("|L  ");
		else if(i == high)
			printf("H|  ");
		else
			printf("    ");
	}
	printf("\n");
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
	QuickSort( L);

	return 0;
} 