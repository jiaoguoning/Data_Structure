#include <stdio.h>
#include <stdlib.h>

#define Status          int //状态
#define OVERFLOW        -1  //溢出
#define OK              1   //正确
#define ERROR           0   //错误


//----- 线性表的动态分配顺序存储结构 -----
#define LIST_INIT_SIZE  100 //线性表存储空间的初始分配量
#define LISTINCREMENT   10  //线性表存储空间的分配增量

#define ElemType int        //ElemType设置为int类型
typedef struct
{
	ElemType * elem;    //存储空间基址
	int length;         //当前长度
	int listsize;       //当前分配的存储容量大小：listsize * sizeof(ElemType)字节
}SqList;

//算法2.3.0
Status InitList_Sq(SqList &L){
    // 构造一个空的线性表
	L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if(!L.elem)
		exit(OVERFLOW);         //存储分配失败
	L.length = 0;               //空表长度为0
	L.listsize = LIST_INIT_SIZE;//初始存储容量
	return OK;
}//InitList_Sq

//算法2.3.1
Status InitList_Sq1(SqList *L){
    // 构造一个空的线性表
	(*L).elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if(!(*L).elem)
		exit(OVERFLOW);             //存储分配失败
	(*L).length = 0;                //空表长度为0
	(*L).listsize = LIST_INIT_SIZE; //初始存储容量
	return OK;
}//InitList_Sq


//算法2.3.2
Status InitList_Sq2(SqList *L){
    // 构造一个空的线性表
	L->elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if(!(*L).elem)
		exit(OVERFLOW);         //存储分配失败
	L->length = 0;               //空表长度为0
	L->listsize = LIST_INIT_SIZE;//初始存储容量
	return OK;
}//InitList_Sq


// 测试InitList
int main(void)
{
	SqList La;
    InitList_Sq(La);
    printf("La.elem     = %p\n",La.elem);
    printf("La.length   = %d\n",La.length);
    printf("La.listsize = %d\n",La.listsize);
	
    

	return 0;
}



