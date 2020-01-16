#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define	INFINITY INT_MAX	//整型的最大值∞
//赫夫曼树和赫夫曼编码的存储表示
typedef struct
{
    unsigned int weight;	//权重
    unsigned int parent,lchild,rchild;
}HTNode, *HuffmanTree;		//动态分配数组存储赫夫曼树
typedef char ** HuffmanCode;//动态分配数组存储赫夫曼编码表


//选出无父结点，并且权值最小的两个结点，赋值给s1，s2 
void Select(HuffmanTree &HT,int x,int &s1,int &s2)
{
    int i = 1,min1 = INFINITY,min2 = INFINITY;
    for(i = 1;i <= x; i++)//找最小 
        if(HT[i].weight < min1 && HT[i].parent == 0)
        {
            min1 = HT[i].weight;
            s1 = i;
        }
        for(i = 1;i <= x; i++)//找次小 
            if(HT[i].weight < min2 && i != s1 && HT[i].parent == 0)
            {
                min2 = HT[i].weight;
                s2 = i;
            }
}

// 算法 6.12 赫夫曼编码算法
void HuffmanCoding(HuffmanTree &HT,HuffmanCode &HC,int *w,int n)
{	//w存放n个字符的权值（均>0），构造赫夫曼树HT，并求出n个字符的赫夫曼编码HC
    int m,i;
    HuffmanTree p;
    char *cd;
    if(n <= 1)
        return ;
    m = 2 * n - 1;
    HT = (HuffmanTree)malloc((m+1) * sizeof(HTNode));	//0号单元未用
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
    for(i = n + 1; i <= m; ++i)	//建赫夫曼树
    {   //在HT[1...i-1]选择parent为0且weight最小的两个结点，其序号分别为s1和s2

        int s1,s2;
        Select(HT,i-1,s1,s2);
        HT[s1].parent = i;	HT[s2].parent = i;
        HT[i].lchild = s1;	HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
    //---从叶子到根逆向求取每个字符的赫夫曼编码---
    HC = (HuffmanCode)malloc((n+1) * sizeof(char *));	//分配n个字符编码的头指针向量
    cd = (char *)malloc(n * sizeof(char));				//分配求编码的工作空间
    cd[n - 1] = '\0';									//编码结束符
    for(i = 1; i <= n; ++i){
        int start = n - 1, c, f;
        //从叶子到根逆向求编码
        for(c = i, f = HT[i].parent; f != 0; c = f,f = HT[f].parent)
            if(HT[f].lchild == c)
                cd[--start] = '0';
            else
                cd[--start] = '1';
        HC[i] = (char *)malloc((n - start) * sizeof(char));	//为第i个字符编码分配空间
        strcpy(HC[i], &cd[start]);
        //printf("%d的赫夫曼编码为：%s\n",HT[i].weight,HC[i]);

    }
    free(cd);	//释放工作空间
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
    num = count / 8;	//存储字符需要的多少个字节
	left = count % 8;	//字符串剩余不足8位的个数
	(*pbicode) = (unsigned char *)malloc(sizeof(unsigned char) * (num + (left ? 1 : 0)));
	memset((*pbicode), 0, num + (left ? 1 : 0));

	j = -1;
	for (i = 0; i < count; i++)//位运算，每8个字符以2进制的形式储存在一个字符中 
	{
		if (i % 8 == 0)			j++;
		(*pbicode)[j] <<= 1;           //左移1位   
		strcode[i] -= '0';
		(*pbicode)[j] |= strcode[i];	//按位或	   
    }
	if (left != 0)	//如果left不为0，需要把剩余的几个位向左边靠拢 
	{
		(*pbicode)[j] <<= 8 - left; //例如left为2，即00000011，需要左移6位变为11000000 
	}
}
void DeCompress(unsigned char* bicode, char *strdecode, int count)
{   // count代表bicode中的字节个数 
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
   {  //Huffman树没有左孩子必没有右孩子，即为叶子结点
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
    char *str = "AEBACEACDCA",*pstr;//str原来串
    char strcode[100] = { 0 };      //编码后0和1的串
    unsigned char *bicode = NULL;   //压缩编码后01二进制  
    char strdecode[100] = { 0 };    //解压编码后0和1的串 
    char destr[100] = { 0 };        //解压后destr原来串 
    char word[6] = {'A', 'B', 'C', 'D', 'E', 0};
    int w[5] =     {4,  1,  3,  1,  2 };
    int i,n = 5, count = 0;


    // 1. Coding 
    HuffmanCoding(HT,HC,w,n);
    for(i = 1; i <= 5; ++i)
        printf("%c编码为:%s\n",word[i-1], HC[i]);
    // 2. GetCodes
    GetCodes(str, HT, HC, strcode);
    printf("%s编码后为：%s\n",str, strcode);
    // 3. Compress
    count = strlen(strcode) % 8 ? strlen(strcode) / 8 + 1 : strlen(strcode) / 8;
    printf("%s压缩后占字节数为：%d\n",strcode, count);
    Compress(strcode, &bicode);
    // 4. DeCompress
    DeCompress( bicode, strdecode, count);
    printf("解压后编码为：%s\n",strdecode);
    // 5. GetStrs
    GetStrs(strdecode, HT,  word, destr);
    printf("解码后为：%s\n",destr);
    

    free(bicode);
    free(HT);
    for(i = 1; i <= 5; ++i)
        free(HC[i]);
    free(HC);
    return 0;
}