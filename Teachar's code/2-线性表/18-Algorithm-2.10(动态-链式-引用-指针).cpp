#include <stdio.h>
#include <stdlib.h>
#define Status          int //״̬
#define OVERFLOW        -2  //���
#define OK              1   //��ȷ
#define ERROR           0   //����

typedef int ElemType;

typedef struct LNode
{
	ElemType data;
	struct LNode *next;		//��������struct
}LNode, *LinkList;

Status InitList_L(LinkList &L)
{
	L = (LinkList)malloc(sizeof(LNode));
	L->data = 0;
	L->next = NULL;
	return OK;
}


// �㷨2.8.0
Status GetElemt_L(LinkList L,int i,ElemType &e)
	// LΪ��ͷ���ĵ������ͷָ��
    // ����i��Ԫ�ش���ʱ����ֵ����e������OK�����򷵻�ERROR
{
	LNode *p = L->next;	//ָ���j�����
	int j = 1;				//�ӵ�һ����ʼ������
	while ( p && j < i ){	//p��Ϊ����j < i
		p = p->next;
		++j;
	}						//pΪ�գ�˵������ѭ��������Ҳû�е���i�����   j==i
	if (!p || j > i){		//��Ϊ�˴���i   û�����ж�   ��� i==0  �� ����  ��������
							//���� i == j == 1 ���������ѭ������  ����
		return ERROR;
	}
	e = p->data;			//ͨ��������ʽ�ı��ڴ���Ԫ�ص�ֵ
	return OK;
}


//�㷨2.9.0
//�����мȿ��Դ���L��Ҳ������ *L   Ҳ������&L
Status ListInsert_L(LinkList &L,int i,ElemType e)	//�����޸�Ӧ�ò��� p = *L����
													//����дû�����⣬��Ϊpָ��ǰ�ڵ㣬�����޸�ֵ
							//ͷ����next����ܻ�ı䣬��˴���ͷָ��ĵ�ַ
{
	LinkList p = L;
	int j = 0;				//��Ϊ����Ѱ�ҵ��ǲ������ǰ������˴�ͷ��㿪ʼ
	LinkList s;
	while (p && j < i - 1){	//Ѱ�ҵ�i-1�����
		p = p->next;
		++j;
	}						
	if (!p || j > i - 1){
		return ERROR;
	}
	s = (LinkList)malloc(sizeof(LNode));
	s->data = e;
	s->next = p->next;
	p->next = s;				//����������������һ��λ�����⣻���ǵڶ���һ��Ҫ�ڵ�����ǰ��
	return OK;
}

//�㷨2.10.0
//�����мȿ��Դ���L��Ҳ������ *L   Ҳ������&L
Status ListDelete_L(LinkList &L,int i,ElemType &e)
{
	LinkList p = L;
	LinkList q;
	int j = 0;
	while (p->next && j < i-1){	//�ҵ�ɾ������ǰ�������ұ�֤���ǰ�����Next��Ϊ��
								//��Ϊ���ǰ������Next������ǿգ��޷����ɾ������
		p = p->next;
		++j;
	}
	if (!(p->next) || j > i-1)
		return ERROR;
	q = p->next;
	p->next = q->next;
	e = q->data;
	free(q);
	return OK;
}

//�㷨2.10.1
//�����мȿ��Դ���L��Ҳ������ *L   Ҳ������&L
Status ListDelete_L1(LinkList L,int i,ElemType &e)
{
	LinkList p = L;
	LinkList q;
	int j = 0;
	while (p->next && j < i-1){	//�ҵ�ɾ������ǰ�������ұ�֤���ǰ�����Next��Ϊ��
								//��Ϊ���ǰ������Next������ǿգ��޷����ɾ������
		p = p->next;
		++j;
	}
	if (!(p->next) || j > i-1)
		return ERROR;
	q = p->next;
	p->next = q->next;
	e = q->data;
	free(q);
	return OK;
}


//�㷨2.10.2
//�����мȿ��Դ���L��Ҳ������ *L   Ҳ������&L
Status ListDelete_L2(LinkList *L,int i,ElemType *e)
{
	LinkList p = (*L);
	LinkList q;
	int j = 0;
	while (p->next && j < i-1){	//�ҵ�ɾ������ǰ�������ұ�֤���ǰ�����Next��Ϊ��
								//��Ϊ���ǰ������Next������ǿգ��޷����ɾ������
		p = p->next;
		++j;
	}
	if (!(p->next) || j > i-1)
		return ERROR;
	q = p->next;
	p->next = q->next;
	*e = q->data;
	free(q);
	return OK;
}

Status visit(ElemType e) {
    if(printf("%d   ", e))
        return OK;
    return ERROR;
}

Status visit1(ElemType e) {
    if(printf("%d\n", e))
        return OK;
    return ERROR;
}

// ����
Status ListTraverse_L(LinkList L, Status (*pvisit)(ElemType)) {
    LNode *p = L->next;
    while (p) {
        if(!pvisit(p->data))
            return ERROR;
        p = p->next;
    }
    printf("\n");
    return OK;
}


// ���ԣ�ɾ��
int main(void)
{
	LinkList L;
    ElemType e;
    int i;
	InitList_L(L);
	ListInsert_L(L, 1, 11);
	ListInsert_L(L, 2, 22);
	ListInsert_L(L, 3, 33);
	ListInsert_L(L, 4, 44);
    ListInsert_L(L, 5, 55);
    ListInsert_L(L, 5, 66);
	ListTraverse_L(L, visit);
    ListDelete_L(L, 1, e);
    ListTraverse_L(L, visit);
	ListDelete_L1(L, 1, e);
    ListTraverse_L(L, visit);
	ListDelete_L2(&L, 1, &e);
    ListTraverse_L(L, visit);




	return 0;
}

