#include <stdio.h>
#include <stdlib.h>
//���Ķѷ���洢��ʾ
typedef struct {
	char *ch;	//���Ƿǿմ����򰴴�������洢��������chΪNULL
	int length;	//������
}HString;

int StrInsert(HString *S,int pos,HString T)
{
	//1 �� pos �� StrLength(S) + 1���ڴ�S�ĵ�pos���ַ�֮ǰ���봮T��
	//��1���ַ����±���0��
	int i;
	if(pos < 1 || pos > (*S).length + 1)
		return 0;
	if (T.length)
	{
		if(!((*S).ch = (char*)realloc(S->ch,(S->length + T.length) * sizeof(char))))
		{
			printf("ERROR!\n");
			exit(1);
		}
		//ע��������ƶ�������һ��Ҫ���ƶ����һ�����������ƶ���pos��
		//��Ϊ���ƶ���pos���Ḳ��ԭ���ַ��Ժ����ƶ�����Ӱ��
		for(i = S->length-1;i >= pos-1 ;--i)
			S->ch[i + T.length] = S->ch[i];
		for (i = pos-1; i < pos-1 + T.length; i++)
			S->ch[i] = T.ch[i - pos + 1];
		S->length += T.length;
	}
	return 1;
}

int StrAssign(HString *T,char *chars)
{
	//����һ����ֵ���ڴ�����chars�Ĵ�T
	int i,j;
	char *c;
	if(T->ch)
		free(T->ch);
	for (i = 0,c = chars; *c; ++i,++c)
		;
	if(!i)
	{
		T->ch = NULL;
		T->length = 0;
	}
	else
	{
		if(!(T->ch = (char*)malloc(i * sizeof(char))))
		{
			printf("ERROR!\n");
			exit(1);
		}
		for (j = 0; j < i; ++j)
			T->ch[j] = chars[j];
		T->length = i;
	}
	return 1;
}

int StrLength(HString S)
	//����S��Ԫ�ظ�������Ϊ���ĳ���
{
	return S.length;
}

int StrCompare(HString S,HString T)
	//��S>T���򷵻�ֵ>0����S=T���򷵻�ֵ=0����S<T���򷵻�ֵ<0
{
	int i;
	for (i = 0; i < S.length && i < T.length; ++i)
		if(S.ch[i] != T.ch[i])
			return S.ch[i] - T.ch[i];

	return S.length - T.length;
}

int ClearString(HString *S)
	//��S���
{
	if (S->ch)
	{
		free(S->ch);
		S->ch = NULL;
	}
	S->length = 0;
	return 1;
}

int Concat(HString *T,HString S1,HString S2)
	//��T������S1��S2���Ӷ��ɵ��´���
{
	int i;
	if (T->ch)
		free(T->ch);
	if(!(T->ch = (char *)malloc((S1.length + S2.length) * sizeof(char))))
	{
		printf("ERROR!\n");
		exit(1);
	}
	for (i = 0; i < S1.length; i++)
		T->ch[i] = S1.ch[i];
	T->length = (S1.length + S2.length);
	for (; i < T->length; i++)
		T->ch[i] = S2.ch[i - S1.length];
	
	return 1;
}

int SubString(HString *Sub,HString S,int pos,int len)
	//��Sub���ش�S�ĵ�pos���ַ��𳤶�Ϊlen���Ӵ���
	//���У�1��pos��StrLength(S)��0��len��StrLength(S)-pos+1
	//��1���ַ����±�Ϊ0
{
	int i;
	if(pos < 1 || pos > S.length || len < 0 || len > S.length - pos + 1)
		return 0;
	if(Sub->ch)
		free(Sub->ch);
	if(!len)
	{
		Sub->ch = NULL;
		Sub->length = 0;
	}
	else
	{
		if(!(Sub->ch = (char *)malloc(len * sizeof(char))))
		{
			printf("ERROR!\n");
			exit(1);
		}
		for (i = 0; i < len; i++)
			Sub->ch[i] = S.ch[pos + i - 1];	//����
		Sub->length = len;
	}
	return 1;
}

void PrintStr(HString S)
{
	int i;
	for ( i = 0; i < S.length; i++)
		printf("%c",S.ch[i]);
	printf("\n");
}

int main(void)
{
	int i;
	HString s1,s2,T;
	char *chars = "123";
	s1.ch = (char *)malloc(10 * sizeof(char));
	s1.length = 10;
	for (i = 0; i < s1.length; i++)
		s1.ch[i] = 'a'+i;
	PrintStr(s1);
	s2.ch = (char *)malloc(10 * sizeof(char));
	s2.length = 10;
	for (i = 0; i < s2.length; i++)
		s2.ch[i] = 'A'+i;
	T.ch = (char *)malloc(3 * sizeof(char));
	T.length = 3;
	T.ch[0] = 'Z';T.ch[1] = 'Z';T.ch[2] = 'Z';
	
	SubString(&T,s1,4,6);
	PrintStr(T);

	




	return 0;
}