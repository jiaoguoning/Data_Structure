#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//------------
#define  EQ(a, b)	((a)==(b))	//a,bΪ��ֵ��
#define  LT(a, b)	((a)< (b))
#define  LQ(a, b)	((a)<=(b))

#define KeyType int
#define InfoType char

typedef struct
{
	KeyType key;	//����Ԫ���в��ҵĹؼ���
	InfoType* info;	//����Ԫ���е�������Ϣ
}ElemType;

typedef struct
{
	ElemType *elem;	//����Ԫ�ش洢�ռ��ַ������ʱ��ʵ�ʳ��ȷ��䣬0�ŵ�Ԫ����
	int length;		//����
}SSTable;
//------------

//�������Ķ�������洢��ʾ
#define TElemType ElemType

typedef struct BiTNode
{
	TElemType data;
	int pos;
	struct BiTNode *lchild ,*rchild;	//���Һ���ָ��
}BiTNode,*BiTree;




int Visit(TElemType e)
{
	if(!e.key)
		return 0;
	printf("%d ",e.key);
	return 1;
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




BiTree SearchBST1(BiTree T,KeyType key)
	//�ڸ�ָ��T��ָ�����������еݹ�ز���ĳ�ؼ��ֵ���key������Ԫ�أ�
	//�����ҳɹ����򷵻�ָ������ݽ���ָ�룬���򷵻ؿ�ָ��
{
	if((!T) || EQ(key,T->data.key))
		return T;							//���ҽ���
	else if(LT(key, T->data.key))
		return (SearchBST1(T->lchild,key));	//���������м�������
	else
		return (SearchBST1(T->rchild,key));	//���������м�������
}



int SearchBST2(BiTree T,KeyType key,BiTree f,BiTree &p)
	//�ڸ�ָ��T��ָ�����������еݹ�ز���ĳ�ؼ��ֵ���key������Ԫ�أ�
	//�����ҳɹ���ָ��pָ�������Ԫ�صĽ�㣬������1������pָ�����·��
	//�Ϸ��ʵ����һ����㲢����0��ָ��fָ��T��˫�ף��ҳ�ʼ����ֵ��NULL
{
	if(!T)						//���Ҳ��ɹ�
	{
		p = f;
		return 0;
	}
	else if(EQ(key,T->data.key))//���ҳɹ�
	{
		p = T;
		return 1;
	}else if(LT(key,T->data.key))//����������������
	{
		return SearchBST2(T->lchild,key,T,p);
	}
	else						//����������������
	{
		return SearchBST2(T->rchild,key,T,p);
	}
}

void PrintSearchBST(BiTree T1)
{
	if(T1)
		printf("�鵽�Ľ����%d��\n", T1->data.key);
	else
		printf("δ�鵽�����\n");
}

int InsertBST(BiTree &T, ElemType e)
	//������������T�в����ڹؼ��ֵ���e.key������Ԫ��ʱ������e������1��
	//���򷵻�0.
{
	BiTree p, s;	
	if(!SearchBST2(T,e.key,NULL,p))
	{
		s = (BiTree)malloc(sizeof(BiTNode));
		s->data.key = e.key;
		s->lchild = s->rchild = NULL;
		if(!p)
			T = s;						//����ڵ�*sΪ�µĸ��ڵ�
		else if(LT(e.key,p->data.key))	//�жϲ���Ľ��keyֵ�Ͳ���λ��˫�׽���С���жϲ�����߻����ұ�
			p->lchild = s;				//����ڵ�*sΪ�µ����ӽڵ�
		else
			p->rchild = s;				//����ڵ�*sΪ�µ��Һ��ӽڵ�
		return 1;
	}

	return 0;	//�����Ѵ��ڹؼ�����ͬ�Ľ�㣬���ز���
}

//Ŀ������Ҫɾ������ǰ������ǰ������Ҫɾ���Ľ�㣬��������ʹ������������ܵ�Ӱ��
int Delete(BiTree &p)
	//�Ӷ�����������ɾ�����p�����ؽ��������������
{
	BiTree q, s;
	if(!p->rchild)		//����������ֻ���ؽ����������� ����Ҷ�ӽ��ɾ�����
	{
		q = p;
		p = p->lchild;
		free(q);
	}else if(!p->lchild)//ֻ���ؽ�����������
	{
		q = p;
		p = p->rchild;
		free(q);
	}else				//��������������
	{
		q = p;
		s = p->lchild;
		while (s->rchild)
		{
			q = s;
			s = s->rchild;	//sָ����������Ȼ�������ߵ���ͷ��Ҳ���Ǳ�ɾ�����ġ�ǰ����
		}
		p->data = s->data;	//��ǰ���������ݸ��Ƹ�Ҫɾ���Ľ��
		if(q != p)
			q->rchild = s->lchild;	//ǰ������Ҫɾ���Ľ��
		else
			q->lchild = s->lchild;	//����������Ҫɾ���Ľ��
		free(s);
	}
	return 1;
}

int DeleteBST(BiTree &T, KeyType key)
	//������������T�д��ڹؼ��ֵ���key������Ԫ��ʱ����ɾ��������Ԫ�صĽ�㣬
	//������1,���򷵻�0.
{
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

	for (i = 0; i < 8; i++)
	{
		e.key = arr[i];
		InsertBST(T, e);
	}

	printf("�������:");
	PreOrderTraverse(T,Visit);
	printf("\n�������:");
	InOrderTraverse(T,Visit);
	printf("\n");

	printf("---------------------\n");
	DeleteBST(T,37);
	printf("�������:");
	PreOrderTraverse(T,Visit);
	printf("\n�������:");
	InOrderTraverse(T,Visit);
	printf("\n");

	return 0;
}
/*
�������:45 2 37 24 40 90 53 50
�������:2 24 37 40 45 50 53 90
---------------------
�������:45 2 24 40 90 53 50
�������:2 24 40 45 50 53 90
�밴���������. . .
*/