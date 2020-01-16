#include <stdio.h>
#include <string.h>
//串的定长顺序存储表示
#define MAXSTRLEN 255							//用户可在255以内定义最大串长
typedef unsigned char SString[MAXSTRLEN + 1];	//0号单元存放串的长度

int Concat(SString *T,SString S1,SString S2)
	//用T返回S1和S2联接而成的新串。若未截断返回1，若截断返回0
{
	int i = 1,j,uncut = 0;
	if(S1[0] + S2[0] <= MAXSTRLEN)	//未截断
	{
		for (i = 1; i <= S1[0]; i++)//赋值时等号不可丢
			(*T)[i] = S1[i];
		for (j = 1; j <= S2[0]; j++)
			(*T)[S1[0]+j] = S2[j];	//(*T)[i+j] = S2[j]
		(*T)[0] = S1[0] + S2[0];
		uncut = 1;
	}
	else if(S1[0] < MAXSTRLEN)		//截断
	{
		for (i = 1; i <= S1[0]; i++)//赋值时等号不可丢
			(*T)[i] = S1[i];

		for (j = S1[0] + 1; j <= MAXSTRLEN; j++)
		{
			(*T)[j] = S2[j - S1[0] ];
			(*T)[0] = MAXSTRLEN;
			uncut = 0;
		}
	}
	else
	{
		for (i = 0; i <= MAXSTRLEN; i++)
			(*T)[i] = S1[i];
		/*或者分开赋值，先赋值内容，再赋值长度
		for (i = 1; i <= MAXSTRLEN; i++)
			(*T)[i] = S1[i];
		(*T)[0] = MAXSTRLEN;
		*/
		uncut = 0;
	}

	return uncut;
}

int SubString(SString *Sub,SString S,int pos,int len)
	//用Sub返回串S的第pos个字符起长度为len的子串
	//其中，1 ≤ pos ≤ StrLength(S)且0 ≤ len ≤ StrLength(S) - pos + 1(从pos开始到最后有多少字符)
	//第1个字符的下标为1,因为第0个字符存放字符长度
{
	int i;
	if(pos < 1 || pos > S[0] || len < 0 || len > S[0] - pos + 1)
		return 0;
	for (i = 1; i <= len; i++)
	{
		//S中的[pos,len]的元素 -> *Sub中的[1,len]
		(*Sub)[i] = S[pos + i - 1];//下标运算符 > 寻址运算符的优先级
	}
	(*Sub)[0] = len;
	return 1;
}
void PrintStr(SString S)
{
	int i;
	for (i = 1; i <= S[0]; i++)
		printf("%c",S[i]);
	printf("\n");
}


int main(void)
{
	/*定长顺序存储初始化和打印的方法
	SString s = {4,'a','b','c','d'};
	int i;
	//s = "abc";	//不可直接赋值

	for (i = 1; i <= s[0]; i++)
		printf("%c",s[i]);
	*/
	SString s1 = {4,'a','b','c','d'};
	SString s2 = {4,'e','f','g','h'},s3;
	SString T,Sub;
	int i;
	
	for (i = 1; i <= 255; i++)
	{
		s3[i] = 'a';
		if(i >= 248)
			s3[i] = 'K';
	}
	s3[0] = 255;
	SubString(&Sub,s3,247,8);
	PrintStr(Sub);
	



	return 0;
}