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
Status InitStack(SqStack &S)
{
    S.base = (SElemType*)malloc(sizeof(SElemType) * STACK_INIT_SIZE);
    if (!S.base)
    {
        printf("��ʼ��ʧ�ܣ�\n");
        exit(OVERFLOW);     // return ERROR;
    }
    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
    return OK;
}

Status GetTop(SqStack S,SElemType &e){
    //��ջ���գ�����e����S��ջ��Ԫ�أ�������OK�����򷵻�ERROR
    if(S.base == S.top)
        return ERROR;
    e = *(S.top - 1);
    return OK;
}

Status Push(SqStack &S,SElemType e){
    //����Ԫ��eΪ�µ�ջ��Ԫ�� 
    if ((S.top - S.base) >= S.stacksize)    // ջ��
    {
        S.base = (SElemType *)realloc(S.base,S.stacksize+STACKINCREMENT);
        if (!S.base)
        {
            printf("׷��ʧ��!\n");
            exit(OVERFLOW);     // return ERROR;
        }
        S.top = S.base + S.stacksize;
        S.stacksize += STACKINCREMENT;
    }
    *S.top++ = e;
    return OK;
}

Status Pop(SqStack &S,SElemType &e)
{
    if (S.top == S.base)
    {
        printf("��ջʧ�ܣ�ջΪ��!\n");
        return ERROR;
    }
    e = *--S.top;
    return OK;
}

void ClearStack(SqStack &S)
{
    S.top = S.base;
}

void DestroyStack(SqStack &S)
{
    free(S.base);
    S.base = NULL;
    S.top = NULL;
    S.stacksize = 0;
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

int main(void)
{
    SqStack s;
    int e,i,stats = 0;
    InitStack(s);
    Push(s,11);
    Push(s,22);
    Push(s,33);
    Push(s,44);
    Push(s,55);

    for (i = 1; i <= 6; i++)
    {
        stats = Pop(s,e);
        if (stats)
            printf("e = %d\n",e);
    }

    return 0;
}



