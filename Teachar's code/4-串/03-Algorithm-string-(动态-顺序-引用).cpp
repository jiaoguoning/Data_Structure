#include <stdio.h>
#include <stdlib.h>

#define Status      int
#define OK          1
#define ERROR       0
#define OVERFLOW    -2

//---- 串的堆分配存储表示----  
typedef struct {
	char *ch;	//若是非空串，则按串长分配存储区，否则ch为NULL
	int length;	//串长度
}HString;


// 算法4.4 
Status StrInsert(HString &S,int pos,HString T)
{
	//1 ≤ pos ≤ StrLength(S) + 1。在串S的第pos个字符之前插入串T。
	//第1个字符的下标是0。
	int i;
	if(pos < 1 || pos > S.length + 1)
		return ERROR;
	if (T.length)
	{
		if(!(S.ch = (char*)realloc(S.ch,(S.length + T.length) * sizeof(char))))
		{
			printf("ERROR!\n");
			exit(OVERFLOW);
		}
		//注意这个在移动过程中一定要先移动最后一个，不能先移动第pos个
		//因为先移动第pos个会覆盖原来字符对后面移动产生影响
		for(i = S.length - 1;i >= pos-1 ;--i)
			S.ch[i + T.length] = S.ch[i];
		for (i = pos-1; i < pos-1 + T.length; i++)
			S.ch[i] = T.ch[i - pos + 1];
		S.length += T.length;
	}
	return OK;
}


Status StrAssign(HString &T,char *chars)
{
	//生成一个其值等于串常量chars的串T
	int i,j;
	char *c;
	if(T.ch)
		free(T.ch);
	for (i = 0,c = chars; *c; ++i,++c)   ;   
	if(!i)
	{
		T.ch = NULL;
		T.length = 0;
	}
	else
	{
		if(!(T.ch = (char*)malloc(i * sizeof(char))))
			exit(OVERFLOW);
		for (j = 0; j < i; ++j)
			T.ch[j] = chars[j];
		T.length = i;
	}
	return OK;
}

int StrLength(HString S)
	//返回S的元素个数，称为串的长度
{
	return S.length;
}

int StrCompare(HString S,HString T)
	//若S>T，则返回值>0；若S=T，则返回值=0；若S<T，则返回值<0
{
	int i;
	for (i = 0; i < S.length && i < T.length; ++i)
		if(S.ch[i] != T.ch[i])
			return S.ch[i] - T.ch[i];

	return S.length - T.length;
}

Status Strcopy(HString &T, HString S)
{
    int n, i;
    if(T.ch)
        free(T.ch);
    n = S.length;
    if(n != 0)
    {
        T.ch = (char *)malloc(n * sizeof(char));
        if(!T.ch)
            exit(OVERFLOW);
        for(i = 0; i < n; ++i)
            T.ch[i] = S.ch[i];
        T.length = S.length;
    }
    return OK;
} // Strcopy

Status ClearString(HString &S)
	//将S清空
{
	if(S.ch)
	{
		free(S.ch);
		S.ch = NULL;
	}
	S.length = 0;
	return OK;
}

Status Concat(HString &T,HString S1,HString S2)
	//用T返回由S1和S2联接而成的新串。
{
	int i;
	if (T.ch)
		free(T.ch);
	if(!(T.ch = (char *)malloc((S1.length + S2.length) * sizeof(char))))
		exit(OVERFLOW);
	
	for (i = 0; i < S1.length; i++)
		T.ch[i] = S1.ch[i];
	T.length = (S1.length + S2.length);
	for (; i < T.length; i++)
		T.ch[i] = S2.ch[i - S1.length];
	
	return OK;
}

Status SubString(HString &Sub,HString S,int pos,int len)
	//用Sub返回串S的第pos个字符起长度为len的子串。
	//其中，1≤pos≤StrLength(S)且0≤len≤StrLength(S)-pos+1
	//第1个字符的下标为0
{
	int i;
	if(pos < 1 || pos > S.length || len < 0 || len > S.length - pos + 1)
		return ERROR;
	if(Sub.ch)
		free(Sub.ch);
	if(!len)
	{
		Sub.ch = NULL;
		Sub.length = 0;
	}
	else
	{
		if(!(Sub.ch = (char *)malloc(len * sizeof(char))))
			exit(OVERFLOW);
		
		for (i = 0; i < len; i++)
			Sub.ch[i] = S.ch[pos + i - 1];	//测试
		Sub.length = len;
	}
	return OK;
}

void PrintStr(HString S)
{
	int i;
	for (i = 0; i < S.length; i++)
		printf("%c",S.ch[i]);
	printf("\n");
}

int main(void)
{
	int i;
	HString s1 ,s2 , t, sub;
    sub.ch = s1.ch = s2.ch = t.ch = NULL;

	StrAssign(s1, "123567890");
	PrintStr(s1);

    StrAssign(s2, "ABCDEFGH");
	PrintStr(s2);
	
	StrInsert(s1, 2 ,s2);
    PrintStr(s1);

    SubString(sub, s1, 6, 7);
    PrintStr(sub);

    Concat(t, s1, s2);
    PrintStr(t);



	return 0;
}