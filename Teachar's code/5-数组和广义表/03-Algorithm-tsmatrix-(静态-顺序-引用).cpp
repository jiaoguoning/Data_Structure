#include <stdio.h>
#include <stdlib.h>

#define Status      int
#define OK          1
#define ERROR       0
#define OVERFLOW    -2

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

// 算法5.1 
Status TransposeSMatrix(TSMatrix M,TSMatrix &T)
{	//采用三元组表存储表示，求稀疏矩阵M的转置矩阵T
    //循环中为什么不用i、j，因为i j已经在三元组中使用了，再使用不利于阅读代码
    int col,p,q = 1;
    T.mu = M.nu;
    T.nu = M.mu;
    T.tu = M.tu;
    if (T.tu){
        //对每一列进行循环，在三元组中找对应的元素
        for ( col = 1; col <= M.nu;  col++)	
            for (p = 1; p <= M.tu; p++)
                //三元组中如果列号相同，行号小的肯定先出现，因为我是行为主序存放的
                    if(col == M.data[p].j)
                    {
                        T.data[q].i = M.data[p].j;
                        T.data[q].j = M.data[p].i;
                        T.data[q].e = M.data[p].e;
                        ++q;	//q是从1开始的，因为data[0]未用
                    }
    }
    return OK;
}

// 算法5.2 
Status FastTransposeSMatrix(TSMatrix M,TSMatrix &T)
	//采用三元组顺序表存储表示，求稀疏矩阵M的转置矩阵T。
{
	int col,t,p,q;
	int *num = (int *)malloc((M.nu + 1) * sizeof(int));//因为矩阵下标从1开始，因此多申请一个位置
	int *cpot = (int *)malloc((M.nu + 1) * sizeof(int));//因为矩阵下标从1开始，因此多申请一个位置
    T.mu = M.nu;
    T.nu = M.mu;
    T.tu = M.tu;
    if (T.tu){
        //num[0]没有用，为了和矩阵的下标对应
        for(col = 1; col <= M.nu; ++col)
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
            T.data[q].i = M.data[p].j;
            T.data[q].j = M.data[p].i;
            T.data[q].e = M.data[p].e;
            ++cpot[col];
        }
    }
    return OK;
}

void MatrixPrint(TSMatrix M)
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
	TSMatrix m,T,n;
	int i;
	Triple Data[8] = {{1,2,12}, {1,3,9}, {3,1,-3},  
	{3,6,14}, {4,3,24}, {5,2,18}, {6,1,15}, {6,4,-7}};
	for(i = 1; i <= 8; ++i)
		m.data[i] = Data[i-1];
	m.mu = 6;
	m.nu = 7;
	m.tu = 8;
	printf("M矩阵如下：\n");
	MatrixPrint(m);
	FastTransposeSMatrix(m, T);
	printf("M的快速转置矩阵T为：\n");
	MatrixPrint(T);
	TransposeSMatrix(m, T);
	printf("M的转置矩阵为：\n");
	MatrixPrint(T);


	return 0;
}
