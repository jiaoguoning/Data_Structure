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



//// ���Ƚ�1 
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

// �㷨4.3 
Status SubString(SString *Sub,SString S,int pos,int len)
{   //��Sub���ش�S�ĵ�pos���ַ��𳤶�Ϊlen���Ӵ�
    //���У�1 �� pos �� StrLength(S)��0 �� len �� StrLength(S) - pos + 1(��pos��ʼ������ж����ַ�)
    //��1���ַ����±�Ϊ1,��Ϊ��0���ַ�����ַ�����
    int i;
    if(pos < 1 || pos > S[0] || len < 0 || len > S[0] - pos + 1)
        return ERROR ;
    for (i = 1; i <= len; i++)
    {
        //S�е�[pos,len]��Ԫ�� -> *Sub�е�[1,len]
        (*Sub)[i] = S[pos + i - 1];//�±������ > Ѱַ����������ȼ�
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
            SubString(&sub, S, i, m);
            if(StrCompare(sub, T) != 0)
                ++i;
            else
                return i;
        }//while
    }//if

    return 0;
}


// ���� Index
int main(void)
{
    SString S, T;
    int i = 0;
    char *c1 = "abcdefde",*t1 = "de";
   
    StrAssign(&S, c1);
    StrAssign(&T, t1);
    i = Index(S, T, 1);
    if(i)
        printf("%s��һ�γ��ֵ�%sλ���ڵ�%d��λ��\n",c1, t1, i);
    else
        printf("%s��û���ֵ�%s\n",c1, t1);

    return 0;
}






//// ���� Concat
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




//// ���� SubString
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







