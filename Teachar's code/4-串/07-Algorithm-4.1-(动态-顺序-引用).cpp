#include <stdio.h>
#include <stdlib.h>

#define Status      int
#define OK          1
#define ERROR       0
#define OVERFLOW    -2

//串的定长顺序存储表示
#define MAXSTRLEN       255						//用户可在255以内定义最大串长
typedef unsigned char SString[MAXSTRLEN + 1];	//0号单元存放串的长度

// 串赋值也就是串的初始化
Status StrAssign(SString &T,char * chars)
{    // 生成一个其值等于串常量chars的串T
    char *c = NULL;
    int i, uncut = 0;
    for(i = 1, c = chars; *c && i <= 255; ++i)
        T[i] = *c++;
    T[0] = i-1;
    if(i > 255)
        return ERROR;   // 产生截断
    else
        return OK;
}

// 求长度
int StrLength(SString S)
{
    return S[0];
}

//// 串比较 
int StrCompare(SString S,SString T)
	//若S>T，则返回值>0；若S=T，则返回值=0；若S<T，则返回值<0
{
	int i;
	for (i = 1; i <= S[0] && i <= T[0]; ++i)
		if(S[i] != T[i])
			return S[i] - T[i];

	return S[0] - T[0];
}


// 算法4.3 
Status SubString(SString &Sub,SString S,int pos,int len)
{   //用Sub返回串S的第pos个字符起长度为len的子串
    //其中，1 ≤ pos ≤ StrLength(S)且0 ≤ len ≤ StrLength(S) - pos + 1(从pos开始到最后有多少字符)
    //第1个字符的下标为1,因为第0个字符存放字符长度
    int i;
    if(pos < 1 || pos > S[0] || len < 0 || len > S[0] - pos + 1)
        return ERROR ;
    for (i = 1; i <= len; i++)
    {
        //S中的[pos,len]的元素 -> *Sub中的[1,len]
        Sub[i] = S[pos + i - 1];//下标运算符 > 寻址运算符的优先级
    }
    Sub[0] = len;
    return OK;
}
void PrintStr(SString S)
{
    int i;
    for (i = 1; i <= S[0]; i++)
        printf("%c",S[i]);
    printf("\n");
}

// 算法4.1  
int Index(SString S, SString T,int pos)
{   // T为非空串。若主串S中第pos个字符之后存在与T相等的子串，
    // 则返回第一个这样的子串在S中的位置，否则返回0
    int n, m, i;
    SString sub;
    if(pos > 0){
        n = StrLength(S);   m = StrLength(T);   i = pos;
        while (i <= n-m+1)
        {
            SubString(sub, S, i, m);
            if(StrCompare(sub, T) != 0)
                ++i;
            else
                return i;
        }//while
    }//if

    return 0;
}



//  测试算法4.1 Index
int main(void)
{
    SString S, T;
    int i = 0, pos = 5;
    char *c1 = "abcdefde",*t1 = "de";
   
    StrAssign(S, c1);
    StrAssign(T, t1);
    i = Index(S, T, pos);
    if(i)
        printf("%s中从第%d开始第一次出现的%s位置在第%d个位置\n",c1, pos, t1, i);
    else
        printf("%s中从第%d开始没出现的%s\n",c1, pos, t1);

    return 0;
}





