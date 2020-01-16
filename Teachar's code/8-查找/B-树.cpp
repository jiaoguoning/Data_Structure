#include <stdio.h>
#include <stdlib.h>

//------------
#define  EQ(a, b)	((a)==(b))	//a,b为数值型
#define  LT(a, b)	((a)< (b))
#define  LQ(a, b)	((a)<=(b))
//B-树存储表示
#define KeyType int
#define Record char
#define 	m	3
typedef struct BTNode
{
	int keynum;				//结点中关键字的个数，即结点的大小
	struct BTNode * parent;	//指向双亲的结点
	KeyType key[m+1];		//关键字向量，0号单元未用
	struct BTNode* ptr[m+1];//子树指针向量
	Record *recptr[m+1];	//记录指针向量，0号单元未用
}BTNode,*BTree;				//B-树的结点和B-树的类型

typedef struct
{
	BTNode *pt;		//指向找到的结点
	int i;			//1...m在结点中关键字的序号
	int tag;		//1：查找成功，0：查找失败
}Result;			//B-树的查找结果类型

//创建二叉树的原始数据
const KeyType arr1[] = {45,24,53,90,3,12,37,50,61,70,100};
int arr_i = 0;
const int arrLen = 11;

int Search(BTree p ,KeyType K)					//可能存在问题 ！！！default
{
	int i = 0;
    for(i = 0;i < p->keynum && p->key[i+1] <= K;i++);
    return i;
}

Result SearchBTree(BTree T,KeyType K)			
	//在m阶B-树T上查找关键字K，返回结果(pt, i, tag)。若查找成功，则特征值tag = 1，指针pt所指结点中
	//第i个关键字等于K；否则特征值tag = 0，等于K的关键字应插入在指针pt所指结点中第i和第i+1个关键字之间
{
	Result r;
	BTree p = T, q = NULL;	//初始化，p指向待查结点，q指向p的双亲
	int found = 0, i = 0;
	while(p && !found)
	{
		i = Search(p , K);		//在p->key[1...keynum]中查找，
								//i使得：p->key[i] <= K < p->[i+1]
		if(i > 0 && p->key[i] == K)
			found = 1;			//找到关键字
		else
		{
			q = p;
			p = p->ptr[i];
		}
	}
	if(found)
	{
		r.pt = p;	//查找成功返回当前结点
		r.i = i;
		r.tag = 1;
	}else
	{
		r.pt = q;	//查找不成功返回双亲结点
		r.i = i;
		r.tag = 0;
	}
	return r;
}

void Insert(BTree &q,int i,KeyType  k, BTNode* ap)
{
	int j, flag = 0;
    for(j = q->keynum; j > i;--j)
	{                       //整体后移空出一个位置
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
    ap = (BTNode *)malloc(sizeof(BTNode));		//给结点ap分配空间
    ap->ptr[0] = q->ptr[s];						//后一半移入结点ap
    for(i = s + 1;i <= m; ++i)
	{
        ap->key[i - s] = q->key[i];
        ap->recptr[i - s] = q->recptr[i];
    }
	for(i = s ;i <= m; ++i)
        ap->ptr[i - s] = q->ptr[i];

    ap->keynum = q->keynum - s;                
    ap->parent = q->parent;
    for(i = 0;i <= q->keynum - s; ++i)			//修改双亲指针 
        if(ap->ptr[i]!=NULL) 
            ap->ptr[i]->parent = ap;
    q->keynum = s - 1 ;							//结点q的前一半保留,修改结点q的keynum
}

void NewRoot(BTree &T ,BTree q,KeyType k,BTNode* ap)
{
	T = (BTNode *)malloc(sizeof(BTNode));       //分配空间 
    T->keynum = 1;
    T->ptr[0] = q;
    T->ptr[1] = ap;
    T->key[1] = k;
    if(q != NULL)                               //调整结点q和ap的双亲指针 
        q->parent = T;
    if(ap != NULL) 
        ap->parent = T;
    T->parent=NULL;
}

int InsertBTree(BTree &T, KeyType K, BTree q, int i)
	//在m阶B-树T上结点*q的key[i]与key[i+1]之间插入关键字K。
	//若引起结点过大，则沿双亲链进行必要的结点分裂调整，使T仍是m阶B-树。
{
	KeyType x = K;
	int s;	
	BTNode * ap = NULL;			//或者 BTree ap = NULL;
	int finished = 0;
	BTree qq = q;				//点睛之笔，书上有些不太完美
	while (q && !finished)
	{
		Insert(q, i, x, ap);	//将x和ap分别插入到q->key[i+1]和q->ptr[i+1]
		if(q->keynum < m)		//不能超过m-1,否则进行结点分裂	
			finished = 1;		//插入完成
		else{
			s = (m + 1) / 2;
			split(q, s, ap);
			x = q->key[s];
			//将q->key[s+1...m],q->ptr[s...m]和q->recptr[s+1...m]
			//移入新结点*ap
			qq = q;				//点睛之笔
								//因为如果q->parentNULL的话，q得到双亲的值是NULL
								//这样在q生成根结点时,就丢失了q的内容，因此先放在qq中保存
			q = q->parent;
			if(q)
				i = Search(q,x);//在双亲结点*q中查找x的插入位置
		}//else
	}//while
	if(!finished)	//T是空树（参数q初值为NULL）或者根节点已分裂为结点*q和*ap
		NewRoot(T , qq, x, ap);	//生成信息(T, x, ap)的新的根节点*T，原T和ap为子树指针
	return 1;
}
	



int main(void)
{
    BTree t = NULL;
    Result s;                                       //设定查找结果 
    int j;
    for(j = 0;j < arrLen; ++j)
	{                               //逐一插入元素 
        s = SearchBTree(t,arr1[j]);
		if(s.tag == 0)
			InsertBTree(t,arr1[j],s.pt,s.i);
        printf("   第%d步,插入元素%d \n",j+1,arr1[j]);
	}
	s = SearchBTree(t,30);
		if(s.tag == 0)
			InsertBTree(t,30,s.pt,s.i);

	return 0;
}

