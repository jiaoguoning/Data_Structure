#include <stdio.h>
#include <stdlib.h>
#define STACK_INIT_SIZE 20
#define STACKINCREMENT 5
#define ElemType char



typedef struct {
	ElemType *base;
	ElemType *top;
	int stacksize;
}SqStack;

//因为要修改栈S内存中数据成员的值，因此必须传递S的地址
int InitStack(SqStack *S)
{
	S->base = (ElemType*)malloc(sizeof(ElemType) * STACK_INIT_SIZE);
	if (!S->base)
	{
		printf("初始化失败！\n");
		return 0;
	}
	S->top = S->base;
	S->stacksize = STACK_INIT_SIZE;
	return 1;
}

int push(SqStack *S,ElemType e)
{
	if ((S->top - S->base) >= S->stacksize)
	{
		S->base = (ElemType *)realloc(S->base,S->stacksize+STACKINCREMENT);
		if (!S->base)
		{
			printf("追加失败!\n");
			return 0;
		}
		S->top = S->base + S->stacksize;
		S->stacksize += STACKINCREMENT;
	}
	*S->top++ = e;
	return 1;
}

int pop(SqStack *S,ElemType *e)
{
	if (S->top == S->base)
	{
		printf("出栈失败，栈为空!\n");
		return 0;
	}
	*e = *--S->top;
	return 1;
}
//括号匹配
int matchBracket(SqStack *S,ElemType *str)
{
	int i = 0;
	ElemType e = NULL;
	ElemType *p;
	InitStack(S);
	while (str[i])
	{
		if (str[i] == '(' || str[i] == '[' || str[i] == '{')
			push(S,str[i]);
		else
		{
			if (S->base == S->top)
			{
				printf("匹配错误，第一个为右括号！\n");
				return 0;
			}
			if(*(S->top-1) + 1 == str[i] || *(S->top-1) + 2 == str[i])
			{
				pop(S,&e);
				printf("%c\n",e);
			}else
			{
				printf("匹配错误，最后左括号没遇到与之对应的右括号！\n");
				return 0;
			}
		}
		i++;
	}
	if (S->base == S->top)
	{
		printf("括号匹配成功！\n");
		return 1;
	}
	else
	{
		printf("左括号太多，匹配失败！\n");
		return 0;
	}
}

//行编辑程序
void lineEditing(SqStack *S,ElemType *str)
{
	int i = 0;
	ElemType e;
	InitStack(S);
	while (str[i])
	{
		if (str[i] == '#')
		{
			if (S->top != S->base)
			{
				pop(S,&e);
			}
		}
		else if(str[i] == '@')
			S->top = S->base;
		else
			push(S,str[i]);
		i++;
	}
	push(S,'\0');
}


int main(void)
{
	SqStack s;
	ElemType e;
	char str[40] = "whil##ilr#e(s#*s)";
	lineEditing(&s,str);
	printf("%s\n",s.base);

	return 0;
}



