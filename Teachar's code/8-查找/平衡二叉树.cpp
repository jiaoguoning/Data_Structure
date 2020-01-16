#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define Status int
#define OK	1
#define ERROR	0

#define Boolean int
#define FALSE	0
#define TRUE	1



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

typedef struct BSTNode
{
	TElemType data;
	int bf;								//����ƽ������
	struct BSTNode *lchild ,*rchild;	//���Һ���ָ��
}BSTNode,*BSTree;

#define LH	1
#define EH	0
#define RH	-1

/*
����*T��������������
    1.�õ�������lc
    2.����*T�����ӵ���lc���Һ���
    3.��lc���Һ��ӵ�����*T
    4.������Ϊlc
*/
//��������  ��ͼд
void R_Rotate(BSTree *p)
	//����*pΪ���Ķ�����������������������֮��pָ���µ�������㣬����ת
	//����֮ǰ���������ĸ����
{
    BSTree lc = (*p)->lchild;	//lcָ���*p�������������
    (*p)->lchild = lc->rchild;	//lc���������ҽ�Ϊ*p��������
    lc->rchild = (*p);			//pָ���µĸ����
    (*p) = lc;
}

/*
����*T��������������
    1.�õ����Һ���rc
    2.����*T���Һ��ӵ���rc������
    3.��lc�����ӵ�����*T
    4.������Ϊrc
*/
//��������
void L_Rotate(BSTree *T)
{
    BSTree rc = (*T)->rchild;
    (*T)->rchild = rc->lchild;
    rc->lchild = (*T);
    (*T) = rc;
}

//������ƽ�⴦��
void LeftBalance(BSTree *T)
{
    BSTree lc = NULL, rd = NULL;
    lc = (*T)->lchild;

    switch(lc->bf)
    {
    case LH:     //���������������ӣ���������
        (*T)->bf = lc->bf = EH;
        R_Rotate(T);        break;
    case RH:    //�������������Һ��ӣ����������������������������������
        rd = lc->rchild;
/*-----------------NO---------------------*/
        switch(rd->bf)
        {
        case LH:
            (*T)->bf = RH;
            lc->bf = EH;
            break;
        case EH:
            (*T)->bf = lc->bf = EH;
            break;
        case RH:
            (*T)->bf = EH;
            lc->bf = LH;
            break;
        }
        rd->bf = EH;
/*----------------------------------------*/
        L_Rotate(&((*T)->lchild));
        R_Rotate(T);
    }
}

//������ƽ�⴦��
void RightBalance(BSTree *T)
{
    BSTree rc = NULL, ld = NULL;

    rc = (*T)->rchild;

    switch(rc->bf)
    {
    case RH:     //���������������ӣ���������
        (*T)->bf = rc->bf = EH;
        L_Rotate(T);
        break;
    case LH:    //�������������Һ��ӣ����������������������������������
        ld = rc->lchild;
/*-----------------NO---------------------*/
        switch(ld->bf)
        {
        case RH:
            (*T)->bf = LH;
            rc->bf = EH;
            break;
        case EH:
            (*T)->bf = rc->bf = EH;
            break;
        case LH:
            (*T)->bf = EH;
            rc->bf = RH;
            break;
        }
        ld->bf = EH;
/*----------------------------------------*/
        R_Rotate(&((*T)->rchild));
        L_Rotate(T);
    }
}

//����ƽ�������,taller��ʾС���Ƿ񳤸�     false û���� true ����
Status InsertAVL(BSTree * T, ElemType e, bool *taller)
{
    //��Ϊ�գ�ֱ�Ӳ���
    if(!(*T))
    {
        /*
        ����Ҷ�ӽ�㣬tallerΪtrue����ʾС������
        */
        (*T) = (BSTree)malloc(sizeof(BSTNode));
        (*T)->data = e;
        (*T)->lchild = (*T)->rchild = NULL;
        (*T)->bf = EH;
        *taller = TRUE;
    }
    else//��Ϊ�յ����
    {
        //Ԫ���Ѵ��ڣ��ܾ�����
        if(EQ(e.key, (*T)->data.key))//���ڸ��ڵ�
        {
            taller = FALSE;
            return ERROR;
        }
		if(LT(e.key, (*T)->data.key))//С�ڸ��ڵ㣬���������в���
        {
            //���벻�ɹ�
            if(!InsertAVL(&(*T)->lchild, e, taller))
                 return 0;
            //С������
            if(*taller)
            {
                switch ((*T)->bf)
                {
                case LH:				//ע���ǵݹ飬ԭ���������ߣ������������ֳ����ˣ��ƻ���ƽ����
                    LeftBalance(T);		//������ƽ�⴦��
                    *taller = FALSE;	//ƽ�⴦��֮�����ĸ߶���Ϊ����ڵ�֮ǰ,δ����
                    break;
                case EH:				//ԭ�����������ȸߣ��������������ߣ�������Ȼ����ƽ��������Ķ���
                    (*T)->bf = LH;      //����������
                    *taller = TRUE;		//�����峤��
                    break;
                case RH:
                    (*T)->bf = EH;		//ԭ���������ߣ�����������֮����������һ����
                    *taller = FALSE;    //������Ͳ���֮ǰһ���ߣ�������ƽ����δ���ƻ�
                    break;
                }
            }
        }
        else					//���ڸ��ڵ㣬���������н��в���
        {
            //����ʧ��
            if(!InsertAVL(&(*T)->rchild, e, taller))
                return ERROR;
            //С������
            if(*taller)
            {
                switch((*T)->bf)
                {
                case LH:
                    (*T)->bf = EH;       //ԭ������ߵ�С���ߣ��ұߵ�С������֮�󣬾�һ������
                    *taller = FALSE;      //������˵��С����δ����
                    break;
                case EH:
                    (*T)->bf = RH;       //ԭ��������С��һ���ߣ������ұߵ�С������֮���ұߵ�С����
                    *taller = TRUE;      //������˵���������ˣ����ǲ�δ�ƻ������ƽ����
                    break;
                case RH:     //ԭ���Ǿ����ұߵ�С���ߣ��ұߵ�С���ٳ���֮�󣬾��ƻ�����������ƽ����
                    RightBalance(T);      //ƽ�⴦��
                    *taller = FALSE;      //����֮������δ����
                    break;
                }
            }
        }
    }

    return OK;
}

//�������
void Traverse(BSTree T)
{
    if(T)
    {
        Traverse(T->lchild);
        printf("%d ", T->data.key);
        Traverse(T->rchild);
    }
}

//�������
void PreTraverse(BSTree T)
{
    if(T)
    {
        printf("%d ", T->data.key);
        PreTraverse(T->lchild);
        PreTraverse(T->rchild);
    }
}

int arr[10] = {1, 6, 9, 5, 6, 4, 2, 8, 7, 5};

int main(void)
{
    int i;
    bool taller;
    ElemType e;
    BSTree T = NULL;

    for(i = 0; i < 10; ++i)
    {
        e.key = arr[i];
        InsertAVL(&T, e, &taller);
    }
    printf("����\n");
    Traverse(T);
    printf("\n����\n");
    PreTraverse(T);
		printf("\n");

    return 0;
}

/*
����
1 2 4 5 6 7 8 9
����
4 1 2 6 5 8 7 9
*/
