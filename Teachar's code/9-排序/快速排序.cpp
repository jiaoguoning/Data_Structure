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

void printData(SqList L,int low,int high);

int Partition1(SqList &L, int low,int high)
	//����˳���L���ӱ�L.r[low...high]�ļ�¼��ʹ�����¼��λ��������������λ��
	//��ʱ����֮ǰ���󣩵õ���¼������С��������
{
	RedType temp;
	KeyType pivotkey = L.r[low].key;	//���ӱ��һ����¼�������¼
	while (low < high)					//�ӱ�����˽�������м�ɨ��
	{
		while (low < high && L.r[high].key >= pivotkey)	//Ϊʲôȡ�Ⱥţ���Ϊ������ȵ����
			--high;										//�����������Լ��ٽ������������Ч��
		temp = L.r[high];				//���������¼С�ļ�¼�������Ͷ�
		L.r[high] = L.r[low];
		L.r[low] = temp;
		while (low < high && L.r[low].key <= pivotkey)
			++low;
		temp = L.r[high];				//���������¼��ĵļ�¼�������߶�
		L.r[high] = L.r[low];
		L.r[low] = temp;
	}
	return low;							//������������λ��
}


int Partition2(SqList &L, int low,int high)
{
	KeyType pivotkey;
	L.r[0] = L.r[low];					//���ӱ�ĵ�һ����¼�������¼
	pivotkey = L.r[low].key;			//�����¼�ؼ���
	printData(L,low,high);
	while(low < high)
	{
		while (low < high && L.r[high].key >= pivotkey)	//Ϊʲôȡ�Ⱥţ���Ϊ������ȵ����
		{												//�����������Լ��ٽ������������Ч��
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
	L.r[low] = L.r[0];					//�����¼��λ
	printData(L,low,high);
	return low;							//��������λ��
}

void QSort(SqList &L,int low,int high)
	//��˳���L�е�������L.r[low...high]����������
{
	int pivotloc;							//���ڴ洢���ص�����λ��
	if(low < high)							//���ȴ���1
	{
		pivotloc = Partition2(L,low,high);	//��L.r[low...high]һ��Ϊ��
		QSort(L, low,pivotloc - 1);			//���ӱ�ݹ�����pivotloc��һ��Ϊ��������λ��
		QSort(L, pivotloc + 1,high);		//�Ը��ӱ�ݹ�����
	}
}

void QuickSort(SqList &L)
	//��˳���L����������
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