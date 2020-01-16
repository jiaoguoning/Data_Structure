#include <stdio.h>
#include <stdlib.h>
#define STACK_INIT_SIZE 20
#define STACKINCREMENT 5
#define ElemType char

const ElemType OP[8] = "+-*/()#";
const char priority[][7] =					//���������ȼ���ϵ
{
	{ '>','>','<','<','<','>','>' },
	{ '>','>','<','<','<','>','>' },
	{ '>','>','>','>','<','>','>' },
	{ '>','>','>','>','<','>','>' },
	{ '<','<','<','<','<','=','0' },
	{ '>','>','>','>','0','>','>' },
	{ '<','<','<','<','<','0','=' },
};
typedef struct {
	ElemType *base;
	ElemType *top;
	int stacksize;
}SqStack;


//��ΪҪ�޸�ջS�ڴ������ݳ�Ա��ֵ����˱��봫��S�ĵ�ַ
int InitStack(SqStack *S)
{
	S->base = (ElemType*)malloc(sizeof(ElemType) * STACK_INIT_SIZE);
	if (!S->base)
	{
		printf("��ʼ��ʧ�ܣ�\n");
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
			printf("׷��ʧ��!\n");
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
		printf("��ջʧ�ܣ�ջΪ��!\n");
		return 0;
	}
	*e = *--S->top;
	return 1;
}

int IsOpt(ElemType e)
{
	int i = 0;
	while (OP[i])
	{
		if (e == OP[i])		return 1;
		i++;
	}
	return 0;
}

int getIndex(char c)
{
	int i = 0;
	while (OP[i])
	{
		if (c == OP[i])
			return i;
		i++;
	}
	printf("����ʧ�ܣ�\n");
	return -1;
}

char Operate(char a,char theta,char b)
{
	char result = 0;
	switch (getIndex(theta))
	{
	case 0:
		result = (a -'0') + (b -'0');
		break;
	case 1:
		result = (a -'0') - (b -'0');
		break;
	case 2:
		result = (a -'0') * (b -'0');
		break;
	case 3:
		result = (a -'0') / (b -'0');
		break;
	}

	return result += '0';
}

char Precede(char theta1, char theta2)		//��ȡtheta1��theta2֮������ȼ�
{
	int index1 = getIndex(theta1);
	int index2 = getIndex(theta2);
	return priority[index1][index2];
}
//֧������   3*(7-5)#      ��Ϊ������ݵ�ջ����������Ϊchar   ֻ�ܴ��һλ�����ַ�������м������ܳ�����λ��
//��ѧ��������  ����������ͬ���͵�ջ   һ���Ǵ���ַ� ֻ��ŷ���  һ���Ǵ������   ��������ѧ
char EvaluateExpression()
	//�������ʽ��ֵ������������㷨����OPTR��OPND�ֱ�Ϊ�����ջ��������ջ��
	//OPΪ��������ϡ�
{
	SqStack OPTR;	//�����ջ
	SqStack OPND;	//������ջ
	int i;
	char c,e,theta,a,b;
	InitStack(&OPTR);
	InitStack(&OPND);
	push(&OPTR,'#');
	c = getchar();
	while (c != '#' || *(OPTR.top-1) != '#')
	{
		if(!IsOpt(c))
		{
			push(&OPND,c);
			c = getchar();
		}
		else
		{
			switch (Precede(*(OPTR.top-1),c))
			{
			case '<':
				push(&OPTR,c);
				c = getchar();
				break;
			case '=':
				pop(&OPTR,&e);
				c = getchar();
				break;
			case '>':
				pop(&OPTR,&theta);
				pop(&OPND,&b);
				pop(&OPND,&a);
				push(&OPND,Operate(a,theta,b));
				break;
			}

		}
	}
	return *(OPND.top-1);
}


int main(void)
{
	char r;
	printf("��������ʽ����#�Ž���: ");
	//3*(7-5)#  
	r = EvaluateExpression();
	printf("\n�ñ��ʽ�Ľ��Ϊ��");
	printf("%c\n",r);

	return 0;
}



