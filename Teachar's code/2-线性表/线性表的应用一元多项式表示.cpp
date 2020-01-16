#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0
typedef int Status;

typedef struct	//��ı�ʾ������ʽ������ΪLinkList������Ԫ��
{
	float coef;	//ϵ��
	int expn;	//ָ��
}term, ElemType;//������������term���ڱ�ADT��ElemTypeΪLinkList�����ݶ�����

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
//PPT�ϵ�����
int Arr[] = {7,0,3,1,9,8,5,17};
int Brr[] = {8,1,22,7,-9,8};

void SetCurElem(polynomial &h,term e)
{
	h->data.coef = e.coef;
	h->data.expn = e.expn;
}
int cmp(term a, term b)
{	//��a��ָ��ֵ<��=��>b��ָ��ֵ���ֱ𷵻�-1��0��+1
	if (a.expn == b.expn)
		return 0;
	else
		return (a.expn - b.expn) / abs(a.expn - b.expn);
}

Status LocateElem(polynomial L, term e, Position &q, int  (*compare)(term,term))
	//����������L�д�����e�����ж�����compare()ȡֵΪ0��Ԫ�أ���qָʾL�� 
	//��һ��ֵΪe�Ľ���λ�ã�������TRUE������qָʾ��һ����e�����ж�����
	//compare()ȡֵ>0��Ԫ�ص�ǰ����λ�á�������FALSE��������һԪ����ʽ��
{
	LinkList p = L, pp;
	do
	{
		pp = p;		//ppָ��p��ǰ��
		p = p->next;
	} while (p && (compare(p->data, e)<0)); // û����β��p->data.expn<e.expn 
	if (!p || compare(p->data, e)>0)		// ����β��compare(p->data,e)>0 
	{
		q = pp;
		return 0;
	}else 
	{										// û����β��p->data.expn == e.expn 
		q = p;
		return 1;
	}
}

Status MakeNode(LinkList &p, ElemType e)
{	//������pָ���ֵΪe�Ľ�㣬������OK��������ʧ�ܡ��򷵻�ERROR.
    p = (LinkList)malloc(sizeof(LNode));
    if (!p)
        return ERROR;
    p->data = e;
    return OK;
}
Status InsFirst(LinkList q, LinkList s)
{	//��sָ��Ľ�㣬���뵽qָ��Ľ�����
    s->next = q->next;
    q->next = s;
    return OK;
}

void CreatPolyn(polynomial &P, int m)
	//����m���ϵ����ָ����������ʾһԪ����ʽ����������P
{
	polynomial h;	ElemType e;		int i;
	InitList(P);
	printf("������%d�����ϵ����ָ����\n",m);
	h = P;
	e.coef = 0.0;
	e.expn = -1;
	SetCurElem(h, e);	//����ͷ��������Ԫ��

	for(i = 1; i <= m; ++i)
	{
		Position q;	LinkList s;
		scanf("%f %d",&e.coef,&e.expn);
		if(!LocateElem(P, e, q, cmp))	//��ǰ�������ڸ�ָ����
		{
			if(MakeNode(s, e))
				InsFirst(q,s);			//���ɽ�㲢��������
		}
	}
}//CreatPolyn

Status DelFirst(LinkList h, LinkList q) 
{	//hָ��q��ǰ������hָ��q����һ�����
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
{	//��ָ��s(s->dataΪ��һ������Ԫ��)��ָ(�˴���ָ������,��NULL��β)��
    //һ�������������������L�����һ�����֮��
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
	//����ʽ�ļӷ���Pa = Pa + Pb,������������ʽ�Ľ�㹹�ɡ��Ͷ���ʽ���� 
{
	LinkList ha = Pa;		//ha��hb�ֱ�ָ��Pa��Pb��ͷָ��
	LinkList hb = Pb;
	LinkList qa = Pa->next;
	LinkList qb = Pb->next;	//ha��hb�ֱ�ָ��pa��pb��ǰ��
	while (qa && qb)		//���qa��qb���ǿ�
	{
		float sum = 0.0;
		term a = qa->data;
		term b = qb->data;
		switch (cmp(a,b))
		{
		case -1:	//����ʽPA�е�ǰ����ָ��ֵС
			ha = qa;
			qa = qa->next;
			break;
		case 0:		//����ָ��ֵ���
			sum = a.coef + b.coef;
			if(sum != 0.0)
			{	//�޸Ķ���ʽPA�е�ǰ����ϵ��ֵ
				qa->data.coef = sum;
				ha = qa;
			}else
			{	//ɾ������ʽPA�е�ǰ���
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
//����PPT������׼ȷ����

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
	printf("��ӽ��Ϊ��\n");
	Print(P1);

	DestroyList(P1);



	return 0;
}
