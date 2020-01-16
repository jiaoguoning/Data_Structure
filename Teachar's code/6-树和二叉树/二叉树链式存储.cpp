#include <stdio.h>
#include <stdlib.h>
#define TElemType char

//二叉树的二叉链表存储表示
typedef struct BiTNode
{
	TElemType data;
	struct BiTNode *lchild ,*rchild;	//左右孩子指针
}BiTNode,*BiTree;

/*------------------栈的实现-----------------*/
#define STACK_INIT_SIZE 20
#define STACKINCREMENT 5
#define ElemType BiTree
typedef struct {
	ElemType *base;
	ElemType *top;
	int stacksize;
}SqStack;

//因为要修改栈S内存中数据成员的值，因此必须传递S的地址
int InitStack(SqStack *S)
{
	S->base = (ElemType*)malloc(sizeof(ElemType) * STACK_INIT_SIZE);
	if (!S->base)
	{
		printf("初始化失败！\n");
		return 0;
	}
	S->top = S->base;
	S->stacksize = STACK_INIT_SIZE;
	return 1;
}

int push(SqStack *S,ElemType e)
{
	if ((S->top - S->base) >= S->stacksize)
	{
		S->base = (ElemType *)realloc(S->base,S->stacksize+STACKINCREMENT);
		if (!S->base)
		{
			printf("追加失败!\n");
			return 0;
		}
		S->top = S->base + S->stacksize;
		S->stacksize += STACKINCREMENT;
	}
	*S->top++ = e;
	return 1;
}

int pop(SqStack *S,ElemType *e)
{
	if (S->top == S->base)
	{
		printf("出栈失败，栈为空!\n");
		return 0;
	}
	*e = *--S->top;
	return 1;
}

int GetTop(SqStack S,ElemType *e)
{
	if(S.base == S.top)
		return 0;
	*e = *(S.top - 1);
	return 1;
}

void PrintStack(SqStack S)
{
	//ElemType *p = S.base;
	//while(p < S.top)
	//{
	//	if((*(p)))
	//		printf("%c ",(*(p))->data);
	//	else
	//		printf("0 ");
	//	++p;
	//}
	//printf("\n");
}
/*-----------------------------------------*/


//创建二叉树的原始数据
char arr1[] = {'A','B','D','\0','\0','E','G','\0','\0','\0','C','\0','F','\0','\0'};
char arr2[] = {'A','B','E','\0','L','\0','\0','\0','D','H','M','\0','\0','I','\0','\0','J','\0','\0'};
char arr3[] = {'-','+','a','\0','\0','*','b','\0','\0','-','c','\0','\0','d','\0','\0','/','e','\0','\0','f','\0','\0'};

int arr_i = 0;



//按照先序遍历创建二叉树
int CreateBiTree(BiTree &T)
{
	char ch;
	ch = arr3[arr_i++];
	if(ch == '\0')
	{
		T = NULL;
	}
	else
	{
		if(!(T = (BiTNode *)malloc(sizeof(BiTNode))))
			exit(-1);
		T->data = ch;			//生成根节点
		CreateBiTree(T->lchild);//构造左子树
		CreateBiTree(T->rchild);//构造右子树
	}
	return 1;
}

int Visit(TElemType e)
{
	if(!e)
		return 0;
	printf("%c ",e);
	return 1;
}

int PreOrderTraverse(BiTree T,int (*Visit)(TElemType e))
	//采用二叉链表存储结构，Visit是对数据元素操作的应用函数，
	//先序遍历二叉树T的递归算法，对每个数据元素调用函数Visit。
{
	if(T)
	{
		if(Visit(T->data))
			if(PreOrderTraverse(T->lchild,Visit))
				if(PreOrderTraverse(T->rchild,Visit))
					return 1;
		return 0;
	}else
	{
		return 1;
	}
}

int InOrderTraverse(BiTree T,int (*Visit)(TElemType e))
	//采用二叉链表存储结构，Visit是对数据元素操作的应用函数，
	//中序遍历二叉树T的递归算法，对每个数据元素调用函数Visit。
{
	if(T)
	{
		if(InOrderTraverse(T->lchild,Visit))
			if(Visit(T->data))
				if(InOrderTraverse(T->rchild,Visit))
					return 1;
		return 0;
	}else
	{
		return 1;
	}
}

int PostOrderTraverse(BiTree T,int (*Visit)(TElemType e))
	//采用二叉链表存储结构，Visit是对数据元素操作的应用函数，
	//后序遍历二叉树T的递归算法，对每个数据元素调用函数Visit。
{
	if(T)
	{
		if(PostOrderTraverse(T->lchild,Visit))
			if(PostOrderTraverse(T->rchild,Visit))
				if(Visit(T->data))
					return 1;
		return 0;
	}else
	{
		return 1;
	}
}

int InOrderTraverse1(BiTree T,int (*Visit)(TElemType e))
	//采用二叉链表存储结构，Visit是对数据元素操作的应用函数，
	//中序遍历二叉树T的非递归算法，对每个数据元素调用函数Visit。
{
	SqStack S;
	//char test;
	InitStack(&S);
	push(&S,T);	//根指针进栈
	PrintStack(S);
	//test = T->data;
	while (S.base != S.top)	
	{
		BiTree p;
		while (GetTop(S,&p) && p)
			//右子树不是空且左子树不为空，向左走到尽头依次入栈
		{
			//if(p->lchild)
			//	test = p->lchild->data;
			//else
			//	test = 0;
			push(&S,p->lchild);	
			PrintStack(S);
		}
		pop(&S,&p);				//空指针退栈，对于左子树为空或者右子树为空情况
		PrintStack(S);
		if(S.base != S.top)
		{
			pop(&S,&p);			//访问结点，每pop一次，p向上移动，可能一层可能几层
			PrintStack(S);
			if(!Visit(p->data))
				return 0;
			//if(p->rchild)
			//	test = p->rchild->data;
			//else
			//	test = 0;
			push(&S,p->rchild);	//向右下方移动一步
			PrintStack(S);
		}
	}
	return 1;
}

int InOrderTraverse2(BiTree T,int (*Visit)(TElemType e))
	//采用二叉链表存储结构，Visit是对数据元素操作的应用函数，
	//中序遍历二叉树T的非递归算法，对每个数据元素调用函数Visit。
	//比上面方法简洁在：p是空的时候，不用把空也入栈再出栈
{
	SqStack S;
	char test;
	BiTree p;
	InitStack(&S);
	p = T;
	while(p || S.base != S.top)
	{
		if(p)	//只要p指针不为空，就进栈，遍历左子树
		{
			push(&S,p);
			PrintStack(S);
			p = p->lchild;
		}else   //遇到p为空的情况出栈
		{
			pop(&S,&p);
			PrintStack(S);
			if(!Visit(p->data))
				return 1;
			p = p->rchild;
		}
	}
	return 1;
}
//***********给出了采用递归，对二叉树树进行操作的一般方法**********//
void CountLeaf(BiTree T, int &count)
	//先序遍历二叉树，以count返回二叉树中叶子结点的数目
	//conut作为计数器，在传参时count在main中要清零
{
	if(T)
	{
		if((!T->lchild) && (!T->rchild))	//既没有左子树也没有右子树
			++count;						//对叶子结点计数
		CountLeaf(T->lchild,count);
		CountLeaf(T->rchild,count);
	}
}// CountLeaf

int BiTreeDepth(BiTree T)
{
	int depth  , depthleft ,depthright ;
	if(!T)
	{
		depth = 0;
	}
	else
	{
		depthleft  = BiTreeDepth(T->lchild);
		depthright = BiTreeDepth(T->rchild);
		depth = (depthleft > depthright ? depthleft : depthright) + 1;
	}
	return depth;
}




int main(void)
{
	BiTree T;
	int count = 0,depth;
	CreateBiTree(T);
	CountLeaf(T, count);
	printf("%d\n",count);
	printf("%d\n",BiTreeDepth(T));

	


	return 0;
}



