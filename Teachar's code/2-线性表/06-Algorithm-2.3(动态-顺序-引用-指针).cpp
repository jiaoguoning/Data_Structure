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

//�㷨2.3.1
Status InitList_Sq1(SqList *L){
    // ����һ���յ����Ա�
	(*L).elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if(!(*L).elem)
		exit(OVERFLOW);             //�洢����ʧ��
	(*L).length = 0;                //�ձ���Ϊ0
	(*L).listsize = LIST_INIT_SIZE; //��ʼ�洢����
	return OK;
}//InitList_Sq


//�㷨2.3.2
Status InitList_Sq2(SqList *L){
    // ����һ���յ����Ա�
	L->elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if(!(*L).elem)
		exit(OVERFLOW);         //�洢����ʧ��
	L->length = 0;               //�ձ���Ϊ0
	L->listsize = LIST_INIT_SIZE;//��ʼ�洢����
	return OK;
}//InitList_Sq


// ����InitList
int main(void)
{
	SqList La;
    InitList_Sq(La);
    printf("La.elem     = %p\n",La.elem);
    printf("La.length   = %d\n",La.length);
    printf("La.listsize = %d\n",La.listsize);
	
    

	return 0;
}



