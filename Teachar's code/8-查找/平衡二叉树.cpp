#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define Status int
#define OK	1
#define ERROR	0

#define Boolean int
#define FALSE	0
#define TRUE	1



//------------
#define  EQ(a, b)	((a)==(b))	//a,b为数值型
#define  LT(a, b)	((a)< (b))
#define  LQ(a, b)	((a)<=(b))

#define KeyType int
#define InfoType char

typedef struct
{
	KeyType key;	//数据元素中查找的关键字
	InfoType* info;	//数据元素中的其他信息
}ElemType;

typedef struct
{
	ElemType *elem;	//数据元素存储空间基址，建表时按实际长度分配，0号单元留空
	int length;		//表长度
}SSTable;
//------------

//二叉树的二叉链表存储表示
#define TElemType ElemType

typedef struct BSTNode
{
	TElemType data;
	int bf;								//结点的平衡因子
	struct BSTNode *lchild ,*rchild;	//左右孩子指针
}BSTNode,*BSTree;

#define LH	1
#define EH	0
#define RH	-1

/*
对树*T进行右旋操作：
    1.得到其左孩子lc
    2.让树*T的左孩子等于lc的右孩子
    3.让lc的右孩子等于树*T
    4.让树根为lc
*/
//右旋处理  画图写
void R_Rotate(BSTree *p)
	//对以*p为根的二叉排序树作右旋处理，处理之后p指向新的树根结点，即旋转
	//处理之前的左子树的根结点
{
    BSTree lc = (*p)->lchild;	//lc指向的*p的左子树根结点
    (*p)->lchild = lc->rchild;	//lc的右子树挂接为*p的左子树
    lc->rchild = (*p);			//p指向新的根结点
    (*p) = lc;
}

/*
对树*T进行左旋操作：
    1.得到其右孩子rc
    2.让树*T的右孩子等于rc的左孩子
    3.让lc的左孩子等于树*T
    4.让树根为rc
*/
//左旋处理
void L_Rotate(BSTree *T)
{
    BSTree rc = (*T)->rchild;
    (*T)->rchild = rc->lchild;
    rc->lchild = (*T);
    (*T) = rc;
}

//进行左平衡处理
void LeftBalance(BSTree *T)
{
    BSTree lc = NULL, rd = NULL;
    lc = (*T)->lchild;

    switch(lc->bf)
    {
    case LH:     //在左子树插入左孩子，进行右旋
        (*T)->bf = lc->bf = EH;
        R_Rotate(T);        break;
    case RH:    //在左子树插入右孩子，先左子树进行左旋，在树整体进行右旋
        rd = lc->rchild;
/*-----------------NO---------------------*/
        switch(rd->bf)
        {
        case LH:
            (*T)->bf = RH;
            lc->bf = EH;
            break;
        case EH:
            (*T)->bf = lc->bf = EH;
            break;
        case RH:
            (*T)->bf = EH;
            lc->bf = LH;
            break;
        }
        rd->bf = EH;
/*----------------------------------------*/
        L_Rotate(&((*T)->lchild));
        R_Rotate(T);
    }
}

//进行右平衡处理
void RightBalance(BSTree *T)
{
    BSTree rc = NULL, ld = NULL;

    rc = (*T)->rchild;

    switch(rc->bf)
    {
    case RH:     //在左子树插入左孩子，进行右旋
        (*T)->bf = rc->bf = EH;
        L_Rotate(T);
        break;
    case LH:    //在左子树插入右孩子，先左子树进行左旋，在树整体进行右旋
        ld = rc->lchild;
/*-----------------NO---------------------*/
        switch(ld->bf)
        {
        case RH:
            (*T)->bf = LH;
            rc->bf = EH;
            break;
        case EH:
            (*T)->bf = rc->bf = EH;
            break;
        case LH:
            (*T)->bf = EH;
            rc->bf = RH;
            break;
        }
        ld->bf = EH;
/*----------------------------------------*/
        R_Rotate(&((*T)->rchild));
        L_Rotate(T);
    }
}

//创建平衡二叉树,taller表示小树是否长高     false 没长高 true 长高
Status InsertAVL(BSTree * T, ElemType e, bool *taller)
{
    //树为空，直接插入
    if(!(*T))
    {
        /*
        创建叶子结点，taller为true，表示小树长高
        */
        (*T) = (BSTree)malloc(sizeof(BSTNode));
        (*T)->data = e;
        (*T)->lchild = (*T)->rchild = NULL;
        (*T)->bf = EH;
        *taller = TRUE;
    }
    else//不为空的情况
    {
        //元素已存在，拒绝插入
        if(EQ(e.key, (*T)->data.key))//等于根节点
        {
            taller = FALSE;
            return ERROR;
        }
		if(LT(e.key, (*T)->data.key))//小于根节点，在左子树中查找
        {
            //插入不成功
            if(!InsertAVL(&(*T)->lchild, e, taller))
                 return 0;
            //小树长高
            if(*taller)
            {
                switch ((*T)->bf)
                {
                case LH:				//注意是递归，原先左子树高，现在左子树又长高了，破坏了平衡性
                    LeftBalance(T);		//进行左平衡处理
                    *taller = FALSE;	//平衡处理之后，树的高度仍为插入节点之前,未长高
                    break;
                case EH:				//原先左右子树等高，现在左子树长高，但是任然满足平衡二叉树的定义
                    (*T)->bf = LH;      //左子树长高
                    *taller = TRUE;		//树整体长高
                    break;
                case RH:
                    (*T)->bf = EH;		//原先右子树高，左子树长高之后，左右子树一样高
                    *taller = FALSE;    //树整体和插入之前一样高，且树的平衡性未被破坏
                    break;
                }
            }
        }
        else					//大于根节点，在右子树中进行查找
        {
            //插入失败
            if(!InsertAVL(&(*T)->rchild, e, taller))
                return ERROR;
            //小树长高
            if(*taller)
            {
                switch((*T)->bf)
                {
                case LH:
                    (*T)->bf = EH;       //原先是左边的小树高，右边的小树长高之后，就一样高了
                    *taller = FALSE;      //整体来说，小树并未长高
                    break;
                case EH:
                    (*T)->bf = RH;       //原先是左右小树一样高，现在右边的小树长高之后，右边的小树高
                    *taller = TRUE;      //整体来说，树长高了，但是并未破坏整体的平衡性
                    break;
                case RH:     //原先是就是右边的小树高，右边的小树再长高之后，就破坏了整体树的平衡性
                    RightBalance(T);      //平衡处理
                    *taller = FALSE;      //处理之后树并未长高
                    break;
                }
            }
        }
    }

    return OK;
}

//中序遍历
void Traverse(BSTree T)
{
    if(T)
    {
        Traverse(T->lchild);
        printf("%d ", T->data.key);
        Traverse(T->rchild);
    }
}

//先序遍历
void PreTraverse(BSTree T)
{
    if(T)
    {
        printf("%d ", T->data.key);
        PreTraverse(T->lchild);
        PreTraverse(T->rchild);
    }
}

int arr[10] = {1, 6, 9, 5, 6, 4, 2, 8, 7, 5};

int main(void)
{
    int i;
    bool taller;
    ElemType e;
    BSTree T = NULL;

    for(i = 0; i < 10; ++i)
    {
        e.key = arr[i];
        InsertAVL(&T, e, &taller);
    }
    printf("中序：\n");
    Traverse(T);
    printf("\n先序：\n");
    PreTraverse(T);
		printf("\n");

    return 0;
}

/*
中序：
1 2 4 5 6 7 8 9
先序：
4 1 2 6 5 8 7 9
*/
