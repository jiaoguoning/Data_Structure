#include <stdio.h>
#include <stdlib.h>
#define Status          int
#define OK              1
#define ERROR           0
#define OVERFLOW        -2
#define STACK_INIT_SIZE 20
#define STACKINCREMENT  5
#define SElemType       char

typedef struct {
    SElemType *base;    // 在构造之前和销毁之后，base的值为NULL
    SElemType *top;     // 栈顶指针
    int stacksize;      // 当前已分配存储空间，以元素为单位
}SqStack;

//因为要修改栈S内存中数据成员的值，因此必须传递S的地址
Status InitStack(SqStack *S)
{
    (*S).base = (SElemType*)malloc(sizeof(SElemType) * STACK_INIT_SIZE);
    if (!(*S).base)
    {
        printf("初始化失败！\n");
        exit(OVERFLOW);     // return ERROR;
    }
    (*S).top = (*S).base;
    (*S).stacksize = STACK_INIT_SIZE;
    return OK;
}

Status GetTop(SqStack S,SElemType *e){
    //若栈不空，则用e返回S的栈顶元素，并返回OK；否则返回ERROR
    if(S.base == S.top)
        return ERROR;
    *e = *(S.top - 1);
    return OK;
}

Status Push(SqStack *S,SElemType e){
    //插入元素e为新的栈顶元素 
    if (((*S).top - (*S).base) >= (*S).stacksize)    // 栈满
    {
        (*S).base = (SElemType *)realloc((*S).base,(*S).stacksize+STACKINCREMENT);
        if (!(*S).base)
        {
            printf("追加失败!\n");
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
        printf("出栈失败，栈为空!\n");
        return ERROR;
    }
    *e = *--(*S).top;
    return OK;
}

void ClearStack(SqStack *S)
{
    S->top = S->base;
}

void DestroyStack(SqStack *S)
{
    free(S->base);
    S->base = NULL;
    S->top = NULL;
    S->stacksize = 0;
}



void PrintStack(SqStack S)
{
    SElemType *p = S.base;
    while(p < S.top)
    {
        printf("%c",(*(p)));
        ++p;
    }
    printf("\n");
}

//算法3.2 行编辑程序
void LineEdit(SqStack *S) {  
    //利用字符栈S，从终端接收一行并传送至调用过程的数据区。
    char ch;
    InitStack(S);       //构造空栈S
    ch = getchar();     //从终端接收第一个字符
    while (ch != EOF) { //EOF为全文结束符  控制台输入ctrl + z
        while (ch != EOF && ch != '\n') {
            switch (ch) {
            case '#': 
                if(S->base != S->top)
                    Pop(S, &ch);    break;  // 仅当栈非空时退栈
            case '@': ClearStack(S); break;  // 重置S为空栈
            default : Push(S, ch);   break;  // 有效字符进栈,未考虑栈满情形
            }
            ch = getchar();  // 从终端接收下一个字符
        }	
        PrintStack(*S);     // 将从栈底到栈顶的栈内字符传送至调用过程的数据区；
        ClearStack(S);      // 重置S为空栈
        if (ch != EOF)  
            ch = getchar();
    }
    DestroyStack(S);
}


//测试： 
//whli##ilr#e(s#*s)
//    outcha@putchar(*s=#++);

int main(void)
{
    SqStack s;
    
    LineEdit(&s);

    
    return 0;
}





