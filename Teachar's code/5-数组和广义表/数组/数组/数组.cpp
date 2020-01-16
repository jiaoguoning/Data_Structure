#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_ARRAY_DIM 8
typedef struct{
	int *base;		//����Ԫ�صĻ�ַ����InitArray����
	int dim;		//����ά��
	int *bounds;	//�ȼ�����������ά�ĳ��ȣ���InitArray���䣬����7ҳ4��5��bounds[0]ҳbounds[1]��bounds[2]��
	int *constants;	//����ӳ����������ַ��ÿ�仯һά�Ŀ�ȣ���InitArray���䣬
	//����7ҳ4��5��constants[0]����1ҳ�Ŀ�ȣ�constants[1]����1�еĿ�ȣ�constants[2]����1�еĿ��
}Array;

int InitArray(Array *A,int dim,...)//...ʡ�Բ���Ϊÿһά����
	//��ά��dim�͸�ά���ȺϷ���������Ӧ������A��������1
{
	int elemtotal,i;
	va_list ap;
	if(dim < 1 || dim > MAX_ARRAY_DIM)
	{
		printf("����ά��dim����\n");
		return 0;
	}
	A->dim = dim;
	A->bounds = (int *)malloc(dim * sizeof(int));
	if(!A->bounds)
	{
		printf("����ռ�ʧ�ܣ�\n");
		exit(1);
	}
	//����ά���ȺϷ��������A->bounds�������A��Ԫ������elemtotal
	elemtotal = 1;
	va_start(ap,dim);			//apΪva_list���ͣ���ָ���ű䳤��������Ϣ�������ָ��
	//printf("%d\n",sizeof(ap));// 4

	for (i = 0; i < dim; i++)
	{
		//printf("%p\n",ap);			// 010FFCA0 010FFCA4 010FFCA8
		A->bounds[i] = va_arg(ap,int);	//ÿִ����һ�� ap++(ָ������ƶ�һλ)
		if (A->bounds[i] < 0)
			return -1;
		elemtotal *= A->bounds[i];		//ÿά�ĳ�����˿ɵõ��������ݵ�����
	}
	va_end(ap);							//�ͷ�apָ����ڴ棬����apָ�븳ֵΪ NULL
	//printf("%p\n",ap);				//00000000
	A->base = (int *)malloc(elemtotal * sizeof(int));
	if(!A->base)
	{
		printf("����ռ�ʧ�ܣ�\n");
		exit(1);
	}
	//��ӳ�����ĳ���ci��������A->constants[i-1],i = 1,...,dim
	A->constants = (int *)malloc(dim * sizeof(int));
	if(!A->constants)
	{
		printf("����ռ�ʧ�ܣ�\n");
		exit(1);
	}
	A->constants[dim-1] = 1;//L = 1��ָ���������Ԫ�ش�СΪ��λ
	for (i = dim - 2; i >= 0; --i)
		A->constants[i] = A->bounds[i+1] * A->constants[i+1];
	return 1;
}

int DestroyArray(Array *A)
{
	if(!A->base)
	{
		printf("baseָ��Ϊ�գ��޷��ͷţ�\n");
		return 0;
	}
	free(A->base);
	A->base = NULL;

	if(!A->bounds)
	{
		printf("boundsָ��Ϊ�գ��޷��ͷţ�\n");
		return 0;
	}
	free(A->bounds);
	A->bounds = NULL;
	if(!A->constants)
	{
		printf("constantsָ��Ϊ�գ��޷��ͷţ�\n");
		return 0;
	}
	free(A->constants);
	A->constants = NULL;
	return 1;
}

int Locate(Array A,va_list ap,int *off)
	//��apָʾ�ĸ��±�ֵ�Ϸ����������Ԫ����A����Ե�ַoff
	//(offʵ���Ͼ���������±�Ϊ0��Ԫ�أ�����˵��A.baseָ���ڴ��Ԫ�أ�����ƶ��˼���Ԫ�أ�
{
	int i,ind;
	*off = 0;
	for (i = 0; i < A.dim; i++)
	{
		ind = va_arg(ap,int);
		if(ind < 0 || ind >= A.bounds[i])
			return 0;
		*off += A.constants[i] * ind;
	}
	return 1;
}

int Value(Array A,int *e,...)
	//A��nά���飬eΪԪ�ر����������n���±�ֵ��
	//�����±겻Խ�磬��e��ֵΪ��ָ����A��Ԫ��ֵ��������1��
{
	va_list ap;
	int off,result;
	va_start(ap,*e);
	if((result = Locate(A,ap,&off)) <= 0)
		return result;
	*e = *(A.base + off);
	return 1;
}

int Assign(Array *A,int e,...)
	//AΪnά���飬eΪԪ�ر����������n���±�ֵ��
	//���±겻Խ�磬��e��ֵ������ָ����A��Ԫ�أ�������1��
{
	va_list ap;
	int off,result;
	va_start(ap,e);
	if((result = Locate(*A,ap,&off)) <= 0)
		return result;
	*(A->base + off) = e;
	return 1;
}

void PrintArray(Array A)
{
	int i,j,k;
		
	for (i = 0; i < A.bounds[0]; i++)
	{
		for (j = 0; j < A.bounds[1]; j++)
		{
			for ( k = 0; k < A.bounds[2]; k ++)
			{
					printf("%d",A.base[i+j+k]);
			}
			printf("\n");
		}
		printf("\n");
	}
}

void ToLocate(Array A, int *off,...)
{
	va_list ap;
	va_start(ap,off);		
	Locate(A,ap,off);
}

int main(void)
{
	Array a;
	int i,j,k;
	int off;
	InitArray(&a,3,7,4,5);
	for (i = 0; i < 7; i++)
		for (j = 0; j < 4; j++)
			for ( k = 0; k < 5; k ++)
				Assign(&a,j+k,i,j,k);
	PrintArray(a);
	ToLocate(a,&off,3,2,4);
	printf("3ҳ2��4�и�Ԫ�����ַ�����ֽ���(ƫ����)�� %d\n",off);

	return 0;
}