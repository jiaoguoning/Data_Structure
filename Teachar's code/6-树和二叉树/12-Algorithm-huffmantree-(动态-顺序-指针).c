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
void Select(HuffmanTree *HT,int x,int *s1,int *s2)
{
    int i = 1,min1 = INFINITY,min2 = INFINITY;
    for(i = 1;i <= x; i++)//找最小 
        if((*HT)[i].weight < min1 && (*HT)[i].parent == 0)
        {
            min1 = (*HT)[i].weight;
            *s1 = i;
        }
        for(i = 1;i <= x; i++)//找次小 
            if((*HT)[i].weight < min2 && i != *s1 && (*HT)[i].parent == 0)
            {
                min2 = (*HT)[i].weight;
                *s2 = i;
            }
}

// 算法 6.12 赫夫曼编码算法
void HuffmanCoding(HuffmanTree *HT,HuffmanCode *HC,int *w,int n)
{	//w存放n个字符的权值（均>0），构造赫夫曼树HT，并求出n个字符的赫夫曼编码HC
    int m,i;
    HuffmanTree p;
    char *cd;
    if(n <= 1)
        return ;
    m = 2 * n - 1;
    (*HT) = (HuffmanTree)malloc((m+1) * sizeof(HTNode));	//0号单元未用
    for(p = (*HT) + 1, i = 1; i <= n; ++i,++p,++w){
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
        Select(HT, i-1, &s1, &s2);
        (*HT)[s1].parent = i;	(*HT)[s2].parent = i;
        (*HT)[i].lchild = s1;	(*HT)[i].rchild = s2;
        (*HT)[i].weight = (*HT)[s1].weight + (*HT)[s2].weight;
    }
    //---从叶子到根逆向求取每个字符的赫夫曼编码---
    *HC = (HuffmanCode)malloc((n+1) * sizeof(char *));	//分配n个字符编码的头指针向量
    cd = (char *)malloc(n * sizeof(char));				//分配求编码的工作空间
    cd[n - 1] = '\0';									//编码结束符
    for(i = 1; i <= n; ++i){
        int start = n - 1, c, f;
        //从叶子到根逆向求编码
        for(c = i, f = (*HT)[i].parent; f != 0; c = f,f = (*HT)[f].parent)
            if((*HT)[f].lchild == c)
                cd[--start] = '0';
            else
                cd[--start] = '1';
        (*HC)[i] = (char *)malloc((n - start) * sizeof(char));	//为第i个字符编码分配空间
        strcpy((*HC)[i], &cd[start]);
            
        
    }
    free(cd);	//释放工作空间
}

int main(void)
{
    HuffmanTree HT;
    HuffmanCode HC;
    int w[5] = {36, 10, 27, 10, 18};
    int i,n = 5;
    HuffmanCoding(&HT,&HC,w,n);
    for(i = 1;i <= n; ++i)
        printf("%d的赫夫曼编码为：%s\n",HT[i].weight,HC[i]);

    return 0;
}