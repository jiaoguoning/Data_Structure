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

//�㷨3.2 �б༭����
void LineEdit(SqStack *S) {  
    //�����ַ�ջS�����ն˽���һ�в����������ù��̵���������
    char ch;
    InitStack(S);       //�����ջS
    ch = getchar();     //���ն˽��յ�һ���ַ�
    while (ch != EOF) { //EOFΪȫ�Ľ�����  ����̨����ctrl + z
        while (ch != EOF && ch != '\n') {
            switch (ch) {
            case '#': 
                if(S->base != S->top)
                    Pop(S, &ch);    break;  // ����ջ�ǿ�ʱ��ջ
            case '@': ClearStack(S); break;  // ����SΪ��ջ
            default : Push(S, ch);   break;  // ��Ч�ַ���ջ,δ����ջ������
            }
            ch = getchar();  // ���ն˽�����һ���ַ�
        }	
        PrintStack(*S);     // ����ջ�׵�ջ����ջ���ַ����������ù��̵���������
        ClearStack(S);      // ����SΪ��ջ
        if (ch != EOF)  
            ch = getchar();
    }
    DestroyStack(S);
}


//���ԣ� 
//whli##ilr#e(s#*s)
//    outcha@putchar(*s=#++);

int main(void)
{
    SqStack s;
    
    LineEdit(&s);

    
    return 0;
}





