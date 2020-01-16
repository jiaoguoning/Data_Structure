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
Status StrAssign(SString *T,char * chars)
{    // 生成一个其值等于串常量chars的串T
    char *c = NULL;
    int i, uncut = 0;
    for(i = 1, c = chars; *c && i <= 255; ++i)
        (*T)[i] = *c++;
    (*T)[0] = i-1;
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



//// 串比较1 
//Status StrCompare1(SString S,SString T)
//{
//    int i;
//    if(!S[0] || !T[0])
//        exit(OVERFLOW);
//    for (i = 1; i <= S[0] && i <= T[0] && S[i] == T[i]; i++);
//    if(i > S[0] && i > T[0])
//        return 0;
//    else if(i > S[0])
//        return -1;
//    else
//        return 1;
//}

// 算法4.2 
Status Concat(SString *T,SString S1,SString S2)
{    //用T返回S1和S2联接而成的新串。若未截断返回1，若截断返回0
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

// 算法4.3 
Status SubString(SString *Sub,SString S,int pos,int len)
{   //用Sub返回串S的第pos个字符起长度为len的子串
    //其中，1 ≤ pos ≤ StrLength(S)且0 ≤ len ≤ StrLength(S) - pos + 1(从pos开始到最后有多少字符)
    //第1个字符的下标为1,因为第0个字符存放字符长度
    int i;
    if(pos < 1 || pos > S[0] || len < 0 || len > S[0] - pos + 1)
        return ERROR ;
    for (i = 1; i <= len; i++)
    {
        //S中的[pos,len]的元素 -> *Sub中的[1,len]
        (*Sub)[i] = S[pos + i - 1];//下标运算符 > 寻址运算符的优先级
    }
    (*Sub)[0] = len;
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
            SubString(&sub, S, i, m);
            if(StrCompare(sub, T) != 0)
                ++i;
            else
                return i;
        }//while
    }//if

    return 0;
}


// 测试 Index
int main(void)
{
    SString S, T;
    int i = 0;
    char *c1 = "abcdefde",*t1 = "de";
   
    StrAssign(&S, c1);
    StrAssign(&T, t1);
    i = Index(S, T, 1);
    if(i)
        printf("%s第一次出现的%s位置在第%d个位置\n",c1, t1, i);
    else
        printf("%s中没出现的%s\n",c1, t1);

    return 0;
}






//// 测试 Concat
//int main(void)
//{
//    SString s1,s2,T, s3;
//    int i;
//    char *c1 = "abcdef", *c2 = "ABCDEFGHIJ", c3[258];
//    for (i = 0; i < 258; i++){
//        c3[i] = 'a';
//        if(i >= 248)
//            c3[i] = 'K'- 248 + i;
//    }
//
//    StrAssign(&s1, c1);
//    StrAssign(&s2, c2);
//    StrAssign(&s3, c3);
//    PrintStr(s3);
//
//    Concat(&T, s1, s2);
//
//    PrintStr(T);
//
//    PrintStr(s3);
//    Concat(&T, s1, s3);
//    PrintStr(T);
//
//    return 0;
//}




//// 测试 SubString
//int main(void)
//{
//    SString s3, T,Sub;
//    int i;
//    for (i = 1; i <= 255; i++)
//    {
//        s3[i] = 'a';
//        if(i >= 248)
//            s3[i] = 'K';
//    }
//    s3[0] = 255;
//    SubString(&Sub,s3,247,8);
//    PrintStr(Sub);
//
//    return 0;
//}
//







