#include <stdio.h>
#include <stdlib.h>
#define TElemType char

typedef enum PointerTag
{
	Link, Thread
};	//Link == 0：指针， Thread == 1：线索

typedef struct BiThrNode
{
	TElemType data;
	struct BiThrNode *lchild, *rchild;	//左右孩子指针
	PointerTag LTag,RTag;				//左右标志
}BiThrNode,*BiThrTree;

char arr3[] = {'-','+','a','\0','\0','*','b','\0','\0','-','c','\0','\0','d','\0','\0','/','e','\0','\0','f','\0','\0'};
int arr_i = 0;

//按照先序遍历创建二叉树
int CreateBiTree(BiThrTree &T)
{
	char ch;
	ch = arr3[arr_i++];
	if(ch == '\0')
	{
		T = NULL;
	}
	else
	{
		if(!(T = (BiThrNode *)malloc(sizeof(BiThrNode))))
			exit(-1);
		T->data = ch;			//生成根节点
		T->LTag = Link;			//生成时给线索标志域赋初值
		T->RTag = Link;			//默认都是Link
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

int InOrderTraverse_Thr(BiThrTree T,int (* Visit)(TElemType e))
	//T指向头结点，头结点的左链lchild指向根节点，可参见线索化算法。
	//中序遍历二叉线索树T的非递归算法，对每个数据元素调用函数Visit。
{
	BiThrTree p;
	p = T->lchild;	//p指向根节点
	while (p != T)	//空树或遍历结束时，p == T
	{
		while (p->LTag == Link)
			p = p->lchild;	
		if(!Visit(p->data))	//访问左子树为空的结点
			return 0;
		while (p->RTag == Thread && p->rchild != T)
		{
			p = p->rchild;
			Visit(p->data);	//访问后继结点  这里为啥不判定失败？
		}
		p = p->rchild;
	}
	return 1;
}//InOrderTraverse_Thr


//此处也可以把pre设置为全局变量，那就将InOrderThreading函数中的pre定义去掉
void InThreading(BiThrTree p,BiThrTree &pre)
{
	if(p)
	{
		InThreading(p->lchild,pre);	//左子树线索化
		if(!p->lchild)			//若p指向结点没有左孩子，线索化前驱
		{
			p->LTag = Thread;
			p->lchild = pre;	//前驱线索化
		}
		if(!pre->rchild)		//若p指向结点没有右孩子，线索化后继
		{
			pre->RTag = Thread;
			pre->rchild = p;	//后继线索化
		}
		pre = p;				//保持pre指向p的前驱
		InThreading(p->rchild,pre);	//右子树线索化
	}
}

int InOrderThreading(BiThrTree &Thrt,BiThrTree T)
	//中序遍历二叉树T，并将其中序线索化，Thrt指向头结点。
{
	BiThrTree pre = NULL;
	if(!(Thrt = (BiThrNode *)malloc(sizeof(BiThrNode))))
		exit(-1);
	Thrt->LTag = Link;	Thrt->RTag = Thread;	//建头结点
	Thrt->data = '#';
	Thrt->rchild = Thrt;						//右指针回指
	if(!T)
	{
		Thrt->lchild = Thrt;					//若二叉树为空，则左指针回指(就是指向自己)
	}else
	{
		Thrt->lchild = T;
		pre = Thrt;
		InThreading(T,pre);						//中序遍历进行中序线索化
		pre->rchild = Thrt;	pre->RTag = Thread;	//最后一个结点线索化
		Thrt->rchild = pre;
	}
	return 1;
}

int main(void)
{
	BiThrTree T,Thrt;
	CreateBiTree(T);
	InOrderThreading(Thrt,T);
	InOrderTraverse_Thr(Thrt,Visit);


	return 0;
}
