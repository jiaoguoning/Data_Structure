#include <stdio.h>
#include <stdlib.h>
#define CHUNKSIZE 80	//可用户定义的块大小
//串的块链存储表示
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