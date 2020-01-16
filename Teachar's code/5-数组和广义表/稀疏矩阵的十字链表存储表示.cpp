#include <stdio.h>
#include <stdlib.h>
#define ElemType int

typedef struct OLNode{
	int i,j;					//�÷���Ԫ���к����±�
	ElemType e;
	struct OLNode *right,*down;	//�÷���Ԫ�����б���б�ĺ������
}OLNode,*OLink;

typedef struct{
	OLink *rhead,*chead;
	int mu,nu,tu;
}CrossList;



int CreateSMatrix_OL(CrossList &M)
	//����ϡ�����M������ʮ������洢��ʾ��
{
	int m = 3,n = 4,t = 4,ii;
	M.mu = m;	M.nu = n;	M.tu = t;
	M.chead = M.rhead = NULL;

	if(!(M.rhead = (OLink *)malloc((m+1)*sizeof(OLink))))
		exit(-1);
	if(!(M.chead = (OLink *)malloc((n+1)*sizeof(OLink))))
		exit(-1);
	for(ii = 0; ii <= m;++ii)//��ʼ������ͷָ������������������Ϊ������
		M.rhead[ii] = NULL;
	for(ii = 0; ii <= n;++ii)
		M.chead[ii] = NULL;
	OLNode Node[6];
	Node[1].i = 1;	Node[1].j = 1;	Node[1].e = 3;
	Node[2].i = 1;	Node[2].j = 4;	Node[2].e = 5;
	Node[3].i = 2;	Node[3].j = 2;	Node[3].e = -1;
	Node[4].i = 3;	Node[4].j = 1;	Node[4].e = 2;
	Node[5].i = 0;	//������ֹ�����ѭ��
	for (ii = 1; ii  <= 5; )
	{
		int i,j,e;
		//������������������Ԫ
		for(i = Node[ii].i,j = Node[ii].j,e = Node[ii].e;++ii,
			i != 0;i = Node[ii].i,j = Node[ii].j,e = Node[ii].e)
		{
			OLNode *p = NULL,*q = NULL;
			if(!(p = (OLNode *)malloc(sizeof(OLNode))))	
				exit(-1);
			p->i = i;	p->j = j;	p->e = e;			//���ɽ��
			if(M.rhead[i] == NULL || M.rhead[i]->j > j)	
			//�����i��ͷָ��Ϊ�գ�	���ߵ�i����ָ��ĵ�һ������кű�Ҫ������кŴ�
			//��ôҪ����Ľ��Ҫ�ŵ���i�еĵ�һ��λ�ã�����ͷ�巨
			{
				p->right = M.rhead[i];					
				M.rhead[i] = p;
			}else
			{ //Ѱ�����б��еĲ���λ��
				//q->rightָ�����q��ָ�������һ����㣬����˵q->right�����һ�����ĵ�ַ
				for(q = M.rhead[i];(q->right) && q->right->j < j;q = q->right);
				//����forѭ����ѭ����Ϊ�գ���Ѱ��ǰ���Ĺ���
				p->right = q->right;
				q->right = p;
			}
			if(M.chead[j] == NULL || M.chead[j]->i > i)
			{
				p->down = M.chead[j];
				M.chead[j] = p;
			}else
			{
				for(q = M.chead[j]; (q->down) && q->down->i < i; q = q->down);
				p->down = q->down;
				q->down = p;
			
			}


		}
	}//iiѭ����ֵ

	return 1;
}


int main(void)
{
	CrossList M;
	CreateSMatrix_OL(M);
	M.chead[1]->right->e;
	M.rhead[1]->right->e;

	return 0;
}