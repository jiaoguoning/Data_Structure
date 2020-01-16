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

//�㷨2.3.0
Status InitList_Sq(SqList &L){
    // ����һ���յ����Ա�
	L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if(!L.elem)
		exit(OVERFLOW);         //�洢����ʧ��
	L.length = 0;               //�ձ���Ϊ0
	L.listsize = LIST_INIT_SIZE;//��ʼ�洢����
	return OK;
}//InitList_Sq

//�㷨2.4.0
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
			exit(OVERFLOW);         //return ERROR;
		L.elem = newbase;           //��ȡ�»�ַ
		L.listsize += LISTINCREMENT;//���Ӵ洢����
	}
	q = &L.elem[i-1];   //�����λ��
	for(p = &(L.elem[L.length-1]); p >= q; --p)
		*(p+1) = *p;    //����λ�ü�֮��Ԫ�غ���1λ
	*q = e;             //����e
	++L.length;          
	return OK;
}

//�㷨2.5.0
Status ListDelete_Sq(SqList &L,int i,ElemType &e){
	ElemType *p, *q;
	if(i < 1 || i > L.length)           
	{
		printf("ɾ��λ������!\n");
		return ERROR;
	}
	p = &(L.elem[i-1]);         
    e = *p;
    q = L.elem + L.length - 1;  
    for (++p; p <= q; ++p)      
        *(p-1) = *p;
	--L.length;
	return OK;
}

//�㷨2.5.1
Status ListDelete_Sq1(SqList &L,int i,ElemType &e){
    //��˳�����Ա�L��ɾ����i��Ԫ�أ�����e������ֵ
    //i�ĺϷ�ֵΪ��[1, ListLength_Sq(L)]
	ElemType *p, *q;
	if(i < 1 || i > L.length)            
	{
		printf("ɾ��λ������!\n");
		return ERROR;
	}
    p = L.elem + i - 1;
    e = *p;
	q = &(L.elem[L.length - 1]);  
    for (; p < q; ++p)      
        *p = *(p+1);

	--L.length;
	return OK;
}


//�㷨2.5.2
Status ListDelete_Sq2(SqList &L,int i,ElemType &e){
    //��˳�����Ա�L��ɾ����i��Ԫ�أ�����e������ֵ
    //i�ĺϷ�ֵΪ��[1, ListLength_Sq(L)]
	int k = 0;
	if(i < 1 || i > L.length)            
	{
		printf("ɾ��λ������!\n");
		return ERROR;
	}
	e = L.elem[i-1];
    //ʱ�̼�ס��i��Ԫ�ض�Ӧ�±���i-1
	for(k = i; k <= L.length-1; ++k)
		L.elem[k-1] = L.elem[k];
	
	--L.length;
	return OK;
}


//�㷨2.5.3
Status ListDelete_Sq3(SqList &L,int i,ElemType &e){
    //��˳�����Ա�L��ɾ����i��Ԫ�أ�����e������ֵ
    //i�ĺϷ�ֵΪ��[1, ListLength_Sq(L)]
	int k = 0;
	if(i < 1 || i > L.length)            
	{
		printf("ɾ��λ������!\n");
		return ERROR;
	}
	e = L.elem[i-1];
	for(k = i-1; k <= L.length-2; ++k)
		L.elem[k] = L.elem[k+1];
	
	--L.length;
	return OK;
}

Status GetElem(SqList L,int i,ElemType &e)
{
    if(i < 1 || i > L.length)
        return ERROR;
    e = L.elem[i-1];
    return OK;
}

void visit(ElemType e)
{
	printf("%4d ",e);
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

// ����Delete
int main(void)
{
	SqList La, Lb;
	int i;
	ElemType e;
	ElemType data[9] = {11,-22,-33,3,-88,21,77,0,-9}; 
   
	InitList_Sq(La);
    
	for (i = 1; i <= 9; i++)
		ListInsert_Sq(La,i,data[i-1]);
    TraverseList(La, visit);

    ListDelete_Sq3(La, 1, e);
    TraverseList(La, visit);
   
	return 0;
}


