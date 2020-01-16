#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 12500

typedef struct{
	int i,j;		//行数，列数
	int e;			//元素值
}Triple;

typedef struct{
	Triple data[MAXSIZE + 1];	//矩阵中非零元三元组表，data[0]未用
	int mu,nu,tu;				//矩阵的行数、列数和非零元个数
	//因为data中我只知道三元组顺序表的容量MAXSIZE，而不知道三元组顺序表的长度
}TSMatrix;

int TransposeSMatrix(TSMatrix M,TSMatrix *T)
	//采用三元组表存储表示，求稀疏矩阵M的转置矩阵T
{
	//循环中为什么不用i、j，因为i j已经在三元组中使用了，再使用不利于阅读代码
	int col,p,q = 1;
	T->mu = M.nu;
	T->nu = M.mu;
	T->tu = M.tu;

	if (!T->tu)
		return 1;
	//对每一列进行循环，在三元组中找对应的元素
	for ( col = 1; col <= M.nu;  col++)	
	{
		for (p = 1; p <= M.tu; p++)
		{
			//三元组中如果列号相同，行号小的肯定先出现，因为我是行为主序存放的
			if(col == M.data[p].j)
			{
				T->data[q].i = M.data[p].j;
				T->data[q].j = M.data[p].i;
				T->data[q].e = M.data[p].e;
				++q;						//q是从1开始的，因为data[0]未用
			}
		}
	}
	return 1;
}

int FastTransposeSMatrix(TSMatrix M,TSMatrix *T)
	//采用三元组顺序表存储表示，求稀疏矩阵M的转置矩阵T。
{
	int col,t,p,q;
	int *num = (int *)malloc((M.nu + 1) * sizeof(int));//因为矩阵下标从1开始，因此多申请一个位置
	int *cpot = (int *)malloc((M.nu + 1) * sizeof(int));//因为矩阵下标从1开始，因此多申请一个位置
	T->mu = M.nu;
	T->nu = M.mu;
	T->tu = M.tu;
	if (!T->tu)
		return 1;
	for(col = 1; col <= M.nu; ++col)//num[0]没有用，为了和矩阵的下标对应
		num[col] = 0;
	for (t = 1; t <= M.tu; ++t)
		++num[M.data[t].j];
	cpot[1] = 1;
	//求第col列中第一个非零元在b.data中的序号
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

