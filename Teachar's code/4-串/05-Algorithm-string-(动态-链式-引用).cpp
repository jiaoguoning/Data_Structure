#include <stdio.h>
#include <stdlib.h>

#define Status      int
#define OK          1
#define ERROR       0
#define OVERFLOW    -2
#define BLANK       '#'


#define CHUNKSIZE 4	//可用户定义的块大小
//== == == 串的块链存储表示(不带头结点)== == ==
typedef struct Chunk{
    char ch[CHUNKSIZE];
    struct Chunk *next;
}Chunk, SNode;

typedef struct{
    Chunk *head, *tail; // 头尾指针（类似于链队列）
    int curlen;         // 当前串长（因为最后一个结点不一定占满）
}LString;

Status StrDestroy(LString &S)
{
    while (S.head)
    {
        S.tail = S.head->next;
        free(S.head);
        S.head = S.tail;
    }
    S.curlen = 0;
    return OK;
}

Status StrAssign(LString &T,char *chars)
{
    int i, j, k;
    char *c = NULL;
    SNode *p = NULL;
    if(T.head)
        StrDestroy(T);
    T.curlen = 0;
    for(i = 0, c = chars; *c ; ++i){ //保证chars指向的字符串以'\0'结尾
        p = (SNode* )malloc(sizeof(SNode));
        if(!p)
            exit(OVERFLOW);
        for(k = 0; k < CHUNKSIZE && *c; ++k, T.curlen++)
            p->ch[k] = *c++;
        p->next = NULL;
        if(i == 0)
            T.head =  p;
        else
            T.tail->next = p;
        T.tail = p;
    }
    for (; k < CHUNKSIZE; ++k)
        p->ch[k] = BLANK;
    return OK;
}



void PrintStr(LString S)
{
    int i = 0, j;
    SNode *p = S.head;
    while (i < S.curlen)
    {
        for(j = 0; j < CHUNKSIZE; ++j)
            if(p->ch[j] != BLANK){
                printf("%c", p->ch[j]);
                ++i;
            }
        p = p->next;
    }
    printf("\n");
}




int main(void)
{
    char str[18] = {'a','b','c','d','e','f','g','h','i','g','k','l','m','n','o','p','q','\0'};
    LString S;
    S.head = NULL;
    StrAssign(S ,str);
    PrintStr(S);




    return 0;
}