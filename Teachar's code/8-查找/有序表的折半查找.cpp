#include <stdio.h>
#include <stdlib.h>
#define  EQ(a, b)	((a)==(b))	//a,bΪ��ֵ��
#define  LT(a, b)	((a)< (b))
#define  LQ(a, b)	((a)<=(b))

#define KeyType int
#define InfoType char

typedef struct
{
	KeyType key;	//����Ԫ���в��ҵĹؼ���
	InfoType* info;	//����Ԫ���е�������Ϣ
}ElemType;

typedef struct
{
	ElemType *elem;	//����Ԫ�ش洢�ռ��ַ������ʱ��ʵ�ʳ��ȷ��䣬0�ŵ�Ԫ����
	int length;		//����
}SSTable;

//����PPT�ϵ���֪����
#define ELENGTH 11
int KeyArr[ELENGTH] = {5, 13, 19, 21, 37, 56, 64, 75, 80, 88, 92};	
void PrintHL(SSTable ST,int low ,int high,int mid);
int Search_Bin(SSTable ST, KeyType key)
	//�������ST���۰������ؼ��ֵ���key������Ԫ�ء����ҵ�������ֵΪ��Ԫ���ڱ��е�λ�ã����򷵻�0��
{
	int low = 1, high = ST.length;			//�������ֵ
	while (low <= high)
	{
		int mid = (low + high) / 2;
		PrintHL(ST,low ,high,mid);
		if(EQ(key,ST.elem[mid].key))		//�ҵ�����Ԫ��
		{
			PrintHL(ST,low ,high,mid);
			return mid;
		}
		else if(LT(key, ST.elem[mid].key))	//������ǰ�������в���
		{
			high = mid - 1;
			PrintHL(ST,low ,high,mid);
		}
		else								//�ں�������в���
		{
			low = mid + 1;
			PrintHL(ST,low ,high,mid);
		}
	}
	return 0;								//˳����в����ڴ���Ԫ��
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