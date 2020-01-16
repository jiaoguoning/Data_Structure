#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define	INFINITY INT_MAX	//���͵����ֵ��
//�շ������ͺշ�������Ĵ洢��ʾ
typedef struct
{
    unsigned int weight;	//Ȩ��
    unsigned int parent,lchild,rchild;
}HTNode, *HuffmanTree;		//��̬��������洢�շ�����
typedef char ** HuffmanCode;//��̬��������洢�շ��������


//ѡ���޸���㣬����Ȩֵ��С��������㣬��ֵ��s1��s2 
void Select(HuffmanTree &HT,int x,int &s1,int &s2)
{
    int i = 1,min1 = INFINITY,min2 = INFINITY;
    for(i = 1;i <= x; i++)//����С 
        if(HT[i].weight < min1 && HT[i].parent == 0)
        {
            min1 = HT[i].weight;
            s1 = i;
        }
        for(i = 1;i <= x; i++)//�Ҵ�С 
            if(HT[i].weight < min2 && i != s1 && HT[i].parent == 0)
            {
                min2 = HT[i].weight;
                s2 = i;
            }
}

// �㷨 6.12 �շ��������㷨
void HuffmanCoding(HuffmanTree &HT,HuffmanCode &HC,int *w,int n)
{	//w���n���ַ���Ȩֵ����>0��������շ�����HT�������n���ַ��ĺշ�������HC
    int m,i;
    HuffmanTree p;
    char *cd;
    if(n <= 1)
        return ;
    m = 2 * n - 1;
    HT = (HuffmanTree)malloc((m+1) * sizeof(HTNode));	//0�ŵ�Ԫδ��
    for(p = HT + 1, i = 1; i <= n; ++i,++p,++w){
        p->weight = *w;
        p->parent = 0;
        p->lchild = 0;
        p->rchild = 0;
    }
    for(;i <= m; ++i,++p){
        p->weight = 0;
        p->parent = 0;
        p->lchild = 0;
        p->rchild = 0;
    }
    for(i = n + 1; i <= m; ++i)	//���շ�����
    {   //��HT[1...i-1]ѡ��parentΪ0��weight��С��������㣬����ŷֱ�Ϊs1��s2

        int s1,s2;
        Select(HT,i-1,s1,s2);
        HT[s1].parent = i;	HT[s2].parent = i;
        HT[i].lchild = s1;	HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
    //---��Ҷ�ӵ���������ȡÿ���ַ��ĺշ�������---
    HC = (HuffmanCode)malloc((n+1) * sizeof(char *));	//����n���ַ������ͷָ������
    cd = (char *)malloc(n * sizeof(char));				//���������Ĺ����ռ�
    cd[n - 1] = '\0';									//���������
    for(i = 1; i <= n; ++i){
        int start = n - 1, c, f;
        //��Ҷ�ӵ������������
        for(c = i, f = HT[i].parent; f != 0; c = f,f = HT[f].parent)
            if(HT[f].lchild == c)
                cd[--start] = '0';
            else
                cd[--start] = '1';
        HC[i] = (char *)malloc((n - start) * sizeof(char));	//Ϊ��i���ַ��������ռ�
        strcpy(HC[i], &cd[start]);
        //printf("%d�ĺշ�������Ϊ��%s\n",HT[i].weight,HC[i]);

    }
    free(cd);	//�ͷŹ����ռ�
}


void GetCodes(char *str, HuffmanTree HT, HuffmanCode HC, char *strcode)
{
    int i;
    char *pstr = str;
    for(i = 0, pstr = str; *pstr; ++pstr){
        if(*pstr == 'A'){
            strcpy(&strcode[i], HC[1]);
            i += strlen(HC[1]);
        }else if (*pstr == 'B'){
            strcpy(&strcode[i], HC[2]);
            i += strlen(HC[2]);
        }else if (*pstr == 'C'){
            strcpy(&strcode[i], HC[3]);
            i += strlen(HC[3]);
        }else if (*pstr == 'D'){
            strcpy(&strcode[i], HC[4]);
            i += strlen(HC[4]);
        }else {
            strcpy(&strcode[i], HC[5]);
            i += strlen(HC[5]);
        }
    }
    strcode[i] = '\0';
}

void Compress(char *strcode,unsigned char**pbicode)
{
	int num, left, count, i, j;
    int arrtest[100] = {0};
    count = strlen(strcode);
    num = count / 8;	//�洢�ַ���Ҫ�Ķ��ٸ��ֽ�
	left = count % 8;	//�ַ���ʣ�಻��8λ�ĸ���
	(*pbicode) = (unsigned char *)malloc(sizeof(unsigned char) * (num + (left ? 1 : 0)));
	memset((*pbicode), 0, num + (left ? 1 : 0));

	j = -1;
	for (i = 0; i < count; i++)//λ���㣬ÿ8���ַ���2���Ƶ���ʽ������һ���ַ��� 
	{
		if (i % 8 == 0)			j++;
		(*pbicode)[j] <<= 1;           //����1λ   
		strcode[i] -= '0';
		(*pbicode)[j] |= strcode[i];	//��λ��	   
    }
	if (left != 0)	//���left��Ϊ0����Ҫ��ʣ��ļ���λ����߿�£ 
	{
		(*pbicode)[j] <<= 8 - left; //����leftΪ2����00000011����Ҫ����6λ��Ϊ11000000 
	}
}
void DeCompress(unsigned char* bicode, char *strdecode, int count)
{   // count����bicode�е��ֽڸ��� 
    int k , ii, i, j = 0;
    unsigned char N;
    for(i = 0; i < count; ++i){
        int arr[8] = {0};
        N = bicode[i];
        k = 0;
        while (N)
        {
            arr[k++] = N % 2;
            N /= 2;
        }
    
    for (ii = 7; ii >= 0; --ii)
        strdecode[j++] = arr[ii] + '0';
    }
    strdecode[j] = '\0';
}

void GetStrs(char *strdecode, HuffmanTree HT,  char* word, char *destr)
{
    int i, n, k = 0;
    char *p = strdecode, str;
    n = strlen(word);
	for (; *p; p++){
		i = 2 * n - 1;
		while (HT[i].lchild)
   {  //Huffman��û�����ӱ�û���Һ��ӣ���ΪҶ�ӽ��
            str = *p++;
			if(str == '0')
				i = HT[i].lchild;
			else
				i = HT[i].rchild;
		}
        --p;
        destr[k++] = word[i-1];
    }

}


int main(void)
{
    HuffmanTree HT;
    HuffmanCode HC;
    char *str = "AEBACEACDCA",*pstr;//strԭ����
    char strcode[100] = { 0 };      //�����0��1�Ĵ�
    unsigned char *bicode = NULL;   //ѹ�������01������  
    char strdecode[100] = { 0 };    //��ѹ�����0��1�Ĵ� 
    char destr[100] = { 0 };        //��ѹ��destrԭ���� 
    char word[6] = {'A', 'B', 'C', 'D', 'E', 0};
    int w[5] =     {4,  1,  3,  1,  2 };
    int i,n = 5, count = 0;


    // 1. Coding 
    HuffmanCoding(HT,HC,w,n);
    for(i = 1; i <= 5; ++i)
        printf("%c����Ϊ:%s\n",word[i-1], HC[i]);
    // 2. GetCodes
    GetCodes(str, HT, HC, strcode);
    printf("%s�����Ϊ��%s\n",str, strcode);
    // 3. Compress
    count = strlen(strcode) % 8 ? strlen(strcode) / 8 + 1 : strlen(strcode) / 8;
    printf("%sѹ����ռ�ֽ���Ϊ��%d\n",strcode, count);
    Compress(strcode, &bicode);
    // 4. DeCompress
    DeCompress( bicode, strdecode, count);
    printf("��ѹ�����Ϊ��%s\n",strdecode);
    // 5. GetStrs
    GetStrs(strdecode, HT,  word, destr);
    printf("�����Ϊ��%s\n",destr);
    

    free(bicode);
    free(HT);
    for(i = 1; i <= 5; ++i)
        free(HC[i]);
    free(HC);
    return 0;
}