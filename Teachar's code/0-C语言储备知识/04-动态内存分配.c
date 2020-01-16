#include <stdio.h>
#include <stdlib.h>

//-------------    ∂ØÃ¨∑÷≈‰     -------------//
int main(void)
{
	int i;
	int *q;
	int *p = (int *)malloc(4 * sizeof(int));
	if(p == NULL)
	{
		printf("ø’º‰…Í«Î ß∞‹£°\n");
		exit(1);
	}
	for(i = 0; i < 4; ++i)
	{
		p[i] = i+1;
	}
	q = (int *)realloc(p , 6 * sizeof(int));
	if(q == NULL)
	{
		printf("ø’º‰◊∑º” ß∞‹!\n");
		exit(1);
	}

	printf("%d\n",q[3]);


	free(p);

	return 0;
}