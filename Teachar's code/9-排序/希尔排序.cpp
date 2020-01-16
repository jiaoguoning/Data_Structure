#include <stdio.h>
#include <windows.h>
#define  EQ(a, b)	((a)==(b))	//a,bΪ��ֵ��
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
	//��˳���L��һ��ϣ���������򡣱��㷨�Ǻ�һ��ֱ�Ӳ���������ȣ����������޸�
	//1. ǰ���¼λ�õ�������dk��������1;
	//2. r[0]ֻ���ݴ浥Ԫ�������ڱ�����j <= 0ʱ������λ�����ҵ���
{
	int i, j;
	PrintStep(L, dk);
	for(i = dk+1; i <= L.length; ++i)
	{
		if(LT(L.r[i].key, L.r[i-dk].key))	//�轫L.r[i]�������������ӱ�
		{									//���Ҫ�����L.r[i]��L.r[i-dk].keyС������ǰ��(���жϺ�һ��С��ǰһ���Ƿ����)
			L.r[0] = L.r[i];				//��L.r[i]�ݴ���L.r[0]
			PrintStep(L, dk);
			for(j = i-dk; j > 0 && LT(L.r[0].key, L.r[j].key); j -= dk)
				L.r[j + dk] = L.r[j];		//��¼���ƣ����Ҳ����λ��
			PrintStep(L, dk);
			L.r[j+dk] = L.r[0];				//����L.r[0]
			PrintStep(L, dk);
		}
	}
}

void ShellSort(SqList &L,int dlta[],int t)
	//����������dlta[0...t-1]��˳���L��ϣ������
{
	int k;
	for(k = 0; k < t; ++k)
		ShellInsert(L, dlta[k]);	//һ������Ϊdlta[k]�Ĳ�������
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