#include <stdio.h>
#include <stdlib.h>


//1. ����˫�״洢��ʾ
#define MAX_TREE_SIZE 100
#define TElemType char
typedef struct			//���ṹ
{
	TElemType data;
	int parent;			//˫�׵�λ����
}PTNode;

typedef struct			//���Ľṹ
{
	PTNode nodes[MAX_TREE_SIZE];
	int r,n;			//����λ�úͽ����
}PTree;

//2. ���ĺ�������洢��ʾ��
typedef struct CTNode
{
	int child;
	struct CTNode * next;
}*ChildPtr;

typedef struct
{
	TElemType data;
	ChildPtr firstchild;//��������ͷָ��
}CTBox;

typedef struct
{
	CTBox nodes[MAX_TREE_SIZE];
	int n,r;			//������͸���λ��
}CTree;

//3. ���Ķ�����������-�ֵܣ��洢��ʾ��
typedef struct CSNode
{
	TElemType data;
	struct CSNode *firstchild, *nextsibling;
}CSNode, *CSTree;

int main(void)
{



	return 0;
}

