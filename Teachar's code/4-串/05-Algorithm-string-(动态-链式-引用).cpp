#include <stdio.h>
#include <stdlib.h>

#define Status      int
#define OK          1
#define ERROR       0
#define OVERFLOW    -2
#define BLANK       '#'


#define CHUNKSIZE 4	//���û�����Ŀ��С
//== == == ���Ŀ����洢��ʾ(����ͷ���)== == ==
typedef struct Chunk{
    char ch[CHUNKSIZE];
    struct Chunk *next;
}Chunk, SNode;

typedef struct{
    Chunk *head, *tail; // ͷβָ�루�����������У�
    int curlen;         // ��ǰ��������Ϊ���һ����㲻һ��ռ����
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
    for(i = 0, c = chars; *c ; ++i){ //��֤charsָ����ַ�����'\0'��β
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