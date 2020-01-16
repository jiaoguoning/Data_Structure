#include <stdio.h>
#define  EQ(a, b)	((a)==(b))	//a,bΪ��ֵ��
#define  LT(a, b)	((a)< (b))
#define  LQ(a, b)	((a)<=(b))
#define MAXSIZE 20
typedef int KeyType;

typedef struct{
	KeyType key;
}RedType;

typedef struct {
	RedType r[MAXSIZE+1];
	int length;
}SqList;

void printData(SqList L);
void InsertSort(SqList &L)
{
	int i,j;
	for(i = 2;i <= L.length; ++i)
	{
		if(LT(L.r[i].key , L.r[i-1].key))	//��<���轫L.r[i]���������ӱ�
		{
			L.r[0] = L.r[i];				//����Ϊ�ڱ�
			L.r[i] = L.r[i-1];
			printData(L);
			for(j = i-2;L.r[0].key < L.r[j].key;--j)
			{
				L.r[j+1] = L.r[j];			//��¼����
				printData(L);
			}
			L.r[j+1] = L.r[0];				//���뵽��ȷλ��
			printData(L);
		}
		printData(L);
		printf("-------\n");
	}
}



/////////////////////   �����������ݽṹ��    ///////////////////////////
void printData(SqList L)
{
	for (int i = 0; i <= L.length; i++)
		printf("%d  ", L.r[i].key);
	printf("\n");
}

int main(void)
{
	int arr[8] = {49,38,65,97,76,13,27,49};
	SqList L;
	L.length = 0;
	for (int i = 1; i <= 8; i++)
	{
		L.r[i].key = arr[i-1];
		++L.length;
	}
	printData(L);
	InsertSort(L);
	printData(L);



	return 0;
}
