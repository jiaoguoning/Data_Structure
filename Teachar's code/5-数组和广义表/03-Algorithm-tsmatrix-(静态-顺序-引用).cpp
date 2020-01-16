#include <stdio.h>
#include <stdlib.h>

#define Status      int
#define OK          1
#define ERROR       0
#define OVERFLOW    -2

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

// �㷨5.1 
Status TransposeSMatrix(TSMatrix M,TSMatrix &T)
{	//������Ԫ���洢��ʾ����ϡ�����M��ת�þ���T
    //ѭ����Ϊʲô����i��j����Ϊi j�Ѿ�����Ԫ����ʹ���ˣ���ʹ�ò������Ķ�����
    int col,p,q = 1;
    T.mu = M.nu;
    T.nu = M.mu;
    T.tu = M.tu;
    if (T.tu){
        //��ÿһ�н���ѭ��������Ԫ�����Ҷ�Ӧ��Ԫ��
        for ( col = 1; col <= M.nu;  col++)	
            for (p = 1; p <= M.tu; p++)
                //��Ԫ��������к���ͬ���к�С�Ŀ϶��ȳ��֣���Ϊ������Ϊ�����ŵ�
                    if(col == M.data[p].j)
                    {
                        T.data[q].i = M.data[p].j;
                        T.data[q].j = M.data[p].i;
                        T.data[q].e = M.data[p].e;
                        ++q;	//q�Ǵ�1��ʼ�ģ���Ϊdata[0]δ��
                    }
    }
    return OK;
}

// �㷨5.2 
Status FastTransposeSMatrix(TSMatrix M,TSMatrix &T)
	//������Ԫ��˳���洢��ʾ����ϡ�����M��ת�þ���T��
{
	int col,t,p,q;
	int *num = (int *)malloc((M.nu + 1) * sizeof(int));//��Ϊ�����±��1��ʼ����˶�����һ��λ��
	int *cpot = (int *)malloc((M.nu + 1) * sizeof(int));//��Ϊ�����±��1��ʼ����˶�����һ��λ��
    T.mu = M.nu;
    T.nu = M.mu;
    T.tu = M.tu;
    if (T.tu){
        //num[0]û���ã�Ϊ�˺;�����±��Ӧ
        for(col = 1; col <= M.nu; ++col)
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
	printf("M�������£�\n");
	MatrixPrint(m);
	FastTransposeSMatrix(m, T);
	printf("M�Ŀ���ת�þ���TΪ��\n");
	MatrixPrint(T);
	TransposeSMatrix(m, T);
	printf("M��ת�þ���Ϊ��\n");
	MatrixPrint(T);


	return 0;
}
