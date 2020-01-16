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



Status matchBracket(SqStack *S,SElemType *str)
{
	int i = 0;
	SElemType e = NULL;
	SElemType *p;
	InitStack(S);
	while (str[i])
	{
		if (str[i] == '(' || str[i] == '[' || str[i] == '{')
			Push(S,str[i]);
		else if(str[i] == ')' || str[i] == ']' || str[i] == '}')
		{
			if (S->base == S->top)
			{
				printf("ƥ����������Ŷ࣡\n");
				return ERROR;
			}
			if(*(S->top-1) + 1 == str[i] || *(S->top-1) + 2 == str[i])
			{
				Pop(S,&e);
				printf("%c\n",e);
			}else
			{
				printf("ƥ��������������û������֮��Ӧ�������ţ�\n");
				return ERROR;
			}
		}
		i++;
	}
	if (S->base == S->top)
	{
		printf("����ƥ��ɹ���\n");
		return OK;
	}
	else
	{
		printf("������̫�࣬ƥ��ʧ�ܣ�\n");
		return ERROR;
	}
}


int main(void)
{
	SqStack s;
	SElemType e;
	char str[20] = "{[(q)(a)]}";
    InitStack(&s);
	matchBracket(&s,str);

	return 0;
}





