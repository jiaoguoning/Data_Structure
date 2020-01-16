#include <stdio.h>
#include <stdlib.h>
#define Status          int
#define OK              1
#define ERROR           0
#define OVERFLOW        -2
#define STACK_INIT_SIZE 20
#define STACKINCREMENT  5
#define SElemType       int

typedef struct {
    SElemType *base;    // �ڹ���֮ǰ������֮��base��ֵΪNULL
    SElemType *top;     // ջ��ָ��
    int stacksize;      // ��ǰ�ѷ���洢�ռ䣬��Ԫ��Ϊ��λ
}SqStack;

//��ΪҪ�޸�ջS�ڴ������ݳ�Ա��ֵ����˱��봫��S�ĵ�ַ
Status InitStack(SqStack *S)
{
    (*S).base = (SElemType*)malloc(sizeof(SElemType) * STACK_INIT_SIZE);
    if (!(*S).base)
    {
        printf("��ʼ��ʧ�ܣ�\n");
        exit(OVERFLOW);     // return ERROR;
    }
    (*S).top = (*S).base;
    (*S).stacksize = STACK_INIT_SIZE;
    return OK;
}

Status GetTop(SqStack S,SElemType *e){
    //��ջ���գ�����e����S��ջ��Ԫ�أ�������OK�����򷵻�ERROR
    if(S.base == S.top)
        return ERROR;
    *e = *(S.top - 1);
    return OK;
}

Status Push(SqStack *S,SElemType e){
    //����Ԫ��eΪ�µ�ջ��Ԫ�� 
    if (((*S).top - (*S).base) >= (*S).stacksize)    // ջ��
    {
        (*S).base = (SElemType *)realloc((*S).base,(*S).stacksize+STACKINCREMENT);
        if (!(*S).base)
        {
            printf("׷��ʧ��!\n");
            exit(OVERFLOW);     // return ERROR;
        }
        (*S).top = (*S).base + (*S).stacksize;
        (*S).stacksize += STACKINCREMENT;
    }
    *(*S).top++ = e;
    return OK;
}

Status Pop(SqStack *S,SElemType *e)
{
    if ((*S).top == (*S).base)
    {
        printf("��ջʧ�ܣ�ջΪ��!\n");
        return ERROR;
    }
    *e = *--(*S).top;
    return OK;
}



void PrintStack(SqStack S)
{
    SElemType *p = S.base;
    while(p < S.top)
    {
        printf("%d ",(*(p)));
        ++p;
    }
    printf("\n");
}


Status converting(SqStack *S,int N)
{
	while (N)
	{
		if(!Push(S,N % 8))
			return 0;
		N /= 8;
	}
	return 1;
}


Status converting1(SqStack *S,int N)
{
	int e;
	InitStack(S);
	while (N)
	{
		if(!Push(S,N % 8))
			return 0;
		N /= 8;
	}

	while((*S).base != (*S).top)
	{
		Pop(S,&e);
		printf("%d ",e);
	}
	printf("\n");
	return OK;
}


int main(void)
{
    SqStack s;
	int N = 1348, i, e;
	InitStack(&s);
	converting(&s,N);
	while(s.base != s.top)
	{
		Pop(&s,&e);
		printf("%d ",e);
	}
	printf("\n");

    return 0;
}



