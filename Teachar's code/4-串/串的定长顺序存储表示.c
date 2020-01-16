#include <stdio.h>
#include <string.h>
//���Ķ���˳��洢��ʾ
#define MAXSTRLEN 255							//�û�����255���ڶ�����󴮳�
typedef unsigned char SString[MAXSTRLEN + 1];	//0�ŵ�Ԫ��Ŵ��ĳ���

int Concat(SString *T,SString S1,SString S2)
	//��T����S1��S2���Ӷ��ɵ��´�����δ�ضϷ���1�����ضϷ���0
{
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

int SubString(SString *Sub,SString S,int pos,int len)
	//��Sub���ش�S�ĵ�pos���ַ��𳤶�Ϊlen���Ӵ�
	//���У�1 �� pos �� StrLength(S)��0 �� len �� StrLength(S) - pos + 1(��pos��ʼ������ж����ַ�)
	//��1���ַ����±�Ϊ1,��Ϊ��0���ַ�����ַ�����
{
	int i;
	if(pos < 1 || pos > S[0] || len < 0 || len > S[0] - pos + 1)
		return 0;
	for (i = 1; i <= len; i++)
	{
		//S�е�[pos,len]��Ԫ�� -> *Sub�е�[1,len]
		(*Sub)[i] = S[pos + i - 1];//�±������ > Ѱַ����������ȼ�
	}
	(*Sub)[0] = len;
	return 1;
}
void PrintStr(SString S)
{
	int i;
	for (i = 1; i <= S[0]; i++)
		printf("%c",S[i]);
	printf("\n");
}


int main(void)
{
	/*����˳��洢��ʼ���ʹ�ӡ�ķ���
	SString s = {4,'a','b','c','d'};
	int i;
	//s = "abc";	//����ֱ�Ӹ�ֵ

	for (i = 1; i <= s[0]; i++)
		printf("%c",s[i]);
	*/
	SString s1 = {4,'a','b','c','d'};
	SString s2 = {4,'e','f','g','h'},s3;
	SString T,Sub;
	int i;
	
	for (i = 1; i <= 255; i++)
	{
		s3[i] = 'a';
		if(i >= 248)
			s3[i] = 'K';
	}
	s3[0] = 255;
	SubString(&Sub,s3,247,8);
	PrintStr(Sub);
	



	return 0;
}