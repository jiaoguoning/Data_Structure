#include <stdio.h>
#include <stdlib.h>

#define Status      int
#define OK          1
#define ERROR       0
#define OVERFLOW    -2
#define TElemType   char

// 二叉树的二叉链表存储表示
typedef struct BiTNode
{
    TElemType data;
    struct BiTNode *lchild ,*rchild;	//左右孩子指针
}BiTNode,*BiTree;

/* ------------------栈的实现----------------- */
#define STACK_INIT_SIZE 20
#define STACKINCREMENT  5
#define ElemType        BiTree

//因为要修改栈S内存中数据成员的值，因此必须传递S的地址
typedef struct {
    ElemType *base;     // 在构造之前和销毁之后，base的值为NULL
    ElemType *top;      // 栈顶指针
    int stacksize;      // 当前已分配存储空间，以元素为单位
}SqStack;

//因为要修改栈S内存中数据成员的值，因此必须传递S的地址
Status InitStack(SqStack &S)
{
    S.base = (ElemType*)malloc(sizeof(ElemType) * STACK_INIT_SIZE);
    if (!S.base)
    {
        printf("初始化失败！\n");
        exit(OVERFLOW);     // return ERROR;
    }
    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
    return OK;
}

Status GetTop(SqStack S,ElemType &e){
    //若栈不空，则用e返回S的栈顶元素，并返回OK；否则返回ERROR
    if(S.base == S.top)
        return ERROR;
    e = *(S.top - 1);
    return OK;
}

Status Push(SqStack &S,ElemType e){
    //插入元素e为新的栈顶元素 
    if ((S.top - S.base) >= S.stacksize)    // 栈满
    {
        S.base = (ElemType *)realloc(S.base,S.stacksize+STACKINCREMENT);
        if (!S.base)
        {
            printf("追加失败!\n");
            exit(OVERFLOW);     // return ERROR;
        }
        S.top = S.base + S.stacksize;
        S.stacksize += STACKINCREMENT;
    }
    *S.top++ = e;
    return OK;
}

Status Pop(SqStack &S,ElemType &e)
{
    if (S.top == S.base)
    {
        printf("出栈失败，栈为空!\n");
        return ERROR;
    }
    e = *--S.top;
    return OK;
}
/*-----------------------------------------*/


//创建二叉树的原始数据
char arr1[] = {'A','B','D','\0','\0','E','G','\0','\0','\0','C','\0','F','\0','\0'};
char arr2[] = {'A','B','E','\0','L','\0','\0','\0','D','H','M','\0','\0','I','\0','\0','J','\0','\0'};
char arr3[] = {'-','+','a','\0','\0','*','b','\0','\0','-','c','\0','\0','d','\0','\0','/','e','\0','\0','f','\0','\0'};

int arr_i = 0;

// 算法6.4 二叉树创建 - 按照先序遍历创建二叉树
Status CreateBiTree(BiTree &T)
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
            exit(OVERFLOW);
        T->data = ch;			//生成根节点
        CreateBiTree(T->lchild);//构造左子树
        CreateBiTree(T->rchild);//构造右子树
    }
    return OK;
}

Status Visit(TElemType e)
{
    if(!e)
        return ERROR;
    printf("%c ",e);
    return OK;
}


// 算法 6.1  先序遍历-递归 
Status PreOrderTraverse(BiTree T,int (*Visit)(TElemType e))
{	//采用二叉链表存储结构，Visit是对数据元素操作的应用函数，
    //先序遍历二叉树T的递归算法，对每个数据元素调用函数Visit。
    if(T){
        if(Visit(T->data))
            if(PreOrderTraverse(T->lchild,Visit))
                if(PreOrderTraverse(T->rchild,Visit))
                    return OK;
        return ERROR;
    }else{
        return OK;
    }
}

// 算法6.2.1 中序遍历-递归 
Status InOrderTraverse(BiTree T,int (*Visit)(TElemType e))
    //采用二叉链表存储结构，Visit是对数据元素操作的应用函数，
    //中序遍历二叉树T的递归算法，对每个数据元素调用函数Visit。
{
    if(T){
        if(InOrderTraverse(T->lchild,Visit))
            if(Visit(T->data))
                if(InOrderTraverse(T->rchild,Visit))
                    return OK;
        return ERROR;
    }else
    {
        return OK;
    }
}


// 后序遍历-递归  
Status PostOrderTraverse(BiTree T,int (*Visit)(TElemType e))
    //采用二叉链表存储结构，Visit是对数据元素操作的应用函数，
    //后序遍历二叉树T的递归算法，对每个数据元素调用函数Visit。
{
    if(T){
        if(PostOrderTraverse(T->lchild,Visit))
            if(PostOrderTraverse(T->rchild,Visit))
                if(Visit(T->data))
                    return OK;
        return ERROR;
    }else
    {
        return ERROR;
    }
}


// 算法6.2 中序遍历-非递归
Status InOrderTraverse1(BiTree T,int (*Visit)(TElemType e))
{   //采用二叉链表存储结构，Visit是对数据元素操作的应用函数，
    //中序遍历二叉树T的非递归算法，对每个数据元素调用函数Visit。
    SqStack S;
    InitStack(S);
    Push(S,T);	//根指针进栈

    while (S.base != S.top)	
    {
        BiTree p;
        while (GetTop(S, p) && p){
                //右子树不是空且左子树不为空，向左走到尽头依次入栈
            Push(S, p->lchild);	
        }
        Pop(S, p);				//空指针退栈，对于左子树为空或者右子树为空情况
        if(S.base != S.top){
            Pop(S, p);			//访问结点，每pop一次，p向上移动，可能一层可能几层
            if(!Visit(p->data))
                return ERROR;
            Push(S, p->rchild);	//向右下方移动一步
        }
    }
    return OK;
}

// 算法6.3 中序遍历-非递归
Status InOrderTraverse2(BiTree T,int (*Visit)(TElemType e))
{   //采用二叉链表存储结构，Visit是对数据元素操作的应用函数，
    //中序遍历二叉树T的非递归算法，对每个数据元素调用函数Visit。
    //比上面方法简洁在：p是空的时候，不用把空也入栈再出栈
    SqStack S;
    BiTree p;
    InitStack(S);
    p = T;
    while(p || S.base != S.top)
    {
        if(p){	//只要p指针不为空，就进栈，遍历左子树
            Push(S, p);
            p = p->lchild;
        }else{  //遇到p为空的情况出栈
            Pop(S, p);
            if(!Visit(p->data))
                return ERROR;
            p = p->rchild;
        }
    }
    return OK;
}
//***********给出了采用递归，对二叉树树进行操作的一般方法**********//
// 求叶子结点个数  
void CountLeaf(BiTree T, int &count)
    //先序遍历二叉树，以count返回二叉树中叶子结点的数目
    //conut作为计数器，在传参时count在main中要清零
{
    if(T){
        if((!T->lchild) && (!T->rchild))	//既没有左子树也没有右子树
            ++count;						//对叶子结点计数
        CountLeaf(T->lchild,count);
        CountLeaf(T->rchild,count);
    }
}// CountLeaf


int count;
void CountLeaf1(BiTree T)  //先序
    //先序遍历二叉树，以count返回二叉树中叶子结点的数目
    //conut作为计数器，在传参时count在main中要清零
{
    if(T){
        if((!T->lchild) && (!T->rchild))	//既没有左子树也没有右子树
            ++count;						//对叶子结点计数
        CountLeaf1(T->lchild );
        CountLeaf1(T->rchild );
    }
}// CountLeaf


void CountLeaf2(BiTree T)  //先序
    //先序遍历二叉树，以count返回二叉树中叶子结点的数目
    //conut作为计数器，在传参时count在main中要清零
{
    if(T){
        CountLeaf2(T->lchild );
        if((!T->lchild) && (!T->rchild))	//既没有左子树也没有右子树
            ++count;						//对叶子结点计数
        CountLeaf2(T->rchild );
    }
}// CountLeaf

void CountLeaf3(BiTree T)  //先序
    //先序遍历二叉树，以count返回二叉树中叶子结点的数目
    //conut作为计数器，在传参时count在main中要清零
{
    if(T){
        CountLeaf3(T->lchild );
        CountLeaf3(T->rchild );
        if((!T->lchild) && (!T->rchild))	//既没有左子树也没有右子树
            ++count;						//对叶子结点计数
    }
}// CountLeaf


// 求二叉树深度  
int BiTreeDepth(BiTree T)
{
    int depth  , depthleft ,depthright ;
    if(!T){
        depth = 0;
    }
    else{
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
    PreOrderTraverse(T,Visit);
    printf("\n");
    InOrderTraverse1(T,Visit);
    printf("\n");
    CountLeaf(T, count);
    printf("%d\n",count);
    printf("%d\n",BiTreeDepth(T));


    return 0;
}
