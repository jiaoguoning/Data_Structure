#include <stdio.h>

void Visit1(int brr[5],int length)
{
	printf("brr = %p\n",brr);
	printf("&brr = %p\n",&brr);
	printf("sizeof(brr) = %d\n",sizeof(brr));
}

int main(void)
{
	int arr[5]= {1,2,3};
	int *parr = arr;
	printf("arr[2] = %d\n",arr[2]);
	printf("*(arr+2) = %d\n",*(arr+2));
	printf("parr[2] = %d\n",parr[2]);
	printf("*(parr+2) = %d\n",*(parr+2));
	//Çø±ð
	//++parr;
	//++arr;

	printf("&parr = %p\n",&parr);
	printf("&arr = %p\n",&arr);
	printf("parr = %p\n",parr);

	printf("sizeof(parr) = %d\n",sizeof(parr));
	printf("sizeof(arr) = %d\n",sizeof(arr));
	
	//Visit1(arr,5);

	return 0;
}








