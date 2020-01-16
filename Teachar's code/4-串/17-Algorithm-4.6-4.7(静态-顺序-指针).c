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
Status StrAssign(SString *T,char *chars)
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

void PrintStr(SString S)
{
    int i;
    for (i = 1; i <= S[0]; i++)
        printf("%c",S[i]);
    printf("\n");
}

void PrintIndex(SString S, SString T,int i, int j)
{
    int k = 0, r = 1;
    system("cls");
    for (k = 1; k <= S[0]; k++)
        printf("%c ",S[k]);
    printf("\n");
    for (k = 1; k <= S[0]; k++)
        if(k == i)
            printf("| ");
        else
            printf("  ",S[i]);
    printf("\n");
    for (k = 1; k <= S[0] && r <= T[0] ; k++)
        if(k >= i-j+1)
            printf("%c ",T[r++]);
        else
            printf("  ",S[i]);
    printf("\n");
    system("pause");
}

// 算法4.5  
int Index(SString S, SString T,int pos)
{   // T为非空串。若主串S中第pos个字符之后存在与T相等的子串，
    // 其中：1 ≤ pos ≤ S[0]
    int i = pos, j = 1;
    while (i <= S[0] && j <= T[0]){
        PrintIndex(S, T, i, j);
        if(S[i] == T[j]){   //继续比较后续字符
            ++i;
            ++j;
        }else{
            i = i - j + 2;  //指针后退，重新匹配
            j = 1;
        }
    }
    if(j > T[0])
        return i - T[0];
    else
        return 0;
}



// 算法4.6  
int next[10];   //0号元素不用
int Index_KMP(SString S, SString T,int pos)
{   // T为非空串。若主串S中第pos个字符之后存在与T相等的子串，
    // 其中：1 ≤ pos ≤ S[0]
    int i = pos, j = 1;
    while (i <= S[0] && j <= T[0]){
        PrintIndex(S, T, i, j);
        if(j == 0 || S[i] == T[j]){   //继续比较后续字符
            ++i;
            ++j;
        }else{
            j = next[j];
        }
    }
    if(j > T[0])
        return i - T[0];
    else
        return 0;
}
// 算法 4.7
void get_next(SString T)
{  // 求模式串T的next函数值并存入数组next
    int i = 1, j = 0;
    next[1] = 0;
    while(i < T[0])
    {
        if(j == 0 || T[i] == T[j]){
            ++i;
            ++j;
            next[i] = j;
        }else
            j = next[j];
    }
}// get_next


// 算法4.8 get_nextval    
void get_nextval(SString T)
{    // 求模式串T的next函数修正值并存入数组nextval。
    int i = 1, j = 0;
    next[1] = 0;
    while (i < T[0]) {
        if(j == 0 || T[i] == T[j]){
            ++i;
            ++j;
            if(T[i] != T[j])
                next[i] = j;
            else
                next[i] = next[j];
        }else
            j = next[j];
    }
}


// 测试 算法4.6-4.7 Index_KMP   get_next
int main(void)
{
    SString S, T;
    int i = 0;
    char *c1 = "abaaaaeaaaddaaaaaabe", *t1 = "aaaaaab";

    StrAssign(&S, c1);
    StrAssign(&T, t1);
    get_next(T);
    i = Index_KMP(S, T, 2);
    if(i)
        printf("%s第一次出现的%s位置在第%d个位置\n",c1, t1, i);
    else
        printf("%s中没出现的%s\n",c1, t1);

    return 0;
}

