#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 12500	//����Ԫ�ĸ������ֵΪ12500
#define MAXRC 250
#define Status int
#define OK 1
#define ERROR 0
#define OVERFLOW -2

#define ElemType int
typedef struct
{
	int i, j;
	ElemType e;
}Triple;

typedef struct
{
	Triple data[MAXSIZE + 1];
	int rpos[MAXRC + 1];	//���е�һ������Ԫ��λ�ñ�
	int mu, nu, tu;			//����������������ͷ���Ԫ����
}RLSMatrix;

int ctemp[10];
Status MultSMatrix(RLSMatrix M, RLSMatrix N, RLSMatrix &Q)
{	//�������Q = M * N���������߼����Ӵ洢��ʾ
	int arow, brow, p, q, ccol, tp, ii;
	if(M.nu != N.mu)
		return ERROR;
	Q.mu = M.mu;	Q.nu = N.nu;	Q.tu = 0;
	int *ctemp = (int*)malloc((N.nu + 1)*sizeof(int));//ctemp[0]λ�ò���Ԫ��
	if(M.tu * N.tu != 0)
	{
		for (arow = 1; arow <= M.mu; ++arow)
		{
			for(ii = 1; ii <= N.nu; ++ii)
				ctemp[ii] = 0;
			Q.rpos[arow] = Q.tu + 1;
			if(arow < M.mu)
				tp = M.rpos[arow + 1];
			else
				tp = M.tu + 1;
			for(p = M.rpos[arow];p < tp;++p)
			//M���к�N����ƥ����͵Ĺ��̣�����õ��ۼӺͷ���ctemp����
			{
				int t,q,qq,tt;
				int brow = M.data[p].j;	//�ҵ���ӦԪ����N�е��к�(��ΪN���кź�M���к����)
				if(brow < N.mu)
					t = N.rpos[brow+1];
				else
					t = N.tu + 1;
				qq = N.rpos[brow];
				tt = t;
				for(q = N.rpos[brow];q < t;++q)
				{
					ccol = N.data[q].j;	//�˻�Ԫ����Q���к�
					ctemp[ccol] += M.data[p].e * N.data[q].e;
				}
			}//���Q�е�crow��=arow���еķ���Ԫ
			for(ccol = 1;ccol <= Q.nu;++ccol)//ѹ���洢���еķ���Ԫ
				//����õĽ������Q����Ԫ��Ԫ��˳����еĹ���
			{
				if(ctemp[ccol])				//�ж�����Ľ���Ƿ�Ϊ�㣬��������㣬����Q.data		
				{
					if(++Q.tu > MAXSIZE)
						return 0;
					Q.data[Q.tu].i = arow;
					Q.data[Q.tu].j = ccol;
					Q.data[Q.tu].e = ctemp[ccol];
				}
			}
		}
	}
	free(ctemp);
	return OK;
}

void MatrixPrint(RLSMatrix M)
{
	int i, j, p = 1;
	for (i = 1; i <= M.mu; i++)
	{
		for (j = 1; j <= M.nu; j++)
			if(i == M.data[p].i && j == M.data[p].j)
				printf("%3d ",M.data[p++].e);
			else
				printf("%3d ",0);
		printf("\n");
	}
}

int main(void)
{
	RLSMatrix m,n,r;
	int i;
	Triple mdata[4] = {{1,1,3},{1,4,5},{2,2,-1},{ 3,1,2}};
	Triple ndata[4] = {{1,2,2},{2,1,1},{3,1,-2},{3,2,4}};

	for ( i = 1; i <= 4; ++i)
	{
		m.data[i] = mdata[i-1];
		n.data[i] = ndata[i-1];
	}
	m.mu = 3;	m.nu = 4;	m.tu = 4;
	m.rpos[1] = 1;	m.rpos[2] = 3;	m.rpos[3] = 4;	
	n.mu = 4;	n.nu = 2;	n.tu = 4;
	n.rpos[1] = 1;	n.rpos[2] = 2;	n.rpos[3] = 3;	n.rpos[4] = 5;
	printf("M��������:\n");
	MatrixPrint(m);
	printf("N��������:\n");
	MatrixPrint(n);
	MultSMatrix(m, n, r);
	printf("M*N��������:\n");
	MatrixPrint(r);

	return 0;
}