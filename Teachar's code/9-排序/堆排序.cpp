#include <stdio.h>

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

typedef SqList HeapType;	//�Ѳ���˳���洢��ʾ

void printData(SqList L,int s,int m);

void HeapAdjust(HeapType &H,int s,int m)
	//��֪H.r[s...m]�м�¼�Ĺؼ��ֳ�H.r[s].key֮�������ѵĶ��壬����������H.r[s]
	//�Ĺؼ��֣�ʹH.r[s...m]��Ϊһ���󶥶ѣ������м�¼�Ĺؼ��ֶ��ԣ�
	//���¶������δ����󶥶ѣ����ֻ�ı��������
{
	int j;
	for(j = 2 * s;j <= m; j *= 2)	//��key�ϴ�ĺ��ӽ������ɸѡ
	{
		if( j < m && LT(H.r[j].key,H.r[j+1].key))
			++j;					//j�����ӽڵ���Ϊkey�ϴ��¼���±�
		printData(H,s,m);
		if(!LT(H.r[s].key,H.r[j].key))
			break;					//���ӽ��ϴ�keyֵ�͸����s�Ƚϣ���С�ڸ��ڵ�key������ѭ��
		H.r[0] = H.r[s];			//���򣬽���keyֵ�ϴ��ӽ��͸����
		H.r[s] = H.r[j];
		H.r[j] = H.r[0];			
		printData(H,s,m);
   		s = j;						//������ɺ󣬼����Ƚ��ӽ��j��Ӧ���ӽ��
		printData(H,-1,m);
	}
}

void HeapSort(HeapType &H)
	//��˳���H���ж�����
{
	int i;
	RedType temp;
	for(i = H.length / 2; i > 0; --i)//��H.r[1...H.length]���ɴ󶥶�
	{
		HeapAdjust(H, i, H.length);	 //�����һ�����ն˽�㿪ʼ�����ε������еĽ�㣬ʹ֮��Ϊ�󶥶�
	}
	for(i = H.length; i > 1; --i)
	{
		H.r[0] = H.r[1];			 //���Ѷ���¼�͵�ǰδ������������H.r[1...i]��
		H.r[1] = H.r[i];			 //���һ����¼�໥����
		H.r[i] = H.r[0];
		printData(H,-1,-1);
		HeapAdjust(H, 1, i-1);	//��H.r[1...i-1]���µ���Ϊ�󶥶�
								//��Ϊ�Ѿ���Ϊ�󶥶ѣ�ֻ�Ǹ�����൱�ڲ���һ��Ԫ��
								//����ֻ��Ҫ������1������㼴��
	}
}


void printData(SqList L,int s,int m)
{
	int i;
	for (i = 1; i <= L.length; ++i)
		printf("%2d  ", L.r[i].key);
	printf("\n");
	for (i = 1; i <= m; ++i)
	{
		if(i == s)
			printf("||  ");
		else if(i == 2 * s)
			printf("|L  ");
		else if(i == 2 * s + 1)
			printf("R|  ");
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
	printData(L,-1,-1);
	HeapSort(L);
	printData(L,-1,-1);

	return 0;
} 