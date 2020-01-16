#include <stdio.h>
#include <stdlib.h>

#define Status      int
#define OK          1
#define ERROR       0
#define OVERFLOW    -2
#define TElemType   char

// �������Ķ�������洢��ʾ
typedef struct BiTNode
{
    TElemType data;
    struct BiTNode *lchild ,*rchild;	//���Һ���ָ��
}BiTNode,*BiTree;

/* ------------------ջ��ʵ��----------------- */
#define STACK_INIT_SIZE 20
#define STACKINCREMENT  5
#define ElemType        BiTree

//��ΪҪ�޸�ջS�ڴ������ݳ�Ա��ֵ����˱��봫��S�ĵ�ַ
typedef struct {
    ElemType *base;     // �ڹ���֮ǰ������֮��base��ֵΪNULL
    ElemType *top;      // ջ��ָ��
    int stacksize;      // ��ǰ�ѷ���洢�ռ䣬��Ԫ��Ϊ��λ
}SqStack;

//��ΪҪ�޸�ջS�ڴ������ݳ�Ա��ֵ����˱��봫��S�ĵ�ַ
Status InitStack(SqStack &S)
{
    S.base = (ElemType*)malloc(sizeof(ElemType) * STACK_INIT_SIZE);
    if (!S.base)
    {
        printf("��ʼ��ʧ�ܣ�\n");
        exit(OVERFLOW);     // return ERROR;
    }
    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
    return OK;
}

Status GetTop(SqStack S,ElemType &e){
    //��ջ���գ�����e����S��ջ��Ԫ�أ�������OK�����򷵻�ERROR
    if(S.base == S.top)
        return ERROR;
    e = *(S.top - 1);
    return OK;
}

Status Push(SqStack &S,ElemType e){
    //����Ԫ��eΪ�µ�ջ��Ԫ�� 
    if ((S.top - S.base) >= S.stacksize)    // ջ��
    {
        S.base = (ElemType *)realloc(S.base,S.stacksize+STACKINCREMENT);
        if (!S.base)
        {
            printf("׷��ʧ��!\n");
            exit(OVERFLOW);     // return ERROR;
        }
        S.top = S.base + S.stacksize;
        S.stacksize += STACKINCREMENT;
    }
    *S.top++ = e;
    return OK;
}

Status Pop(SqStack &S,ElemType &e)
{
    if (S.top == S.base)
    {
        printf("��ջʧ�ܣ�ջΪ��!\n");
        return ERROR;
    }
    e = *--S.top;
    return OK;
}
/*-----------------------------------------*/


//������������ԭʼ����
char arr1[] = {'A','B','D','\0','\0','E','G','\0','\0','\0','C','\0','F','\0','\0'};
char arr2[] = {'A','B','E','\0','L','\0','\0','\0','D','H','M','\0','\0','I','\0','\0','J','\0','\0'};
char arr3[] = {'-','+','a','\0','\0','*','b','\0','\0','-','c','\0','\0','d','\0','\0','/','e','\0','\0','f','\0','\0'};

int arr_i = 0;

// �㷨6.4 ���������� - ���������������������
Status CreateBiTree(BiTree &T)
{
    char ch;
    ch = arr3[arr_i++];
    if(ch == '\0')
    {
        T = NULL;
    }
    else
    {
        if(!(T = (BiTNode *)malloc(sizeof(BiTNode))))
            exit(OVERFLOW);
        T->data = ch;			//���ɸ��ڵ�
        CreateBiTree(T->lchild);//����������
        CreateBiTree(T->rchild);//����������
    }
    return OK;
}

Status Visit(TElemType e)
{
    if(!e)
        return ERROR;
    printf("%c ",e);
    return OK;
}


// �㷨 6.1  �������-�ݹ� 
Status PreOrderTraverse(BiTree T,int (*Visit)(TElemType e))
{	//���ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú�����
    //�������������T�ĵݹ��㷨����ÿ������Ԫ�ص��ú���Visit��
    if(T){
        if(Visit(T->data))
            if(PreOrderTraverse(T->lchild,Visit))
                if(PreOrderTraverse(T->rchild,Visit))
                    return OK;
        return ERROR;
    }else{
        return OK;
    }
}

// �㷨6.2.1 �������-�ݹ� 
Status InOrderTraverse(BiTree T,int (*Visit)(TElemType e))
    //���ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú�����
    //�������������T�ĵݹ��㷨����ÿ������Ԫ�ص��ú���Visit��
{
    if(T){
        if(InOrderTraverse(T->lchild,Visit))
            if(Visit(T->data))
                if(InOrderTraverse(T->rchild,Visit))
                    return OK;
        return ERROR;
    }else
    {
        return OK;
    }
}


// �������-�ݹ�  
Status PostOrderTraverse(BiTree T,int (*Visit)(TElemType e))
    //���ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú�����
    //�������������T�ĵݹ��㷨����ÿ������Ԫ�ص��ú���Visit��
{
    if(T){
        if(PostOrderTraverse(T->lchild,Visit))
            if(PostOrderTraverse(T->rchild,Visit))
                if(Visit(T->data))
                    return OK;
        return ERROR;
    }else
    {
        return ERROR;
    }
}


// �㷨6.2 �������-�ǵݹ�
Status InOrderTraverse1(BiTree T,int (*Visit)(TElemType e))
{   //���ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú�����
    //�������������T�ķǵݹ��㷨����ÿ������Ԫ�ص��ú���Visit��
    SqStack S;
    InitStack(S);
    Push(S,T);	//��ָ���ջ

    while (S.base != S.top)	
    {
        BiTree p;
        while (GetTop(S, p) && p){
                //���������ǿ�����������Ϊ�գ������ߵ���ͷ������ջ
            Push(S, p->lchild);	
        }
        Pop(S, p);				//��ָ����ջ������������Ϊ�ջ���������Ϊ�����
        if(S.base != S.top){
            Pop(S, p);			//���ʽ�㣬ÿpopһ�Σ�p�����ƶ�������һ����ܼ���
            if(!Visit(p->data))
                return ERROR;
            Push(S, p->rchild);	//�����·��ƶ�һ��
        }
    }
    return OK;
}

// �㷨6.3 �������-�ǵݹ�
Status InOrderTraverse2(BiTree T,int (*Visit)(TElemType e))
{   //���ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú�����
    //�������������T�ķǵݹ��㷨����ÿ������Ԫ�ص��ú���Visit��
    //�����淽������ڣ�p�ǿյ�ʱ�򣬲��ðѿ�Ҳ��ջ�ٳ�ջ
    SqStack S;
    BiTree p;
    InitStack(S);
    p = T;
    while(p || S.base != S.top)
    {
        if(p){	//ֻҪpָ�벻Ϊ�գ��ͽ�ջ������������
            Push(S, p);
            p = p->lchild;
        }else{  //����pΪ�յ������ջ
            Pop(S, p);
            if(!Visit(p->data))
                return ERROR;
            p = p->rchild;
        }
    }
    return OK;
}
//***********�����˲��õݹ飬�Զ����������в�����һ�㷽��**********//
// ��Ҷ�ӽ�����  
void CountLeaf(BiTree T, int &count)
    //�����������������count���ض�������Ҷ�ӽ�����Ŀ
    //conut��Ϊ���������ڴ���ʱcount��main��Ҫ����
{
    if(T){
        if((!T->lchild) && (!T->rchild))	//��û��������Ҳû��������
            ++count;						//��Ҷ�ӽ�����
        CountLeaf(T->lchild,count);
        CountLeaf(T->rchild,count);
    }
}// CountLeaf


int count;
void CountLeaf1(BiTree T)  //����
    //�����������������count���ض�������Ҷ�ӽ�����Ŀ
    //conut��Ϊ���������ڴ���ʱcount��main��Ҫ����
{
    if(T){
        if((!T->lchild) && (!T->rchild))	//��û��������Ҳû��������
            ++count;						//��Ҷ�ӽ�����
        CountLeaf1(T->lchild );
        CountLeaf1(T->rchild );
    }
}// CountLeaf


void CountLeaf2(BiTree T)  //����
    //�����������������count���ض�������Ҷ�ӽ�����Ŀ
    //conut��Ϊ���������ڴ���ʱcount��main��Ҫ����
{
    if(T){
        CountLeaf2(T->lchild );
        if((!T->lchild) && (!T->rchild))	//��û��������Ҳû��������
            ++count;						//��Ҷ�ӽ�����
        CountLeaf2(T->rchild );
    }
}// CountLeaf

void CountLeaf3(BiTree T)  //����
    //�����������������count���ض�������Ҷ�ӽ�����Ŀ
    //conut��Ϊ���������ڴ���ʱcount��main��Ҫ����
{
    if(T){
        CountLeaf3(T->lchild );
        CountLeaf3(T->rchild );
        if((!T->lchild) && (!T->rchild))	//��û��������Ҳû��������
            ++count;						//��Ҷ�ӽ�����
    }
}// CountLeaf


// ����������  
int BiTreeDepth(BiTree T)
{
    int depth  , depthleft ,depthright ;
    if(!T){
        depth = 0;
    }
    else{
        depthleft  = BiTreeDepth(T->lchild);
        depthright = BiTreeDepth(T->rchild);
        depth = (depthleft > depthright ? depthleft : depthright) + 1;
    }
    return depth;
}


int main(void)
{
    BiTree T;
    int count = 0,depth;
    CreateBiTree(T);
    PreOrderTraverse(T,Visit);
    printf("\n");
    InOrderTraverse1(T,Visit);
    printf("\n");
    CountLeaf(T, count);
    printf("%d\n",count);
    printf("%d\n",BiTreeDepth(T));


    return 0;
}
