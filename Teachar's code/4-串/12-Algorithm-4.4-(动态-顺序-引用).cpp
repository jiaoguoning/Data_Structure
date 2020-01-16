#include <stdio.h>
#include <stdlib.h>

#define Status      int
#define OK          1
#define ERROR       0
#define OVERFLOW    -2

//---- ���Ķѷ���洢��ʾ----  
typedef struct {
	char *ch;	//���Ƿǿմ����򰴴�������洢��������chΪNULL
	int length;	//������
}HString;


// �㷨4.4 
Status StrInsert(HString &S,int pos,HString T)
{
	//1 �� pos �� StrLength(S) + 1���ڴ�S�ĵ�pos���ַ�֮ǰ���봮T��
	//��1���ַ����±���0��
	//int i;
	//if(pos < 1 || pos > S.length + 1)
	//	return ERROR;
	//if (T.length)
	//{
	//	if(!(S.ch = (char*)realloc(S.ch,(S.length + T.length) * sizeof(char))))
	//	{
	//		printf("ERROR!\n");
	//		exit(OVERFLOW);
	//	}
	//	//ע��������ƶ�������һ��Ҫ���ƶ����һ�����������ƶ���pos��
	//	//��Ϊ���ƶ���pos���Ḳ��ԭ���ַ��Ժ����ƶ�����Ӱ��
	//	for(i = S.length - 1;i >= pos-1 ;--i)
	//		S.ch[i + T.length] = S.ch[i];
	//	for (i = pos-1; i < pos-1 + T.length; i++)
	//		S.ch[i] = T.ch[i - pos + 1];
	//	S.length += T.length;
	//}
	int i;
    if(pos < 1 || pos > S.length+1)
        return ERROR;
    if(T.length){
        S.ch = (char *)realloc(S.ch, (S.length+T.length)*sizeof(char));
        if(!S.ch)
            exit(OVERFLOW);
        for(i = S.length-1; i >= pos-1; --i)
             S.ch[i + T.length] = S.ch[i];
        for(i = 0; i < T.length ;++i)
            S.ch[pos-1+i] = T.ch[i];
        S.length += T.length;
    }
    
    
    return OK;
}


Status StrAssign(HString &T,char *chars)
{
	//����һ����ֵ���ڴ�����chars�Ĵ�T
	int i,j;
	char *c;
	if(T.ch)
		free(T.ch);
	for (i = 0,c = chars; *c; ++i,++c)   ;   
	if(!i)
	{
		T.ch = NULL;
		T.length = 0;
	}
	else
	{
		if(!(T.ch = (char*)malloc(i * sizeof(char))))
			exit(OVERFLOW);
		for (j = 0; j < i; ++j)
			T.ch[j] = chars[j];
		T.length = i;
	}
	return OK;
}

void PrintStr(HString S)
{
	int i;
	for (i = 0; i < S.length; i++)
		printf("%c",S.ch[i]);
	printf("\n");
}

// �����㷨4.4  StrInsert
int main(void)
{
	int i;
    char str1[12] = {'A','B','C','D','E','F','G','H','I','J','K','\0'};
    char str2[7] = {'u','v','w','x','y','z','\0'};
	HString S, T;
    T.ch = S.ch = NULL;
    StrAssign(S, str1);
    StrAssign(T, str2);
    PrintStr(S);
    PrintStr(T);
    StrInsert(S,5,T);
    PrintStr(S);

	return 0;
}