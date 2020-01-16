#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//------------
#define  EQ(a, b)	((a)==(b))	//a,b为数值型
#define  LT(a, b)	((a)< (b))
#define  LQ(a, b)	((a)<=(b))

#define KeyType int
#define InfoType char

typedef struct{
    KeyType key;	//数据元素中查找的关键字
    InfoType* info;	//数据元素中的其他信息
}ElemType;

typedef struct{
    ElemType *elem;	//数据元素存储空间基址，建表时按实际长度分配，0号单元留空
    int length;		//表长度
}SSTable;
//------------

//二叉树的二叉链表存储表示
#define TElemType ElemType

typedef struct BiTNode{
    TElemType data;
    int pos;
    struct BiTNode *lchild ,*rchild;	//左右孩子指针
}BiTNode,*BiTree;

int Visit(TElemType e){
    if(!e.key)
        return 0;
    printf("%d ",e.key);
    return 1;
}

int InOrderTraverse(BiTree T,int (*Visit)(TElemType e))
{    //采用二叉链表存储结构，Visit是对数据元素操作的应用函数，
     //中序遍历二叉树T的递归算法，对每个数据元素调用函数Visit。
    if(T){
        if(InOrderTraverse(T->lchild,Visit))
            if(Visit(T->data))
                if(InOrderTraverse(T->rchild,Visit))
                    return 1;
        return 0;
    }else{
        return 1;
    }
}

int PreOrderTraverse(BiTree T,int (*Visit)(TElemType e))
{    //采用二叉链表存储结构，Visit是对数据元素操作的应用函数，
    //先序遍历二叉树T的递归算法，对每个数据元素调用函数Visit。
    if(T){
        if(Visit(T->data))
            if(PreOrderTraverse(T->lchild,Visit))
                if(PreOrderTraverse(T->rchild,Visit))
                    return 1;
        return 0;
    }else{
        return 1;
    }
}



// 算法 9.5(a)
BiTree SearchBSTa(BiTree T,KeyType key)
{    //在根指针T所指二叉排序树中递归地查找某关键字等于key的数据元素，
     //若查找成功，则返回指向该数据结点的指针，否则返回空指针
    if((!T) || EQ(key,T->data.key))
        return T;							//查找结束
    else if(LT(key, T->data.key))
        return (SearchBSTa(T->lchild,key));	//在左子树中继续查找
    else
        return (SearchBSTa(T->rchild,key));	//在右子树中继续查找
}




// 算法9.5(b)
int SearchBSTb(BiTree T,KeyType key,BiTree f,BiTree &p)
{   //在根指针T所指二叉排序树中递归地查找某关键字等于key的数据元素，
    //若查找成功，指针p指向该数据元素的结点，并返回1，否则p指向查找路径
    //上访问的最后一个结点并返回0，指针f指向T的双亲，且初始调用值是NULL
    if(!T){						//查找不成功
        p = f;
        return 0;
    }else if(EQ(key,T->data.key)){//查找成功
        p = T;
        return 1;
    }else if(LT(key,T->data.key)){//在左子树继续查找
        return SearchBSTb(T->lchild,key,T,p);
    }else{//在右子树继续查找
        return SearchBSTb(T->rchild,key,T,p);
    }
}

void PrintSearchBST(BiTree T1)
{
    if(T1)
        printf("查到的结果：%d。\n", T1->data.key);
    else
        printf("未查到结果。\n");
}

// 算法 9.6 
int InsertBST(BiTree &T, ElemType e)
{    //当二叉排序树T中不存在关键字等于e.key的数据元素时，插入e并返回1，
     //否则返回0.
    BiTree p, s;	
    if(!SearchBSTb(T,e.key,NULL,p)){
        s = (BiTree)malloc(sizeof(BiTNode));
        s->data.key = e.key;
        s->lchild = s->rchild = NULL;
        if(!p)
            T = s;						//被插节点*s为新的根节点
        else if(LT(e.key,p->data.key))	//判断插入的结点key值和插入位置双亲结点大小，判断插入左边还是右边
            p->lchild = s;				//被插节点*s为新的左孩子节点
        else
            p->rchild = s;				//被插节点*s为新的右孩子节点
        return 1;
    }
    return 0;	//树中已存在关键字相同的结点，不必插入
}

// 算法 9.8  
//目标是找要删除结点的前驱，用前驱代替要删除的结点，调整次序，使中序遍历次序不受到影响
int Delete(BiTree &p)
{    //从二叉排序树中删除结点p，并重接它的左或右子树
    BiTree q, s;
    if(!p->rchild){		//右子树空则只需重接它的左子树 包含叶子结点删除情况
        q = p;
        p = p->lchild;
        free(q);
    }else if(!p->lchild){//只需重接它的右子树
        q = p;
        p = p->rchild;
        free(q);
    }else{				//左右子树均不空
        q = p;
        s = p->lchild;
        while (s->rchild){
            q = s;
            s = s->rchild;	//s指向左子树，然后向右走到尽头，也就是被删除结点的“前驱”
        }
        p->data = s->data;	//将前驱结点的数据复制给要删除的结点
        if(q != p)
            q->rchild = s->lchild;	//前驱代替要删除的结点
        else
            q->lchild = s->lchild;	//左子树代替要删除的结点
        free(s);
    }
    return 1;
}

// 算法 9.7  
int DeleteBST(BiTree &T, KeyType key)
{    //若二叉排序树T中存在关键字等于key的数据元素时，则删除该数据元素的结点，
     //并返回1,否则返回0.
    if(!T)
        return 0;
    else{
        if(EQ(key, T->data.key))
            return Delete(T);
        else if(LT(key,T->data.key))
            return DeleteBST(T->lchild, key);
        else
            return DeleteBST(T->rchild, key);
    }
}
KeyType arr[] = {45,2,90,37,24,40,53,50};

int main(void)
{
    BiTree T = NULL;
    ElemType e;	e.key = 40;
    int count = 0,depth,flag = 0, i;

    for (i = 0; i < 8; i++){
        e.key = arr[i];
        InsertBST(T, e);
    }

    printf("先序遍历:");
    PreOrderTraverse(T,Visit);
    printf("\n中序遍历:");
    InOrderTraverse(T,Visit);
    printf("\n");

    printf("---------------------\n");
    DeleteBST(T,37);
    printf("先序遍历:");
    PreOrderTraverse(T,Visit);
    printf("\n中序遍历:");
    InOrderTraverse(T,Visit);
    printf("\n");

    return 0;
}
/*
先序遍历:45 2 37 24 40 90 53 50
中序遍历:2 24 37 40 45 50 53 90
---------------------
先序遍历:45 2 24 40 90 53 50
中序遍历:2 24 40 45 50 53 90
请按任意键继续. . .
*/