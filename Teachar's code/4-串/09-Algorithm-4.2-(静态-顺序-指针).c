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
Status StrAssign(SString *T,char * chars)
{    // ����һ����ֵ���ڴ�����chars�Ĵ�T
    char *c = NULL;
    int i, uncut = 0;
    for(i = 1, c = chars; *c && i <= 255; ++i)
        (*T)[i] = *c++;
    (*T)[0] = i-1;
    if(i > 255)
        return ERROR;   // �����ض�
    else
        return OK;
}

// �㷨4.2 
Status Concat(SString *T,SString S1,SString S2)
{    //��T����S1��S2���Ӷ��ɵ��´�����δ�ضϷ���1�����ضϷ���0
    int i = 1,j,uncut = 0;
    if(S1[0] + S2[0] <= MAXSTRLEN)	//δ�ض�
    {
        for (i = 1; i <= S1[0]; i++)//��ֵʱ�ȺŲ��ɶ�
            (*T)[i] = S1[i];
        for (j = 1; j <= S2[0]; j++)
            (*T)[S1[0]+j] = S2[j];	//(*T)[i+j] = S2[j]
        (*T)[0] = S1[0] + S2[0];
        uncut = 1;
    }
    else if(S1[0] < MAXSTRLEN)		//�ض�
    {
        for (i = 1; i <= S1[0]; i++)//��ֵʱ�ȺŲ��ɶ�
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
        /*���߷ֿ���ֵ���ȸ�ֵ���ݣ��ٸ�ֵ����
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

// �����㷨4.2 Concat
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
