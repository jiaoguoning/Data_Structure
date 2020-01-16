#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define Status      int
#define OK          1
#define ERROR       0
#define OVERFLOW    -2


#define MAX_ARRAY_DIM 8
typedef struct{
	int *base;		//数组元素的基址，由InitArray分配
	int dim;		//数组维数
	int *bounds;	//等价整型数组存各维的长度，由InitArray分配，对于7页4行5列bounds[0]页bounds[1]行bounds[2]列
	int *constants;	//数组映像函数常量基址，每变化一维的跨度，由InitArray分配，
	// 对于7页4行5列constants[0]代表1页的跨度，constants[1]代表1行的跨度，constants[2]代表1列的跨度
}Array;

Status InitArray(Array *A,int dim,...)//...省略部分为每一维长度
{	//若维数dim和各维长度合法，则构造相应的数组A，并返回1

	int elemtotal,i;
	va_list ap;
	if(dim < 1 || dim > MAX_ARRAY_DIM)
	{
		printf("输入维数dim有误！\n");
		return ERROR;
	}
	A->dim = dim;
	A->bounds = (int *)malloc(dim * sizeof(int));
	if(!A->bounds)
	{
		printf("申请空间失败！\n");
		exit(OVERFLOW);
	}
	//若各维长度合法，则存入A->bounds，并求出A的元素总数elemtotal
	elemtotal = 1;
	va_start(ap,dim);			//ap为va_list类型，是指向存放变长参数表信息的数组的指针
	//printf("%d\n",sizeof(ap));// 4

	for (i = 0; i < dim; i++)
	{
		//printf("%p\n",ap);			// 010FFCA0 010FFCA4 010FFCA8
		A->bounds[i] = va_arg(ap,int);	//每执行完一次 ap++(指针向后移动一位)
		if (A->bounds[i] < 0)
			return -1;
		elemtotal *= A->bounds[i];		//每维的长度相乘可得到容纳数据的总数
	}
	va_end(ap);							//释放ap指向的内存，并将ap指针赋值为 NULL
	//printf("%p\n",ap);				//00000000
	A->base = (int *)malloc(elemtotal * sizeof(int));
	if(!A->base)
	{
		printf("申请空间失败！\n");
		exit(OVERFLOW);
	}
	//求映像函数的常数ci，并存入A->constants[i-1],i = 1,...,dim
	A->constants = (int *)malloc(dim * sizeof(int));
	if(!A->constants)
	{
		printf("申请空间失败！\n");
		exit(OVERFLOW);
	}
	A->constants[dim-1] = 1;//L = 1，指针的增减以元素大小为单位
	for (i = dim - 2; i >= 0; --i)
		A->constants[i] = A->bounds[i+1] * A->constants[i+1];
	return OK;
}

Status DestroyArray(Array *A)
{
	if(!A->base)
	{
		printf("base指针为空，无法释放！\n");
		return ERROR;
	}
	free(A->base);
	A->base = NULL;

	if(!A->bounds)
	{
		printf("bounds指针为空，无法释放！\n");
		return ERROR;
	}
	free(A->bounds);
	A->bounds = NULL;
	if(!A->constants)
	{
		printf("constants指针为空，无法释放！\n");
		return ERROR;
	}
	free(A->constants);
	A->constants = NULL;
	return OK;
}

Status Locate(Array A,va_list ap,int *off)
	//若ap指示的各下标值合法，则求出该元素在A中相对地址off
{	//(off实际上就是相对于下标为0的元素（或者说是A.base指向内存的元素）向后移动了几个元素）
	int i,ind;
	*off = 0;
	for (i = 0; i < A.dim; i++)
	{
		ind = va_arg(ap,int);
		if(ind < 0 || ind >= A.bounds[i])
			return ERROR;
		*off += A.constants[i] * ind;
	}
	return OK;
}

Status Value(Array A,int *e,...)
	//A是n维数组，e为元素变量，随后是n个下标值。
	//若各下标不越界，则e赋值为所指定的A的元素值，并返回1。
{
	va_list ap;
	int off,result;
	va_start(ap,*e);
	if((result = Locate(A,ap,&off)) <= 0)
		return result;
	*e = *(A.base + off);
	return OK;
}

Status Assign(Array *A,int e,...)
	//A为n维数组，e为元素变量，随后是n个下标值。
	//若下标不越界，则将e的值赋给所指定的A的元素，并返回1。
{
	va_list ap;
	int off,result;
	va_start(ap,e);
	if((result = Locate(*A,ap,&off)) <= 0)
		return result;
	*(A->base + off) = e;
	return OK;
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

int main(void)
{
	Array a;
	int i,j,k;
	InitArray(&a,3,7,4,5);
	for (i = 0; i < 7; i++)
		for (j = 0; j < 4; j++)
			for ( k = 0; k < 5; k ++)
				Assign(&a,j+k,i,j,k);
	PrintArray(a);

	return 0;
}