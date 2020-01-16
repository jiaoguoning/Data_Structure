#include <stdio.h>
#include <stdlib.h>
#define ElemType int
#define MAXSIZE 120
#define MAXRC 120



typedef struct{
	int i,j;
	ElemType e;
}Triple;

typedef struct{
	Triple data[MAXSIZE + 1];	//非零元三元组表
	int rpos[MAXRC + 1];		//各行第一个非零元的位置表（MAXRC的最大值是要满足行的个数的）
	//rpos[0]不用变化
	int mu,nu,tu;			//矩阵的行数、列数和非零元的个数
}RLSMatrix;

int MultSMatrix(RLSMatrix M,RLSMatrix N,RLSMatrix &Q)
	//求矩阵乘积采用行逻辑存储
{
	int arow,ii;
	int *ctemp = (int*)malloc((N.nu + 1)*sizeof(int));//ctemp[0]位置不放元素
	if(M.nu != N.mu)	return 0;
	Q.mu = M.mu;	Q.nu = N.nu;	Q.tu = 0;
	if(M.tu * N.tu != 0)
	{
		for(arow = 1;arow <= M.mu;++arow)	//处理M的每一行,按照行号匹配寻找，不是非零元三元组顺序表的第几行
		{
			int tp, p,ccol;					//tp代表第arow+1行第一个非零元的位置					
			for(ii = 0;ii <= N.nu;++ii)		//当前行各元素累加器清零，此项必须在for循环中进行 
				ctemp[ii] = 0;				//ctemp的下标实际上对应的是Q.data[q].j
			Q.rpos[arow] = Q.tu + 1;		//当前要插入的位置就是第arow行一个非零元位置
			if(arow < M.mu)
				tp = M.rpos[arow+1];
			else							//指的是arow和M.mu相等的情况
				tp = M.tu + 1;				//为什么要非零元个数加1？
											//因为对于第一个非零元行号和行数相等的情况
											//那么循环的范围[rpos[M.mu],M.tu+1)
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
			for(ccol = 1;ccol <= Q.nu;++ccol)//压缩存储该行的非零元
				//将求得的结果存入Q非零元三元组顺序表中的过程
			{
				if(ctemp[ccol])				//判断求出的结果是否为零，如果不是零，存入Q.data		
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
	return 1;
}

int main(void)
{
	int result;
	RLSMatrix M,N,Q;
	M.mu = 3;	M.nu = 4;	M.tu = 4;
	M.data[1].i = 1;	M.data[1].j = 1;	M.data[1].e = 3;
	M.data[2].i = 1;	M.data[2].j = 4;	M.data[2].e = 5;
	M.data[3].i = 2;	M.data[3].j = 2;	M.data[3].e = -1;
	M.data[4].i = 3;	M.data[4].j = 1;	M.data[4].e = 2;
	M.rpos[1] = 1;	M.rpos[2] = 3;	M.rpos[3] = 4;	M.rpos[4] = 5;

	N.mu = 4;	N.nu = 2;	N.tu = 4;
	N.data[1].i = 1;	N.data[1].j = 2;	N.data[1].e = 2;
	N.data[2].i = 2;	N.data[2].j = 1;	N.data[2].e = 1;
	N.data[3].i = 3;	N.data[3].j = 1;	N.data[3].e = -2;
	N.data[4].i = 3;	N.data[4].j = 2;	N.data[4].e = 4;
	N.rpos[1] = 1;	N.rpos[2] = 2;	N.rpos[3] = 3;	N.rpos[4] = 5;

	result = MultSMatrix(M,N,Q);
	printf("%d\n",result);

	return 0;
}
