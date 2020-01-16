#include <stdio.h>
#include <stdlib.h>

#define Status      int
#define OK          1
#define ERROR       0
#define OVERFLOW    -2
#define TElemType   char

typedef enum PointerTag {
    Link, Thread
}PointerTag;	//Link == 0��ָ�룬 Thread == 1������

typedef struct BiThrNode {
    TElemType data;
    struct BiThrNode *lchild, *rchild;	//���Һ���ָ��
    PointerTag LTag,RTag;				//���ұ�־
}BiThrNode, *BiThrTree;

char arr3[] = {'-','+','a','\0','\0','*','b','\0','\0','-','c','\0','\0','d','\0','\0','/','e','\0','\0','f','\0','\0'};
int arr_i = 0;

// �������������������������
Status CreateBiTree(BiThrTree *T) {
    char ch;
    ch = arr3[arr_i++];
    if(ch == '\0') {
        (*T) = NULL;
    }else{
        if(!((*T) = (BiThrNode *)malloc(sizeof(BiThrNode))))
            exit(OVERFLOW);
        (*T)->data = ch;			//���ɸ��ڵ�
        (*T)->LTag = Link;			//����ʱ��������־�򸳳�ֵ
        (*T)->RTag = Link;			//Ĭ�϶���Link
        CreateBiTree(&((*T)->lchild));//����������
        CreateBiTree(&((*T)->rchild));//����������
    }
    return OK;
}

Status Visit(TElemType e)
{
    if(!e)
        return ERROR;
    printf("%c ",e);
    return OK;
}

// �㷨 6.5 ����������������� 
Status InOrderTraverse_Thr(BiThrTree T,int (* Visit)(TElemType e))
{   //Tָ��ͷ��㣬ͷ��������lchildָ����ڵ㣬�ɲμ��������㷨��
    //�����������������T�ķǵݹ��㷨����ÿ������Ԫ�ص��ú���Visit��
    BiThrTree p;
    p = T->lchild;	//pָ����ڵ�
    while (p != T) {//�������������ʱ��p == T
        while (p->LTag == Link)
            p = p->lchild;	
        if(!Visit(p->data))	//����������Ϊ�յĽ��
            return ERROR;
        while (p->RTag == Thread && p->rchild != T)
        {
            p = p->rchild;
            Visit(p->data);	//���ʺ�̽��  ����Ϊɶ���ж�ʧ�ܣ�
        }
        p = p->rchild;
    }
    return OK;
}//InOrderTraverse_Thr


// �㷨6.7 ��������������������   
// �˴�Ҳ���԰�pre����Ϊȫ�ֱ������Ǿͽ�InOrderThreading�����е�pre����ȥ��
void InThreading(BiThrTree p,BiThrTree *pre)
{
    if(p){
        InThreading(p->lchild, pre);	//������������
        if(!p->lchild) {    	//��pָ����û�����ӣ�������ǰ��
            p->LTag = Thread;
            p->lchild = (*pre);	//ǰ��������
        }
        if(!(*pre)->rchild){		//��pָ����û���Һ��ӣ����������
            (*pre)->RTag = Thread;
            (*pre)->rchild = p;	//���������
        }
        (*pre) = p;				//����preָ��p��ǰ��
        InThreading(p->rchild, pre);	//������������
    }
}

// �㷨 6.6 ���������� 
Status InOrderThreading(BiThrTree *Thrt,BiThrTree T)
{   // �������������T��������������������Thrtָ��ͷ��㡣
    BiThrTree pre = NULL;
    if(!((*Thrt) = (BiThrNode *)malloc(sizeof(BiThrNode))))
        exit(OVERFLOW);
    (*Thrt)->LTag = Link;	(*Thrt)->RTag = Thread;	//��ͷ���
    (*Thrt)->data = '#';
    (*Thrt)->rchild = (*Thrt);						//��ָ���ָ
    if(!T) {
        (*Thrt)->lchild = (*Thrt);					//��������Ϊ�գ�����ָ���ָ(����ָ���Լ�)
    }else {
        (*Thrt)->lchild = T;
        pre = (*Thrt);
        InThreading(T, &pre);						//���������������������
        pre->rchild = (*Thrt);	pre->RTag = Thread;	//���һ�����������
        (*Thrt)->rchild = pre;
    }
    return OK;
}

int main(void)
{
    BiThrTree T,Thrt;
    CreateBiTree(&T);
    InOrderThreading(&Thrt,T);
    
    InOrderTraverse_Thr(Thrt,Visit);
    printf("\n");

    return 0;
}
