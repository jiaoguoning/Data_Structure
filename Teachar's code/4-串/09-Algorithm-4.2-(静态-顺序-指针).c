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

void PrintStr(SString S)
{
    int i;
    for (i = 1; i <= S[0]; i++)
        printf("%c",S[i]);
    printf("\n");
}

// 测试算法4.2 Concat
int main(void)
{
    SString s1,s2,T, s3;
    int i;
    char *c1 = "abcdef", *c2 = "ABCDEFGHIJ", c3[258];
    for (i = 0; i < 258; i++){
        c3[i] = 'a';
        if(i >= 248)
            c3[i] = 'K'- 248 + i;
    }

    StrAssign(&s1, c1);
    StrAssign(&s2, c2);
    StrAssign(&s3, c3);
    PrintStr(s3);

    Concat(&T, s1, s2);

    PrintStr(T);

    PrintStr(s3);
    Concat(&T, s1, s3);
    PrintStr(T);

    return 0;
}
