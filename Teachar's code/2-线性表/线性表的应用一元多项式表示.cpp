#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0
typedef int Status;

typedef struct	//项的表示，多项式的项作为LinkList的数据元素
{
	float coef;	//系数
	int expn;	//指数
}term, ElemType;//两个类型名：term用于本ADT，ElemType为LinkList的数据对象名

typedef struct Node
{
	ElemType data;
	struct Node * next;	
}LNode, *LinkList, *Position;

typedef LinkList polynomial;

Status InitList(LinkList &L)
{
	L = (LinkList)malloc(sizeof(LNode));
	L->data.coef = 0;
	L->data.expn = 0;
	L->next = NULL;
	return OK;
}
//PPT上的例子
int Arr[] = {7,0,3,1,9,8,5,17};
int Brr[] = {8,1,22,7,-9,8};

void SetCurElem(polynomial &h,term e)
{
	h->data.coef = e.coef;
	h->data.expn = e.expn;
}
int cmp(term a, term b)
{	//依a的指数值<、=或>b的指数值，分别返回-1、0或+1
	if (a.expn == b.expn)
		return 0;
	else
		return (a.expn - b.expn) / abs(a.expn - b.expn);
}

Status LocateElem(polynomial L, term e, Position &q, int  (*compare)(term,term))
	//若升序链表L中存在与e满足判定函数compare()取值为0的元素，则q指示L中 
	//第一个值为e的结点的位置，并返回TRUE；否则q指示第一个与e满足判定函数
	//compare()取值>0的元素的前驱的位置。并返回FALSE。（用于一元多项式）
{
	LinkList p = L, pp;
	do
	{
		pp = p;		//pp指向p的前驱
		p = p->next;
	} while (p && (compare(p->data, e)<0)); // 没到表尾且p->data.expn<e.expn 
	if (!p || compare(p->data, e)>0)		// 到表尾或compare(p->data,e)>0 
	{
		q = pp;
		return 0;
	}else 
	{										// 没到表尾且p->data.expn == e.expn 
		q = p;
		return 1;
	}
}

Status MakeNode(LinkList &p, ElemType e)
{	//分配由p指向的值为e的结点，并返回OK；若分配失败。则返回ERROR.
    p = (LinkList)malloc(sizeof(LNode));
    if (!p)
        return ERROR;
    p->data = e;
    return OK;
}
Status InsFirst(LinkList q, LinkList s)
{	//将s指向的结点，插入到q指向的结点后面
    s->next = q->next;
    q->next = s;
    return OK;
}

void CreatPolyn(polynomial &P, int m)
	//输入m项的系数和指数，建立表示一元多项式的有序链表P
{
	polynomial h;	ElemType e;		int i;
	InitList(P);
	printf("请输入%d个项的系数和指数：\n",m);
	h = P;
	e.coef = 0.0;
	e.expn = -1;
	SetCurElem(h, e);	//设置头结点的数据元素

	for(i = 1; i <= m; ++i)
	{
		Position q;	LinkList s;
		scanf("%f %d",&e.coef,&e.expn);
		if(!LocateElem(P, e, q, cmp))	//当前链表不存在该指数项
		{
			if(MakeNode(s, e))
				InsFirst(q,s);			//生成结点并插入链表
		}
	}
}//CreatPolyn

Status DelFirst(LinkList h, LinkList q) 
{	//h指向q的前驱，让h指向q的下一个结点
	h->next = q->next;
	return 1;
}

Status ListEmpty(LinkList L)
{ 
    if (!L->next)
        return 0;
    else
        return 1;
}
Status Append(LinkList &L, LinkList s)
{	//将指针s(s->data为第一个数据元素)所指(彼此以指针相链,以NULL结尾)的
    //一串结点链接在线性链表L的最后一个结点之后
    LinkList p = L, q = s,newnode;
	while (p->next)
		p = p->next;
	while (q)
	{
		s = s->next;
		MakeNode(newnode,q->data);
		newnode->next = NULL;
		q = s;
		p->next = newnode;
		p = p->next;
	}

    return 1;
}

void DestroyList(LinkList &L)
{
	LinkList p = L;
	while(p)
	{
		L = p->next;
		free(p);
		p = L;
	}
}

void AddPolyn(polynomial &Pa, polynomial &Pb)
	//多项式的加法：Pa = Pa + Pb,利用两个多项式的结点构成“和多项式”。 
{
	LinkList ha = Pa;		//ha和hb分别指向Pa和Pb的头指针
	LinkList hb = Pb;
	LinkList qa = Pa->next;
	LinkList qb = Pb->next;	//ha和hb分别指向pa和pb的前驱
	while (qa && qb)		//如果qa和qb均非空
	{
		float sum = 0.0;
		term a = qa->data;
		term b = qb->data;
		switch (cmp(a,b))
		{
		case -1:	//多项式PA中当前结点的指数值小
			ha = qa;
			qa = qa->next;
			break;
		case 0:		//两者指数值相等
			sum = a.coef + b.coef;
			if(sum != 0.0)
			{	//修改多项式PA中当前结点的系数值
				qa->data.coef = sum;
				ha = qa;
			}else
			{	//删除多项式PA中当前结点
				DelFirst(ha, qa);
				free(qa);
			}
			DelFirst(hb, qb);
			free(qb);
			qb = hb->next;
			qa = ha->next;
			break;
		case 1:
			DelFirst(hb, qb);
			InsFirst(ha, qb);
			qb = hb->next;
			ha = ha->next;
			break;
		}//switch
	}//while
	if(!ListEmpty(Pb))
		Append(Pa,qb);
	DestroyList(hb);

}//AddPolyn
//运行PPT上例子准确无误

void Print(polynomial P)
{
	polynomial p = P->next,q;
	while (p->next)
	{
		if(p->data.coef > 0)
			if(p->data.expn)
				printf("(%.1f)x^%d+",p->data.coef,p->data.expn);
			else
				printf("(%.1f)+",p->data.coef);
		p = p->next;
	}
	printf("(%.1f)x^%d\n",p->data.coef,p->data.expn);
}

int main(void)
{
	polynomial P1,P2;
	CreatPolyn(P1, 4);
	Print(P1);
	CreatPolyn(P2, 3);
	Print(P2);
	AddPolyn(P1, P2);
	printf("相加结果为：\n");
	Print(P1);

	DestroyList(P1);



	return 0;
}
