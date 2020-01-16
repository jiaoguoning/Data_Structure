#include <stdio.h>
#include <stdlib.h>

#define Status      int
#define OK          1
#define ERROR       0
#define OVERFLOW    -2

//���Ķ���˳��洢��ʾ
#define MAXSTRLEN       255						//�û�����255���ڶ�����󴮳�
typedef unsigned char SString[MAXSTRLEN + 1];	//0�ŵ�Ԫ��Ŵ��ĳ���

// ����ֵҲ���Ǵ��ĳ�ʼ��
Status StrAssign(SString &T,char * chars)
{    // ����һ����ֵ���ڴ�����chars�Ĵ�T
    char *c = NULL;
    int i, uncut = 0;
    for(i = 1, c = chars; *c && i <= 255; ++i)
        T[i] = *c++;
    T[0] = i-1;
    if(i > 255)
        return ERROR;   // �����ض�
    else
        return OK;
}


// �㷨4.3 
Status SubString(SString &Sub,SString S,int pos,int len)
{   //��Sub���ش�S�ĵ�pos���ַ��𳤶�Ϊlen���Ӵ�
    //���У�1 �� pos �� StrLength(S)��0 �� len �� StrLength(S) - pos + 1(��pos��ʼ������ж����ַ�)
    //��1���ַ����±�Ϊ1,��Ϊ��0���ַ�����ַ�����
    int i;
    if(pos < 1 || pos > S[0] || len < 0 || len > S[0] - pos + 1)
        return ERROR ;
    for (i = 1; i <= len; i++)
    {
        //S�е�[pos,len]��Ԫ�� -> *Sub�е�[1,len]
        Sub[i] = S[pos + i - 1];//�±������ > Ѱַ����������ȼ�
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

// �����㷨4.3  SubString
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