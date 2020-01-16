#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define	INFINITY INT_MAX	//���͵����ֵ��
//�շ������ͺշ�������Ĵ洢��ʾ
typedef struct
{
	unsigned int weight;	//Ȩ��
	unsigned int parent,lchild,rchild;
}HTNode, *HuffmanTree;		//��̬��������洢�շ�����
typedef char ** HuffmanCode;//��̬��������洢�շ��������

//ѡ���޸���㣬����Ȩֵ��С��������㣬��ֵ��s1��s2 
void Select(HuffmanTree &HT,int x,int &s1,int &s2)
{
	int i = 1,min1 = INFINITY,min2 = INFINITY;
	for(i = 1;i <= x; i++)//����С 
		if(HT[i].weight < min1 && HT[i].parent == 0)
		{
			min1 = HT[i].weight;
			s1 = i;
		}
	for(i = 1;i <= x; i++)//�Ҵ�С 
		if(HT[i].weight < min2 && i != s1 && HT[i].parent == 0)
		{
			min2 = HT[i].weight;
			s2 = i;
		}
}

//�շ��������㷨
void HuffmanCoding(HuffmanTree &HT,HuffmanCode &HC,int *w,int n)
	//w���n���ַ���Ȩֵ����>0��������շ�����HT�������n���ַ��ĺշ�������HC
{
	int m,i;
	HuffmanTree p;
	char *cd;
	if(n <= 1)
		return ;
	m = 2 * n - 1;
	HT = (HuffmanTree)malloc((m+1) * sizeof(HTNode));	//0�ŵ�Ԫδ��
	for(p = HT + 1, i = 1; i <= n; ++i,++p,++w)
	{
		p->weight = *w;
		p->parent = 0;
		p->lchild = 0;
		p->rchild = 0;
	}
	for(;i <= m; ++i,++p)
	{
		p->weight = 0;
		p->parent = 0;
		p->lchild = 0;
		p->rchild = 0;

	}
	for(i = n + 1; i <= m; ++i)	//���շ�����
		//��HT[1...i-1]ѡ��parentΪ0��weight��С��������㣬����ŷֱ�Ϊs1��s2
	{
		int s1,s2;
		Select(HT,i-1,s1,s2);
		HT[s1].parent = i;	HT[s2].parent = i;
		HT[i].lchild = s1;	HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	//---��Ҷ�ӵ���������ȡÿ���ַ��ĺշ�������---
	HC = (HuffmanCode)malloc((n+1) * sizeof(char *));	//����n���ַ������ͷָ������
	cd = (char *)malloc(n * sizeof(char));				//���������Ĺ����ռ�
	cd[n - 1] = '\0';									//���������
	for(i = 1; i <= n; ++i)
	{

		int start = n - 1, c, f;
		//��Ҷ�ӵ������������
		for(c = i, f = HT[i].parent; f != 0; c = f,f = HT[f].parent)
		{
			if(HT[f].lchild == c)
				cd[--start] = '0';
			else
				cd[--start] = '1';
			HC[i] = (char *)malloc((n - start) * sizeof(char));	//Ϊ��i���ַ��������ռ�
			strcpy(HC[i], &cd[start]);
			//printf("%d�ĺշ�������Ϊ��%s\n",HT[i].weight,HC[i]);
		}
	}
	free(cd);	//�ͷŹ����ռ�
}

int main(void)
{
	HuffmanTree HT;
	HuffmanCode HC;
	int w[5] = {36, 10, 27, 10, 18};
	int i,n = 5;
	HuffmanCoding(HT,HC,w,n);
	for(i = 1;i <= n; ++i)
		printf("%d�ĺշ�������Ϊ��%s\n",HT[i].weight,HC[i]);
	return 0;
}