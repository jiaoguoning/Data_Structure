#include <stdio.h>
#include <stdlib.h>
#define Status          int
#define OK              1
#define ERROR           0
#define OVERFLOW        -2
#define STACK_INIT_SIZE 20
#define SElemType       int

typedef struct {
    SElemType base[STACK_INIT_SIZE];    // ��ʼ����С�Ѷ���������
    int top;                            // ջ��ָ��
}SqStack;

//��ΪҪ�޸�ջS�ڴ������ݳ�Ա��ֵ����˱��봫��S�ĵ�ַ
Status InitStack(SqStack &S)
{
    S.top = 0;
    return OK;
}

Status GetTop(SqStack S,SElemType &e){
    //��ջ���գ�����e����S��ջ��Ԫ�أ�������OK�����򷵻�ERROR
    if(S.top == 0)
        return ERROR;
    e = S.base[S.top-1];
    return OK;
}

Status Push(SqStack &S,SElemType e){
    //����Ԫ��eΪ�µ�ջ��Ԫ�� 
    if (S.top + 1  >= STACK_INIT_SIZE)    // ջ��
    {
        printf("�ռ����������ɲ���!\n");
        return ERROR;   //exit(OVERFLOW);     
    }
    S.base[S.top++] = e;
    return OK;
}

Status Pop(SqStack &S,SElemType &e)
{
    if (S.top == 0)
    {
        printf("��ջʧ�ܣ�ջΪ��!\n");
        return ERROR;
    }
    e = S.base[--S.top];
    return OK;
}



void PrintStack(SqStack S)
{
    SElemType *p = S.base;
    while(p < S.base + S.top)
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
    GetTop(s, e);
    printf("ջ��Ϊ��%d\n",e);
    for (i = 1; i <= 6; i++)
    {
        stats = Pop(s,e);
        if (stats)
            printf("e = %d\n",e);
    }

    return 0;
}



