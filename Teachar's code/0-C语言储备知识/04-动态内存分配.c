#include <stdio.h>
#include <stdlib.h>

//-------------    ��̬����     -------------//
int main(void)
{
	int i;
	int *q;
	int *p = (int *)malloc(4 * sizeof(int));
	if(p == NULL)
	{
		printf("�ռ�����ʧ�ܣ�\n");
		exit(1);
	}
	for(i = 0; i < 4; ++i)
	{
		p[i] = i+1;
	}
	q = (int *)realloc(p , 6 * sizeof(int));
	if(q == NULL)
	{
		printf("�ռ�׷��ʧ��!\n");
		exit(1);
	}

	printf("%d\n",q[3]);


	free(p);

	return 0;
}