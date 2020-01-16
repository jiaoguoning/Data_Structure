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
Status StrAssign(SString *T,char *chars)
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

// �㷨4.5  
int Index(SString S, SString T,int pos)
{   // TΪ�ǿմ���������S�е�pos���ַ�֮�������T��ȵ��Ӵ���
    // ���У�1 �� pos �� S[0]
    int i = pos, j = 1;
    while (i <= S[0] && j <= T[0]){
        PrintIndex(S, T, i, j);
        if(S[i] == T[j]){   //�����ȽϺ����ַ�
            ++i;
            ++j;
        }else{
            i = i - j + 2;  //ָ����ˣ�����ƥ��
            j = 1;
        }
    }
    if(j > T[0])
        return i - T[0];
    else
        return 0;
}



// �㷨4.6  
int next[10];   //0��Ԫ�ز���
int Index_KMP(SString S, SString T,int pos)
{   // TΪ�ǿմ���������S�е�pos���ַ�֮�������T��ȵ��Ӵ���
    // ���У�1 �� pos �� S[0]
    int i = pos, j = 1;
    while (i <= S[0] && j <= T[0]){
        PrintIndex(S, T, i, j);
        if(j == 0 || S[i] == T[j]){   //�����ȽϺ����ַ�
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
// �㷨 4.7
void get_next(SString T)
{  // ��ģʽ��T��next����ֵ����������next
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


// �㷨4.8 get_nextval    
void get_nextval(SString T)
{    // ��ģʽ��T��next��������ֵ����������nextval��
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


// ���� �㷨4.6-4.7 Index_KMP   get_next
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
        printf("%s��һ�γ��ֵ�%sλ���ڵ�%d��λ��\n",c1, t1, i);
    else
        printf("%s��û���ֵ�%s\n",c1, t1);

    return 0;
}

