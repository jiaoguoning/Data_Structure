#include<stdio.h>
#include<stdlib.h>

#define Status int 
#define ELemType char
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
#define OK 1
#define ERROR 0

typedef struct {
	ElemType* elem;
	int length;
	int listsize;
}SqList;

Status InitLIst(SqList *L){
	printf("InitLIst_start!\n");
	L->elem = (ELemType *)malloc(sizeof(ElemType)*LIST_INIT_SIZE);
	if(!(L->elem))	return ERROR;
	L->length = 0;
	L->listsize = LIST_INIT_SIZE;
	printf("InitLIst_end!\n");
	return OK;
} 

Status DestroyList(SqList *L){
	printf("DestroyList_start!\n");
	free(L->elem);
	L->length = 0;
	L->listsize = 0;
	printf("DestroyList_end!\n");
	return OK;
}

Status ClearList(SqList *L){
	int i;
	printf("ClearList_start\n");
	for(i=0;i<L->length;i++)
		L->elem[i]=0;
	L->length = 0;
	printf("ClearList_end\n");
	return OK;
}

Status ListEmpty(SqList *L){
	return L->length==0?OK:ERROR;
}

Status ListLength(SqList *L){
	return L->length;
}

Status GetElem(SqList L,int pos,ElemType *e){
	int i;
	if(pos>L.length || pos <=0)	return ERROR;
	*e = L.elem[pos-1];
	return OK;
}


