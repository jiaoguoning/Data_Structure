#include <stdio.h>
#include <stdlib.h>
#define Status          int
#define OK              1
#define ERROR           0
#define OVERFLOW        -2
#define STACK_INIT_SIZE 20
#define SElemType       int

typedef struct {
    SElemType base[STACK_INIT_SIZE];    // 初始化大小已定不可扩充
    int top;                            // 栈顶指针
}SqStack;

//因为要修改栈S内存中数据成员的值，因此必须传递S的地址
Status InitStack(SqStack &S)
{
    S.top = 0;
    return OK;
}

Status GetTop(SqStack S,SElemType &e){
    //若栈不空，则用e返回S的栈顶元素，并返回OK；否则返回ERROR
    if(S.top == 0)
        return ERROR;
    e = S.base[S.top-1];
    return OK;
}

Status Push(SqStack &S,SElemType e){
    //插入元素e为新的栈顶元素 
    if (S.top + 1  >= STACK_INIT_SIZE)    // 栈满
    {
        printf("空间已满，不可插入!\n");
        return ERROR;   //exit(OVERFLOW);     
    }
    S.base[S.top++] = e;
    return OK;
}

Status Pop(SqStack &S,SElemType &e)
{
    if (S.top == 0)
    {
        printf("出栈失败，栈为空!\n");
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
    printf("栈顶为：%d\n",e);
    for (i = 1; i <= 6; i++)
    {
        stats = Pop(s,e);
        if (stats)
            printf("e = %d\n",e);
    }

    return 0;
}



