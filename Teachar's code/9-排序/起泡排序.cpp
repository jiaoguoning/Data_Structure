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

void printData(SqList L,int change);
void printLocate(int j);
void printBound(int l_i);

void BubbleSort(SqList &L)
{
	int i, j, change = 1;
	printData(L,change);
	for(i = 1;i < L.length && change; ++i)
	{
		change = 0;			//change的作用：若需要比较的区间内，没有要进行交换的，
							//那么change一直是0，且在该区间内已经有序，没必要再遍历比它少一个数的子区间
		//printData(L,change);
		for(j = 1; j <= L.length - i; ++j)
		{
			RedType temp;
			printData(L,change);
			printLocate(j);
			if(LT(L.r[j+1].key,L.r[j].key))
			{
				temp = L.r[j+1];
				L.r[j+1] = L.r[j];
				L.r[j] = temp;
				change = 1;
			}
			printData(L,change);
		}
		printBound(L.length - i);
	}
}



void printData(SqList L,int change)
{
	int i;
	for (i = 1; i <= L.length; i++)
		printf("%2d  ", L.r[i].key);
	printf("change = %d ", change);
	printf("\n");
}

void printLocate(int j)
{
	int i;
	for (i = 1; i < j; i++)
		printf("    ");
	printf(" |  ");
	printf(" | ");
	printf("\n");
}

void printBound(int l_i)
{
	int k;
	for (k = 1; k <= l_i; k++)
		printf("----");
	printf("\b|\n");

}



void PrintStep()
{
	system("cls");
	
	system("pause");
}


int main(void)
{
	//int arr[8] = {13, 27,49, 38, 65, 97, 76,  49};
	int arr[8] = {49, 38, 65, 97, 76, 13, 27, 49};
	SqList L;
	L.r[0].key = 0;
	L.length = 0;
	for (int i = 1; i <= 8; i++)
	{
		L.r[i].key = arr[i-1];
		++L.length;
	}
	BubbleSort( L);

	return 0;
} 