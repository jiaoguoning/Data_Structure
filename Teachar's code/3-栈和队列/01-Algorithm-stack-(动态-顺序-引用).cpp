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
    SElemType *base;    // 在构造之前和销毁之后，base的值为NULL
    SElemType *top;     // 栈顶指针
    int stacksize;      // 当前已分配存储空间，以元素为单位
}SqStack;

//因为要修改栈S内存中数据成员的值，因此必须传递S的地址
Status InitStack(SqStack &S)
{
    S.base = (SElemType*)malloc(sizeof(SElemType) * STACK_INIT_SIZE);
    if (!S.base)
    {
        printf("初始化失败！\n");
        exit(OVERFLOW);     // return ERROR;
    }
    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
    return OK;
}

Status GetTop(SqStack S,SElemType &e){
    //若栈不空，则用e返回S的栈顶元素，并返回OK；否则返回ERROR
    if(S.base == S.top)
        return ERROR;
    e = *(S.top - 1);
    return OK;
}

Status Push(SqStack &S,SElemType e){
    //插入元素e为新的栈顶元素 
    if ((S.top - S.base) >= S.stacksize)    // 栈满
    {
        S.base = (SElemType *)realloc(S.base,S.stacksize+STACKINCREMENT);
        if (!S.base)
        {
            printf("追加失败!\n");
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
        printf("出栈失败，栈为空!\n");
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



