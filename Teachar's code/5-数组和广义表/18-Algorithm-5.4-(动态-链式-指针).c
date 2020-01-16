#include <stdio.h>
#include <stdlib.h>


#define Status      int
#define OK          1
#define ERROR       0
#define OVERFLOW    -2

#define ElemType int

typedef struct OLNode{
	int i,j;					//该非零元的行和列下标
	ElemType e;
	struct OLNode *right,*down;	//该非零元所在行表和列表的后继链表
}OLNode,*OLink;

typedef struct{
	OLink *rhead,*chead;
	int mu,nu,tu;
}CrossList;

void MatrixFree(CrossList *M)
{
	if(M->rhead)
		free(M->rhead);
	if(M->chead)
		free(M->chead);
	M->chead = M->rhead = NULL;
}

// 算法5.4 
Status CreateSMatrix(CrossList *M)
{
	int m = 3,n = 4,t = 4,ii;
    OLNode Node[6];
	MatrixFree(M);
	(*M).mu = m;	(*M).nu = n;	(*M).tu = t;
	(*M).chead = (*M).rhead = NULL;

	if(!((*M).rhead = (OLink *)malloc((m+1)*sizeof(OLink))))
		exit(OVERFLOW);	//0号空间未用
	if(!((*M).chead = (OLink *)malloc((n+1)*sizeof(OLink))))
		exit(OVERFLOW);	//0号空间未用
	for(ii = 0; ii <= m;++ii)//初始化行列头指针向量；各行列链表为空链表
		(*M).rhead[ii] = NULL;
	for(ii = 0; ii <= n;++ii)//初始化行列头指针向量；各行列链表为空链表
		(*M).chead[ii] = NULL;
	
	Node[1].i = 1;	Node[1].j = 1;	Node[1].e = 3;
	Node[2].i = 1;	Node[2].j = 4;	Node[2].e = 5;
	Node[3].i = 2;	Node[3].j = 2;	Node[3].e = -1;
	Node[4].i = 3;	Node[4].j = 1;	Node[4].e = 2;
	Node[5].i = 0;	//用于终止下面的循环
	for (ii = 1; ii  <= 5; )
	{
		int i,j,e;
		//按照任意次序输入非零元
		for(i = Node[ii].i,j = Node[ii].j,e = Node[ii].e;++ii,
			i != 0;i = Node[ii].i,j = Node[ii].j,e = Node[ii].e)
		{
			OLNode *p = NULL,*q = NULL;
			if(!(p = (OLNode *)malloc(sizeof(OLNode))))	
				exit(OVERFLOW);
			p->i = i;	p->j = j;	p->e = e;			//生成结点
			if((*M).rhead[i] == NULL || (*M).rhead[i]->j > j)	
			//如果第i行头指针为空，	或者第i行所指向的第一个结点列号比要插入的列号大，
			//那么要插入的结点要放到第i行的第一个位置，类似头插法
			{
				p->right = (*M).rhead[i];
				(*M).rhead[i] = p;
			}else
			{	//寻查在行表中的插入位置
				//q->right指向的是q所指向结点的下一个结点，或者说q->right存放下一个结点的地址
				for(q = (*M).rhead[i];(q->right) && q->right->j < j;q = q->right);
				//以上for循环，循环体为空，是寻找前驱的过程
				p->right = q->right;
				q->right = p;
			}
			if((*M).chead[j] == NULL || (*M).chead[j]->i > i)
			{
				p->down = (*M).chead[j];
				(*M).chead[j] = p;
			}else
			{
				for(q = (*M).chead[j]; (q->down) && q->down->i < i; q = q->down);
				p->down = q->down;
				q->down = p;
			}
		}
	}//ii循环赋值

	return OK;
}

// 测试  算法5.4 
int main(void)
{
	CrossList M;
	M.chead = M.rhead = NULL;
	CreateSMatrix(&M);
	printf("第一行指向第一个结点非零元是：%d \n", M.rhead[1]->e);
	printf("第一行指向第二个结点非零元是：%d \n", M.chead[1]->right->e);
	printf("第一列指向第二个结点非零元是：%d \n", M.chead[1]->down->e);

	return 0;
}