#include <stdio.h>
//---------     引用与函数调用     ---------

void Myswap1(int a,int b)
{
	int c = a;
	a = b;
	b = c;
}

void Myswap2(int &a,int &b)
{
	int c = a;
	a = b;
	b = c;
}

void Myswap3(int *pa,int *pb)
{
	int c = *pa;
	*pa = *pb;
	*pb = c;
}

int main(void)
{
	int a = 1;
	int b = 2;
	int &ra = a;
	int *pa = &a;
	ra = 100;
	printf("&a = %p, a = %d\n",&a,a);
	printf("&ra = %p, ra = %d\n\n",&ra,a);
	*pa = 200;
	printf("&a = %p, a = %d\n",&a,a);
	printf("&ra = %p, ra = %d\n",&ra,a);
	printf("pa = %p, *pa = %d\n\n",pa,*pa);

	Myswap1(a,b);
	printf("Myswap1: a = %d,b = %d\n",a,b);
	Myswap2(a,b);
	printf("Myswap2: a = %d,b = %d\n",a,b);
	Myswap3(&a,&b);
	printf("Myswap3: a = %d,b = %d\n",a,b);

	return 0;
}
