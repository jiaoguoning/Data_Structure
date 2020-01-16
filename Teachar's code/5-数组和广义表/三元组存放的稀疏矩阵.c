#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 12500

typedef struct{
	int i,j;		//����������
	int e;			//Ԫ��ֵ
}Triple;

typedef struct{
	Triple data[MAXSIZE + 1];	//�����з���Ԫ��Ԫ���data[0]δ��
	int mu,nu,tu;				//����������������ͷ���Ԫ����
	//��Ϊdata����ֻ֪����Ԫ��˳��������MAXSIZE������֪����Ԫ��˳���ĳ���
}TSMatrix;

int TransposeSMatrix(TSMatrix M,TSMatrix *T)
	//������Ԫ���洢��ʾ����ϡ�����M��ת�þ���T
{
	//ѭ����Ϊʲô����i��j����Ϊi j�Ѿ�����Ԫ����ʹ���ˣ���ʹ�ò������Ķ�����
	int col,p,q = 1;
	T->mu = M.nu;
	T->nu = M.mu;
	T->tu = M.tu;

	if (!T->tu)
		return 1;
	//��ÿһ�н���ѭ��������Ԫ�����Ҷ�Ӧ��Ԫ��
	for ( col = 1; col <= M.nu;  col++)	
	{
		for (p = 1; p <= M.tu; p++)
		{
			//��Ԫ��������к���ͬ���к�С�Ŀ϶��ȳ��֣���Ϊ������Ϊ�����ŵ�
			if(col == M.data[p].j)
			{
				T->data[q].i = M.data[p].j;
				T->data[q].j = M.data[p].i;
				T->data[q].e = M.data[p].e;
				++q;						//q�Ǵ�1��ʼ�ģ���Ϊdata[0]δ��
			}
		}
	}
	return 1;
}

int FastTransposeSMatrix(TSMatrix M,TSMatrix *T)
	//������Ԫ��˳���洢��ʾ����ϡ�����M��ת�þ���T��
{
	int col,t,p,q;
	int *num = (int *)malloc((M.nu + 1) * sizeof(int));//��Ϊ�����±��1��ʼ����˶�����һ��λ��
	int *cpot = (int *)malloc((M.nu + 1) * sizeof(int));//��Ϊ�����±��1��ʼ����˶�����һ��λ��
	T->mu = M.nu;
	T->nu = M.mu;
	T->tu = M.tu;
	if (!T->tu)
		return 1;
	for(col = 1; col <= M.nu; ++col)//num[0]û���ã�Ϊ�˺;�����±��Ӧ
		num[col] = 0;
	for (t = 1; t <= M.tu; ++t)
		++num[M.data[t].j];
	cpot[1] = 1;
	//���col���е�һ������Ԫ��b.data�е����
	for(col = 2; col <= M.nu; ++col)
		cpot[col] = cpot[col-1]+num[col-1];
	for ( p = 1; p <= M.tu; p++)
	{
		col = M.data[p].j;
		q = cpot[col];
		T->data[q].i = M.data[p].j;
		T->data[q].j = M.data[p].i;
		T->data[q].e = M.data[p].e;
		++cpot[col];
	}

	return 1;
}

int main(void)
{
	Triple t1 = {1,2,-12};
	Triple t2 = {3,4,-1};

	TSMatrix m,T,n;
	m.data[1] = t1;
	m.data[2] = t2;
	m.mu = 4;
	m.nu = 5;
	m.tu = 2;

	FastTransposeSMatrix(m,&T);

	TransposeSMatrix(T,&n);








	return 0;
}

