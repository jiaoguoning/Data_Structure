#include <stdio.h>
#include <stdlib.h>
#define CHUNKSIZE 80	//���û�����Ŀ��С
//���Ŀ����洢��ʾ
typedef struct Chunk{
	char ch[CHUNKSIZE];
	struct Chunk *next;
}Chunk;

typedef struct{
	Chunk *head,*Tail;
	int curlen;
}LString;

int main(void)
{
	
	




	return 0;
}