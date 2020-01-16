#include <stdio.h>
#include <stdlib.h>
#define Status          int //״̬
#define OVERFLOW        -1  //���
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

//�㷨2.11.0 ����L�����Ǵ�������&L��Ҳ�����Ǵ��ݵ�ַ*L�����ǲ����Ǽ�L
void CreateList_L(LinkList &L,int n){
    // ��λ������n��Ԫ�ص�ֵ(11,22,...,nn)����������ͷ���ĵ������Ա�L 
    // ͷ�巨
    LinkList p;
    int i; ElemType data = 11;
    L = (LinkList)malloc(sizeof(LNode));
    L->next = NULL;              // �Ƚ���һ����ͷ���ĵ�����
    for (i = n; i > 0; --i) {
        p = (LinkList)malloc(sizeof(LNode));  // �����½��
        p->data = data;               // ��Ϊһ��������ɵ�����
        p->next = L->next;    L->next = p;    // ���뵽��ͷ
        data += 11;
    }
} // CreateList_L


//�㷨2.11.1    β�巨
void CreateList_L1(LinkList &L,int n){
    // ˳λ������ÿ�������������20��n��Ԫ�ص�ֵ����������ͷ���ĵ������Ա�L 
    
    LinkList p, q;
    int i; ElemType data = 11;
    L = (LinkList)malloc(sizeof(LNode));
    L->next = NULL;              // �Ƚ���һ����ͷ���ĵ�����
    q = L;
    for (i = n; i > 0; --i) {
        p = (LinkList)malloc(sizeof(LNode));  // �����½��
        p->data = data;               // ����data
        p->next = q->next;    q->next = p;    // ���뵽��ͷ
        q = p;
        data += 11;
    }
} // CreateList_L

//�㷨2.11.2 ����L�����Ǵ�������&L��Ҳ�����Ǵ��ݵ�ַ*L�����ǲ����Ǽ�L
void CreateList_L2(LinkList *L,int n){
    // ��λ������n��Ԫ�ص�ֵ(11,22,...,nn)����������ͷ���ĵ������Ա�L 
    // ͷ�巨
    LinkList p;
    int i; ElemType data = 11;
    *L = (LinkList)malloc(sizeof(LNode));
    (*L)->next = NULL;              // �Ƚ���һ����ͷ���ĵ�����
    for (i = n; i > 0; --i) {
        p = (LinkList)malloc(sizeof(LNode));  // �����½��
        p->data = data;               // ��Ϊһ��������ɵ�����
        p->next = (*L)->next;    (*L)->next = p;    // ���뵽��ͷ
        data += 11;
    }
} // CreateList_L


//�㷨2.11.3 ����L�����Ǵ�������&L��Ҳ�����Ǵ��ݵ�ַ*L�����ǲ����Ǽ�L   ERROR!
void CreateList_L3(LinkList L,int n){
    // ��λ������n��Ԫ�ص�ֵ(11,22,...,nn)����������ͷ���ĵ������Ա�L 
    // ͷ�巨
    LinkList p;
    int i; ElemType data = 11;
    L = (LinkList)malloc(sizeof(LNode));
    L->next = NULL;              // �Ƚ���һ����ͷ���ĵ�����
    for (i = n; i > 0; --i) {
        p = (LinkList)malloc(sizeof(LNode));  // �����½��
        p->data = data;               // ��Ϊһ��������ɵ�����
        p->next = L->next;    L->next = p;    // ���뵽��ͷ
        data += 11;
    }
} // CreateList_L

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


// �����㷨2.11
int main(void)
{
    LinkList L;
    ElemType e;
    InitList_L(L);
    CreateList_L3(L, 5);
    ListTraverse_L(L, visit);



    return 0;
}



