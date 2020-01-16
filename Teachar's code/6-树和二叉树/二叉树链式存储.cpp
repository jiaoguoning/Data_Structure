#include <stdio.h>
#include <stdlib.h>
#define TElemType char

//�������Ķ�������洢��ʾ
typedef struct BiTNode
{
	TElemType data;
	struct BiTNode *lchild ,*rchild;	//���Һ���ָ��
}BiTNode,*BiTree;

/*------------------ջ��ʵ��-----------------*/
#define STACK_INIT_SIZE 20
#define STACKINCREMENT 5
#define ElemType BiTree
typedef struct {
	ElemType *base;
	ElemType *top;
	int stacksize;
}SqStack;

//��ΪҪ�޸�ջS�ڴ������ݳ�Ա��ֵ����˱��봫��S�ĵ�ַ
int InitStack(SqStack *S)
{
	S->base = (ElemType*)malloc(sizeof(ElemType) * STACK_INIT_SIZE);
	if (!S->base)
	{
		printf("��ʼ��ʧ�ܣ�\n");
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
			printf("׷��ʧ��!\n");
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
		printf("��ջʧ�ܣ�ջΪ��!\n");
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


//������������ԭʼ����
char arr1[] = {'A','B','D','\0','\0','E','G','\0','\0','\0','C','\0','F','\0','\0'};
char arr2[] = {'A','B','E','\0','L','\0','\0','\0','D','H','M','\0','\0','I','\0','\0','J','\0','\0'};
char arr3[] = {'-','+','a','\0','\0','*','b','\0','\0','-','c','\0','\0','d','\0','\0','/','e','\0','\0','f','\0','\0'};

int arr_i = 0;



//���������������������
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
		T->data = ch;			//���ɸ��ڵ�
		CreateBiTree(T->lchild);//����������
		CreateBiTree(T->rchild);//����������
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
	//���ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú�����
	//�������������T�ĵݹ��㷨����ÿ������Ԫ�ص��ú���Visit��
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
	//���ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú�����
	//�������������T�ĵݹ��㷨����ÿ������Ԫ�ص��ú���Visit��
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
	//���ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú�����
	//�������������T�ĵݹ��㷨����ÿ������Ԫ�ص��ú���Visit��
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
	//���ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú�����
	//�������������T�ķǵݹ��㷨����ÿ������Ԫ�ص��ú���Visit��
{
	SqStack S;
	//char test;
	InitStack(&S);
	push(&S,T);	//��ָ���ջ
	PrintStack(S);
	//test = T->data;
	while (S.base != S.top)	
	{
		BiTree p;
		while (GetTop(S,&p) && p)
			//���������ǿ�����������Ϊ�գ������ߵ���ͷ������ջ
		{
			//if(p->lchild)
			//	test = p->lchild->data;
			//else
			//	test = 0;
			push(&S,p->lchild);	
			PrintStack(S);
		}
		pop(&S,&p);				//��ָ����ջ������������Ϊ�ջ���������Ϊ�����
		PrintStack(S);
		if(S.base != S.top)
		{
			pop(&S,&p);			//���ʽ�㣬ÿpopһ�Σ�p�����ƶ�������һ����ܼ���
			PrintStack(S);
			if(!Visit(p->data))
				return 0;
			//if(p->rchild)
			//	test = p->rchild->data;
			//else
			//	test = 0;
			push(&S,p->rchild);	//�����·��ƶ�һ��
			PrintStack(S);
		}
	}
	return 1;
}

int InOrderTraverse2(BiTree T,int (*Visit)(TElemType e))
	//���ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú�����
	//�������������T�ķǵݹ��㷨����ÿ������Ԫ�ص��ú���Visit��
	//�����淽������ڣ�p�ǿյ�ʱ�򣬲��ðѿ�Ҳ��ջ�ٳ�ջ
{
	SqStack S;
	char test;
	BiTree p;
	InitStack(&S);
	p = T;
	while(p || S.base != S.top)
	{
		if(p)	//ֻҪpָ�벻Ϊ�գ��ͽ�ջ������������
		{
			push(&S,p);
			PrintStack(S);
			p = p->lchild;
		}else   //����pΪ�յ������ջ
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
//***********�����˲��õݹ飬�Զ����������в�����һ�㷽��**********//
void CountLeaf(BiTree T, int &count)
	//�����������������count���ض�������Ҷ�ӽ�����Ŀ
	//conut��Ϊ���������ڴ���ʱcount��main��Ҫ����
{
	if(T)
	{
		if((!T->lchild) && (!T->rchild))	//��û��������Ҳû��������
			++count;						//��Ҷ�ӽ�����
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



