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

// 测试算法4.3  SubString
int main(void)
{
    SString s1, s3, Sub;
    int i;
    char *c = "abcdefghig";
    
    StrAssign(s1, c);
    for (i = 1; i <= 255; i++)
    {
        s3[i] = 'a';
        if(i >= 248)
            s3[i] = 'K';
    }

    s3[0] = 255;
    PrintStr(s3);
    SubString(Sub,s3,247,8);
    PrintStr(Sub);

    PrintStr(s1);
    SubString(Sub,s1,3,6);
    PrintStr(Sub);


    return 0;
}