#include <stdio.h>
#include <windows.h>
#define  EQ(a, b)	((a)==(b))	//a,bΪ��ֵ��
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
//ע��:��Ϊ������Ĳ���������ģ���˿ɶ����򲿷ֽ����۰���ң���
void BInsertSort(SqList &L)
	//��˳���L���۰��������
{
	int i,j;
	for(i = 2;i <= L.length; ++i)
	{
		int low = 1, high = i - 1, mid;		//�����۰���ҵ�����
		L.r[0] = L.r[i];					//��L.r[i]�ݴ浽L.r[0]�������ڱ�
		while(low <= high)
		{
			mid = (low + high)/2;			//�۰���ҵ��м�Ƚ�λ��
			PrintStep(L, low , high, mid);
			if(LT(L.r[0].key,L.r[mid].key))	//�����������keyֵ���м�λ��keyֵС
			{
				high = mid - 1;				//ȥ�����ǰ�벿�ֲ���
				PrintStep(L, low , high, mid);
			}
			else
			{
				low = mid + 1;				//���򣬾�ȥ����ĺ�벿�ֲ���
				PrintStep(L, low , high, mid);
			}
		}//while
		for(j = i - 1; j >= low; --j)
			L.r[j+1] = L.r[j];				//�ӵ�i-1��λ�ü�¼����
		PrintStep(L, low , high, mid);
		L.r[low] = L.r[0];					//��L.r[0]���뵽high+1��λ��
											//����˵��low��λ�ã�������mid��Ϊ����ż
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
