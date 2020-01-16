#include <stdio.h>
#include <stdlib.h>

//------------
#define  EQ(a, b)	((a)==(b))	//a,bΪ��ֵ��
#define  LT(a, b)	((a)< (b))
#define  LQ(a, b)	((a)<=(b))
//B-���洢��ʾ
#define KeyType int
#define Record char
#define 	m	3
typedef struct BTNode
{
	int keynum;				//����йؼ��ֵĸ����������Ĵ�С
	struct BTNode * parent;	//ָ��˫�׵Ľ��
	KeyType key[m+1];		//�ؼ���������0�ŵ�Ԫδ��
	struct BTNode* ptr[m+1];//����ָ������
	Record *recptr[m+1];	//��¼ָ��������0�ŵ�Ԫδ��
}BTNode,*BTree;				//B-���Ľ���B-��������

typedef struct
{
	BTNode *pt;		//ָ���ҵ��Ľ��
	int i;			//1...m�ڽ���йؼ��ֵ����
	int tag;		//1�����ҳɹ���0������ʧ��
}Result;			//B-���Ĳ��ҽ������

//������������ԭʼ����
const KeyType arr1[] = {45,24,53,90,3,12,37,50,61,70,100};
int arr_i = 0;
const int arrLen = 11;

int Search(BTree p ,KeyType K)					//���ܴ������� ������default
{
	int i = 0;
    for(i = 0;i < p->keynum && p->key[i+1] <= K;i++);
    return i;
}

Result SearchBTree(BTree T,KeyType K)			
	//��m��B-��T�ϲ��ҹؼ���K�����ؽ��(pt, i, tag)�������ҳɹ���������ֵtag = 1��ָ��pt��ָ�����
	//��i���ؼ��ֵ���K����������ֵtag = 0������K�Ĺؼ���Ӧ������ָ��pt��ָ����е�i�͵�i+1���ؼ���֮��
{
	Result r;
	BTree p = T, q = NULL;	//��ʼ����pָ������㣬qָ��p��˫��
	int found = 0, i = 0;
	while(p && !found)
	{
		i = Search(p , K);		//��p->key[1...keynum]�в��ң�
								//iʹ�ã�p->key[i] <= K < p->[i+1]
		if(i > 0 && p->key[i] == K)
			found = 1;			//�ҵ��ؼ���
		else
		{
			q = p;
			p = p->ptr[i];
		}
	}
	if(found)
	{
		r.pt = p;	//���ҳɹ����ص�ǰ���
		r.i = i;
		r.tag = 1;
	}else
	{
		r.pt = q;	//���Ҳ��ɹ�����˫�׽��
		r.i = i;
		r.tag = 0;
	}
	return r;
}

void Insert(BTree &q,int i,KeyType  k, BTNode* ap)
{
	int j, flag = 0;
    for(j = q->keynum; j > i;--j)
	{                       //������ƿճ�һ��λ��
        q->key[j+1] = q->key[j];
        q->ptr[j+1] = q->ptr[j];
		flag = 1;
    }
    q->key[i+1] = k;
    q->ptr[i+1] = ap;
    if(ap != NULL) 
        ap->parent = q;
	q->keynum++;
}

void split(BTree &q, int s,BTNode* &ap)
{
	int i;
    ap = (BTNode *)malloc(sizeof(BTNode));		//�����ap����ռ�
    ap->ptr[0] = q->ptr[s];						//��һ��������ap
    for(i = s + 1;i <= m; ++i)
	{
        ap->key[i - s] = q->key[i];
        ap->recptr[i - s] = q->recptr[i];
    }
	for(i = s ;i <= m; ++i)
        ap->ptr[i - s] = q->ptr[i];

    ap->keynum = q->keynum - s;                
    ap->parent = q->parent;
    for(i = 0;i <= q->keynum - s; ++i)			//�޸�˫��ָ�� 
        if(ap->ptr[i]!=NULL) 
            ap->ptr[i]->parent = ap;
    q->keynum = s - 1 ;							//���q��ǰһ�뱣��,�޸Ľ��q��keynum
}

void NewRoot(BTree &T ,BTree q,KeyType k,BTNode* ap)
{
	T = (BTNode *)malloc(sizeof(BTNode));       //����ռ� 
    T->keynum = 1;
    T->ptr[0] = q;
    T->ptr[1] = ap;
    T->key[1] = k;
    if(q != NULL)                               //�������q��ap��˫��ָ�� 
        q->parent = T;
    if(ap != NULL) 
        ap->parent = T;
    T->parent=NULL;
}

int InsertBTree(BTree &T, KeyType K, BTree q, int i)
	//��m��B-��T�Ͻ��*q��key[i]��key[i+1]֮�����ؼ���K��
	//���������������˫�������б�Ҫ�Ľ����ѵ�����ʹT����m��B-����
{
	KeyType x = K;
	int s;	
	BTNode * ap = NULL;			//���� BTree ap = NULL;
	int finished = 0;
	BTree qq = q;				//�㾦֮�ʣ�������Щ��̫����
	while (q && !finished)
	{
		Insert(q, i, x, ap);	//��x��ap�ֱ���뵽q->key[i+1]��q->ptr[i+1]
		if(q->keynum < m)		//���ܳ���m-1,������н�����	
			finished = 1;		//�������
		else{
			s = (m + 1) / 2;
			split(q, s, ap);
			x = q->key[s];
			//��q->key[s+1...m],q->ptr[s...m]��q->recptr[s+1...m]
			//�����½��*ap
			qq = q;				//�㾦֮��
								//��Ϊ���q->parentNULL�Ļ���q�õ�˫�׵�ֵ��NULL
								//������q���ɸ����ʱ,�Ͷ�ʧ��q�����ݣ�����ȷ���qq�б���
			q = q->parent;
			if(q)
				i = Search(q,x);//��˫�׽��*q�в���x�Ĳ���λ��
		}//else
	}//while
	if(!finished)	//T�ǿ���������q��ֵΪNULL�����߸��ڵ��ѷ���Ϊ���*q��*ap
		NewRoot(T , qq, x, ap);	//������Ϣ(T, x, ap)���µĸ��ڵ�*T��ԭT��apΪ����ָ��
	return 1;
}
	



int main(void)
{
    BTree t = NULL;
    Result s;                                       //�趨���ҽ�� 
    int j;
    for(j = 0;j < arrLen; ++j)
	{                               //��һ����Ԫ�� 
        s = SearchBTree(t,arr1[j]);
		if(s.tag == 0)
			InsertBTree(t,arr1[j],s.pt,s.i);
        printf("   ��%d��,����Ԫ��%d \n",j+1,arr1[j]);
	}
	s = SearchBTree(t,30);
		if(s.tag == 0)
			InsertBTree(t,30,s.pt,s.i);

	return 0;
}

