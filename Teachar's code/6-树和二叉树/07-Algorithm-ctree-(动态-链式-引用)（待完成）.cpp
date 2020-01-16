#include <stdio.h>
#include <stdlib.h>


//1. 树的双亲存储表示
#define MAX_TREE_SIZE 100
#define TElemType char
typedef struct			//结点结构
{
	TElemType data;
	int parent;			//双亲的位置域
}PTNode;

typedef struct			//树的结构
{
	PTNode nodes[MAX_TREE_SIZE];
	int r,n;			//根的位置和结点数
}PTree;

//2. 树的孩子链表存储表示法
typedef struct CTNode
{
	int child;
	struct CTNode * next;
}*ChildPtr;

typedef struct
{
	TElemType data;
	ChildPtr firstchild;//孩子链表头指针
}CTBox;

typedef struct
{
	CTBox nodes[MAX_TREE_SIZE];
	int n,r;			//结点数和根的位置
}CTree;

//3. 树的二叉链表（孩子-兄弟）存储表示法
typedef struct CSNode
{
	TElemType data;
	struct CSNode *firstchild, *nextsibling;
}CSNode, *CSTree;

int main(void)
{



	return 0;
}

