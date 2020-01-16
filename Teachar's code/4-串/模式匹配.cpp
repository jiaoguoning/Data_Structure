#include <stdio.h>
#include <Windows.h>
#define MAXSTRLEN 255
#define Status int
#define OK 1
#define ERROR 0

typedef unsigned char SString[MAXSTRLEN + 1];

Status StrAssign(SString &T, char * chars)
{
	int i = 1, uncut = 1;
	char *p = chars;
	while (*p)
	{
		if(i > MAXSTRLEN)
		{
			uncut = 0;
			break;
		}
		T[i] = *p++;
		++i;
	}
	T[0] = i-1;
	return uncut;
}


Status Concat(SString &T,SString S1,SString S2)
{
	int i, uncut;
	if(S1[0] + S2[0] <= MAXSTRLEN)
	{
		for(i = 1; i <= S1[0]; ++i)
			T[i] = S1[i];
		for(i = S1[0] + 1; i <= S1[0] + S2[0]; ++i)
			T[i] = S2[i - S1[0]];
		T[0] = S1[0] + S2[0];
		uncut = 1;
	}else if(S1[0] < MAXSTRLEN)
	{
		for(i = 1; i <= S1[0]; ++i)
			T[i] = S1[i];
		for(i = S1[0] + 1; i <= MAXSTRLEN; ++i)
			T[i] = S2[i - S1[0]];
		T[0] = MAXSTRLEN;
		uncut = 0;
	}else
	{
		for(i = 0; i <= S1[0]; ++i)
			T[i] = S1[i];
		uncut = 0;
	}

	return uncut;
}

Status SubString(SString &Sub,SString S,int pos,int len) 
{
	int i;
	if(pos < 1 || pos > S[0] || len < 0 || len > S[0]-pos+1)
		return 0;
	for(i = pos; i <= pos + len; ++i)
		Sub[i - pos + 1] = S[i];
	Sub[0] = len;

	return OK;
}

int Index(SString S, SString T, int pos)
{
	int i = pos, j = 1;
	while (i <= S[0] && j <= T[0])
	{
		if(S[i] == T[j])
		{
			++i;
			++j;
		}else{
			i = i - j + 2;
			j = 1;
		}
	}
	if(j > T[0])
		return i - T[0];
	else
		return 0;
}
int next[7];	//0号元素不用
void PrintNext(SString T, int Ti,int Tj);
void get_next(SString T)
{
	int i = 1 , j = 0;
	next[1] = 0;
	PrintNext(T, i, j);
	while (i < T[0])
	{
		if(j == 0|| T[i] == T[j])
		{
			++i; ++j; next[i] = j;
			PrintNext(T, i, j);
		}
		else
		{
			j = next[j];
			PrintNext(T, i, j);
		}
	}
	PrintNext(T, i, j);
}
int nextval[7];	//0号元素不用
void PrintNextval(SString T, int Ti,int Tj)
{
	int i;
	system("cls");
	for (i = 1; i <= 6; i++)
	{
		if(i == Ti)
			printf("i| ");
		else
			printf("   ");
	}
	printf("\n");
	for (i = 1; i <= 6; i++)
		printf(" %d ", i);
	printf("\n");
	for (i = 1; i <= T[0]; i++)
		printf(" %c ", T[i]);
	printf("\n");
	for (i = 1; i <= T[0]; i++)
		printf(" %d ", nextval[i]);
	printf("\n");
	for (i = 1; i <= 6; i++)
	{
		if(i == Tj)
			printf("j| ");
		else
			printf("   ");
	}
	printf("\n");
	system("pause");

}

void get_nextval(SString T)
{
	int i = 1, j = 0;	nextval[1] = 0;
	PrintNextval(T, i, j);
	while (i < T[0])
	{
		if(j == 0 || T[i] == T[j])
		{
			++i; ++j;
			if (T[i] != T[j])
			{
				nextval[i] = j;
				PrintNextval(T, i, j);
			}
			else
			{
				nextval[i] = nextval[j];
				PrintNextval(T, i, j);
			}
		}else j = nextval[j];
	}
}

void PrintNext(SString T, int Ti,int Tj)
{
	int i;
	system("cls");
	for (i = 1; i <= 6; i++)
	{
		if(i == Ti)
			printf("i| ");
		else
			printf("   ");
	}
	printf("\n");
	for (i = 1; i <= 6; i++)
		printf(" %d ", i);
	printf("\n");
	for (i = 1; i <= T[0]; i++)
		printf(" %c ", T[i]);
	printf("\n");
	for (i = 1; i <= T[0]; i++)
		printf(" %d ", next[i]);
	printf("\n");
	for (i = 1; i <= 6; i++)
	{
		if(i == Tj)
			printf("j| ");
		else
			printf("   ");
	}
	printf("\n");
	system("pause");

}

void PrintStr(SString S)
{
	int i;
	for(i = 1; i <= S[0]; ++i)
		printf("%c",S[i]);
	printf("\n");
}

int main(void)
{
	SString S ,T;
	StrAssign(S,"abaabc");
	get_next(S);
	return 0;
}



