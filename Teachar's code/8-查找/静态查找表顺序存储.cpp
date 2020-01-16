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
int KeyArr[ELENGTH] = {5, 37, 19, 21, 13, 56, 64, 92, 88, 80, 75};	

int Search_Seq(SSTable ST, KeyType key)
	//��˳���ST��˳�������ؼ��ֵ���key������Ԫ�ء����ҵ�������ֵΪ��Ԫ���ڱ��е�λ�ã����򷵻�0.
{
	int i;
	ST.elem[0].key = key;
	for(i = ST.length; !EQ(ST.elem[i].key,key); --i);
	return i;
}

void PrintSStable(SSTable ST)
{
	int i;
	for(i = 1;i <= ST.length; ++i)
		printf("%d ",ST.elem[i].key);
	printf("\n");
}

int main(void)
{
	int i ;		SSTable ST;
	ST.elem = (ElemType *)malloc(sizeof(ElemType) * ELENGTH + 1);
	ST.length = ELENGTH;
	for(i = 1;i <= ST.length; ++i)
		ST.elem[i].key = KeyArr[i-1];
	PrintSStable(ST);
	printf("%d\n",Search_Seq(ST, 64));

	return 0;
}