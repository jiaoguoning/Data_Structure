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
	Triple data[MAXSIZE + 1];	//����Ԫ��Ԫ���
	int rpos[MAXRC + 1];		//���е�һ������Ԫ��λ�ñ�MAXRC�����ֵ��Ҫ�����еĸ����ģ�
	//rpos[0]���ñ仯
	int mu,nu,tu;			//����������������ͷ���Ԫ�ĸ���
}RLSMatrix;

int MultSMatrix(RLSMatrix M,RLSMatrix N,RLSMatrix &Q)
	//�����˻��������߼��洢
{
	int arow,ii;
	int *ctemp = (int*)malloc((N.nu + 1)*sizeof(int));//ctemp[0]λ�ò���Ԫ��
	if(M.nu != N.mu)	return 0;
	Q.mu = M.mu;	Q.nu = N.nu;	Q.tu = 0;
	if(M.tu * N.tu != 0)
	{
		for(arow = 1;arow <= M.mu;++arow)	//����M��ÿһ��,�����к�ƥ��Ѱ�ң����Ƿ���Ԫ��Ԫ��˳���ĵڼ���
		{
			int tp, p,ccol;					//tp�����arow+1�е�һ������Ԫ��λ��					
			for(ii = 0;ii <= N.nu;++ii)		//��ǰ�и�Ԫ���ۼ������㣬���������forѭ���н��� 
				ctemp[ii] = 0;				//ctemp���±�ʵ���϶�Ӧ����Q.data[q].j
			Q.rpos[arow] = Q.tu + 1;		//��ǰҪ�����λ�þ��ǵ�arow��һ������Ԫλ��
			if(arow < M.mu)
				tp = M.rpos[arow+1];
			else							//ָ����arow��M.mu��ȵ����
				tp = M.tu + 1;				//ΪʲôҪ����Ԫ������1��
											//��Ϊ���ڵ�һ������Ԫ�кź�������ȵ����
											//��ôѭ���ķ�Χ[rpos[M.mu],M.tu+1)
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
