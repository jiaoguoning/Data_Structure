#include <stdio.h>
#define MAXSIZE 10
#define ElemType char
#define Status  int
#define ERROR 0
#define OK  1

typedef struct
{
	ElemType data;
	int cur;
}component, SLinkList[MAXSIZE];

//1. 申请一个可容纳MAXSIZE个结点的静态链表
//2. 每个结点包括一个数据域和一个游标域
//3. 为了合理管理静态链表数据元素，设置一个备用链表，备用
//   链表头结点为L[0],链表头结点为L[MAXSIZE-1]，游标cur=0为空
//4. 初始化时，置链表头结点为空，其余元素组成备用链表，
//   备用链表最后一个元素置为空。

//思路：本质上静态链表是将SLinkList数组分成两个链表：正用链表和备用链表
//正用链表的头结点是申请空间的最后一个结点(length-1号下标)
//备用链表头结点是申请空间的第一个结点(0号下标)



int LocateElem_SL(SLinkList &SL, ElemType e)
	//在静态单链线性表查找第1个值为e的元素。
	//若找到，则返回它在L中的位序，否则返回0.

{
	int i = SL[MAXSIZE-1].cur;			//存放着正用链表第一个结点的下标
	while (i && SL[i].data != e)	//
		i = SL[i].cur;
	return i;
}


void InitSpace_SL(SLinkList &SL)
	//将SL中各分量链成一个备用链表，SL[0].cur为备用链表头指针，
	//SL[MAXSIZE-1].cur表示正用链表的头指针
	//SL[MAXSIZE-2].cur表示备用链表的链表尾;
{
	int i;
	SL[MAXSIZE-1].cur = 0;				//正用链表头结点为空
	for(i = 0; i < MAXSIZE - 2; ++i)	//其余链表构成备用链表
		SL[i].cur = i + 1;
	SL[MAXSIZE-2].cur = 0;				//备用链表最后一个元素置空
}

int Malloc_SL(SLinkList &SL)
	//若备用空间链表非空，则返回分配的结点下标，否则返回0
{
	int i = SL[0].cur;
	if(i)						//如果i不为0，说明还有空间
		SL[0].cur = SL[i].cur;
	return i;
}

void Free_SL(SLinkList &SL, int k)
	//将下标为k的空闲结点回收到备用链表
{
	SL[k].cur = SL[0].cur;
	SL[0].cur = k;
}

Status ListInsert_SL(SLinkList &SL,int i,ElemType e)
{
	int s;
	int p = MAXSIZE - 1 ;
	int j = 0;
	while (p && j < i-1)
	{
		p = SL[p].cur;
		++j;
	}
	if(!p || j > i - 1)
		return ERROR;

	s = Malloc_SL(SL);
	if(!s)
	{
		printf("空间已经用完！\n");
		return ERROR;
	}
	SL[s].data = e;
	SL[s].cur = SL[p].cur;
	SL[p].cur = s;
	return OK;
}

int ListLength_SL(SLinkList &L) 
{ 
	int j = 0;
	int i = L[MAXSIZE - 1].cur; 
	while(i != 0) 
	{ 
		i = L[i].cur;
		++j; 
	} 
	return j; 
}

Status ListDelete_SL(SLinkList &SL, int i,ElemType &e)  
{     
	int q = 0;
	int p = MAXSIZE - 1;
	int j = 0;
	while (SL[p].cur && j < i - 1)
	{
		p = SL[p].cur;
		++j;
	}
	if(!SL[p].cur || j > i - 1)
		return ERROR;
	q = SL[p].cur;
	SL[p].cur = SL[q].cur;
	e = SL[q].data;
	Free_SL(SL, q);
	return OK;  
}

void ListPrint_SL(SLinkList SL)
{
	int p = SL[MAXSIZE-1].cur;
	while (p)
	{
		printf("%c  ", SL[p].data);
		p = SL[p].cur;
	}
	printf("\n");
}



int main(void)
{
	SLinkList SL;
	int i;
	char e;
	InitSpace_SL(SL);
	for (i = 0; i < 12; i++)
	{
		ListInsert_SL(SL, 1, 'A' + i);
		e = ListLength_SL(SL);
	}
	printf("长度为： %d\n",e);
	ListPrint_SL(SL);
	
	for (i = 0; i < 2; i++)
	{
		ListDelete_SL(SL, i+1, e);
		printf("删除第%d个后为： \n", i+1);
		ListPrint_SL(SL);
	}
	printf("与A相同的存放在SL数组下标是：%d \n",LocateElem_SL(SL , 'A'));

	return 0;
}

