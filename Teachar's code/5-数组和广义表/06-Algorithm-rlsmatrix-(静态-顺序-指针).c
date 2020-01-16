#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE     12500	//非零元的个数最大值为12500
#define MAXRC       250
#define Status      int
#define OK          1
#define ERROR       0
#define OVERFLOW    -2

#define ElemType int
typedef struct
{
	int i, j;
	ElemType e;
}Triple;

typedef struct
{
	Triple data[MAXSIZE + 1];
	int rpos[MAXRC + 1];	//各行第一个非零元的位置表
	int mu, nu, tu;			//矩阵的行数、列数和非零元个数
}RLSMatrix;


// 算法5.3  
Status MultSMatrix(RLSMatrix M, RLSMatrix N, RLSMatrix *Q)
{	//矩阵相乘Q = M * N，采用行逻辑链接存储表示
	int arow, brow, p, q, ccol, tp, ii;
    int *ctemp;
	if(M.nu != N.mu)
		return ERROR;
	(*Q).mu = M.mu;	(*Q).nu = N.nu;	(*Q).tu = 0;
	ctemp = (int*)malloc((N.nu + 1)*sizeof(int));//ctemp[0]位置不放元素
	if(M.tu * N.tu != 0)
	{
		for (arow = 1; arow <= M.mu; ++arow)
		{
			for(ii = 1; ii <= N.nu; ++ii)
				ctemp[ii] = 0;
			(*Q).rpos[arow] = (*Q).tu + 1;
			if(arow < M.mu)
				tp = M.rpos[arow + 1];
			else
				tp = M.tu + 1;
			for(p = M.rpos[arow];p < tp;++p)
			//M的列和N的行匹配求和的过程，将求得的累加和放入ctemp数组
			{
				int t,q,qq,tt;
				int brow = M.data[p].j;	//找到对应元素在N中的行号(因为N中行号和M中列号相等)
				if(brow < N.mu)
					t = N.rpos[brow+1];
				else
					t = N.tu + 1;
				qq = N.rpos[brow];
				tt = t;
				for(q = N.rpos[brow];q < t;++q)
				{
					ccol = N.data[q].j;	//乘积元素在Q中列号
					ctemp[ccol] += M.data[p].e * N.data[q].e;
				}
			}//求得Q中第crow（=arow）行的非零元
			for(ccol = 1;ccol <= (*Q).nu;++ccol)//压缩存储该行的非零元
				//将求得的结果存入Q非零元三元组顺序表中的过程
			{
				if(ctemp[ccol])				//判断求出的结果是否为零，如果不是零，存入Q.data		
				{
					if(++(*Q).tu > MAXSIZE)
						return 0;
					(*Q).data[(*Q).tu].i = arow;
					(*Q).data[(*Q).tu].j = ccol;
					(*Q).data[(*Q).tu].e = ctemp[ccol];
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
	printf("M矩阵如下:\n");
	MatrixPrint(m);
	printf("N矩阵如下:\n");
	MatrixPrint(n);
	MultSMatrix(m, n, &r);
	printf("M*N矩阵如下:\n");
	MatrixPrint(r);

	return 0;
}