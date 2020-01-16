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


// ��ʼ������ͷ���
Status InitList_L(LinkList &L)
{
	L = (LinkList)malloc(sizeof(LNode));
	L->data = 0;
	L->next = NULL;
	return OK;
}


// �㷨2.8.0 �����Ͳ���������Ҫ�������ã�Ҳ����Ҫ����ָ��
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


// ����GetElem_L
int main(void)
{
    LinkList L;
    ElemType e;
    int i;
    InitList_L(L);
    printf("%d\n",ListInsert_L(L,1,11));
    printf("%d\n",ListInsert_L(L,2,22));
    printf("%d\n",ListInsert_L(L,3,33));
    printf("%d\n",ListInsert_L(L,4,44));
    for(i = 1; i <= 4; ++i)
    {
        GetElemt_L(L ,i ,e);
        printf("��%d��Ԫ���� %d\n",i , e);
    }

    return 0;
}

