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

// �󳤶�
int StrLength(SString S)
{
    return S[0];
}

//// ���Ƚ� 
int StrCompare(SString S,SString T)
	//��S>T���򷵻�ֵ>0����S=T���򷵻�ֵ=0����S<T���򷵻�ֵ<0
{
	int i;
	for (i = 1; i <= S[0] && i <= T[0]; ++i)
		if(S[i] != T[i])
			return S[i] - T[i];

	return S[0] - T[0];
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

// �㷨4.1  
int Index(SString S, SString T,int pos)
{   // TΪ�ǿմ���������S�е�pos���ַ�֮�������T��ȵ��Ӵ���
    // �򷵻ص�һ���������Ӵ���S�е�λ�ã����򷵻�0
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



//  �����㷨4.1 Index
int main(void)
{
    SString S, T;
    int i = 0, pos = 5;
    char *c1 = "abcdefde",*t1 = "de";
   
    StrAssign(S, c1);
    StrAssign(T, t1);
    i = Index(S, T, pos);
    if(i)
        printf("%s�дӵ�%d��ʼ��һ�γ��ֵ�%sλ���ڵ�%d��λ��\n",c1, pos, t1, i);
    else
        printf("%s�дӵ�%d��ʼû���ֵ�%s\n",c1, pos, t1);

    return 0;
}





