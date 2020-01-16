#include <stdio.h>
#include <stdlib.h>

#define Status          int //״̬
#define OVERFLOW        -1  //���
#define OK              1   //��ȷ
#define ERROR           0   //����


//----- ���Ա�Ķ�̬����˳��洢�ṹ -----
#define LIST_INIT_SIZE  100 //���Ա�洢�ռ�ĳ�ʼ������
#define LISTINCREMENT   10  //���Ա�洢�ռ�ķ�������

#define ElemType int        //ElemType����Ϊint����
typedef struct
{
	ElemType * elem;    //�洢�ռ��ַ
	int length;         //��ǰ����
	int listsize;       //��ǰ����Ĵ洢������С��listsize * sizeof(ElemType)�ֽ�
}SqList;

//�㷨2.3
Status InitList_Sq(SqList &L){
    // ����һ���յ����Ա�
	L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if(!L.elem)
		exit(OVERFLOW);         //�洢����ʧ��
	L.length = 0;               //�ձ���Ϊ0
	L.listsize = LIST_INIT_SIZE;//��ʼ�洢����
	return OK;
}//InitList_Sq

//�㷨2.4
Status ListInsert_Sq(SqList &L, int i,ElemType e){
    //��˳�����Ա�L�е�i��λ��֮ǰ�����µ�Ԫ��e��
    //i�ĺϷ�ֵΪ [1, ListLength_Sq(L)+1]
	ElemType *p, *q, *newbase;
	if(i < 1 || i > L.length + 1)   //iֵ�Ϸ���
	{
		printf("i���Ϸ������ܲ��룡\n");
		return ERROR;
	}
	if(L.length >= L.listsize)      //�ж��Ƿ�Ҫ׷�ӿռ�
	{
		newbase = (ElemType *)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
		if(!newbase)                //�洢����ʧ��
			exit(OVERFLOW);         	//return ERROR;������
		L.elem = newbase;           //��ȡ�»�ַ
		L.listsize += LISTINCREMENT;//���Ӵ洢����
	}
	q = &L.elem[i-1];
	for(p = &(L.elem[L.length-1]); p >= q; --p)
		*(p+1) = *p;    //����λ�ü�֮��Ԫ�غ���1λ
	*q = e;             //����e
	++L.length;         //����1
	return OK;
}

//�㷨2.5
Status ListDelete_Sq(SqList &L,int i,ElemType &e){
    //��˳�����Ա�L��ɾ����i��Ԫ�أ�����e������ֵ
    //i�ĺϷ�ֵΪ��[1, ListLength_Sq(L)]
	ElemType *p, *q;
	if(i < 1 || i > L.length)           //iֵ�Ϸ���
	{
		printf("ɾ��λ������!\n");
		return ERROR;
	}
	p = &(L.elem[i-1]);         //Ҫɾ����Ԫ��λ��
    e = *p;
    q = L.elem + L.length - 1;  //���1��Ԫ�ص�λ�� q = &(L.elem[L.length-1]);
    for (++p; p <= q; ++p)      //��ɾ��Ԫ��֮��Ԫ��ǰ��1λ
        *(p-1) = *p;
	--L.length;
	return OK;
}


int ListLength_Sq(SqList L)
{
    return L.length;
}

//����
Status equal(ElemType e1,ElemType e2)
{
    if(e1 == e2)
        return OK;
    else
        return ERROR;
}
//С��
Status lessthan(ElemType e1,ElemType e2)
{
    if(e1 < e2)
        return OK;
    else
        return ERROR;
}
//С�ڵ���
Status lessequal(ElemType e1,ElemType e2)
{
    if(e1 <= e2)
        return OK;
    else
        return ERROR;
}

Status GetElem(SqList L,int i,ElemType &e)
{
    if(i < 1 || i > L.length)
        return ERROR;
    e = L.elem[i-1];
    return OK;
}

//�㷨2.6.0
int LocateElem_Sq(SqList L,ElemType e,Status (*compare)(ElemType ,ElemType )){
    //��˳�����Ա�L���ҵ���1����e����compare()��Ԫ��λ��
    //���ҵ����򷵻�����L�е�λ�򣬷��򷵻�0
	int i = 1;                  //i�ĳ�ֵΪ��1��Ԫ�ص�λ��
    ElemType *p = L.elem;       //p�ĳ�ֵΪ��1��Ԫ�صĴ洢λ��
    while (i <= L.length && !(*compare)(*p++, e))
        ++i;
    if(i <= L.length)
        return i;
    else
        return 0;
}

//�㷨2.6.1
int LocateElem_Sq1(SqList L,ElemType e,Status (*compare)(ElemType ,ElemType )){
    //��˳�����Ա�L���ҵ���1����e����compare()��Ԫ��λ��
    //���ҵ����򷵻�����L�е�λ�򣬷��򷵻�0
	int i;
    ElemType e1;
	for(i = 1;i <= L.length;i++)
	{
		GetElem(L, i, e1);
        if(compare(e1, e))
			return i;
	}
	return 0;
}



void visit(ElemType e)
{
	printf("%d ",e);
}

void TraverseList(SqList La, void (*pvist)(ElemType ))
{
	int i;
    ElemType e;
	for(i = 1; i <= La.length; ++i)
	{
        GetElem(La, i, e);
		pvist(e);
	}
	printf("\n");
}



////����LocateElem
int main(void)
{
	SqList La;
    int i, pos;
	ElemType data[9] = {1 ,2 ,2 ,3 ,4 ,5 ,6 ,7 , 10}; 
	InitList_Sq(La);
	for (i = 1; i <= 9; i++)
		ListInsert_Sq(La,i,data[i-1]);
    TraverseList(La, visit);
    
    if(pos = LocateElem_Sq(La, 2, equal))
        printf("La����Ԫ��7,��һ����7��Ԫ���ǵ�%d��Ԫ�ء�\n", pos);
    else
        printf("La����Ԫ��7\n");

	return 0;
}