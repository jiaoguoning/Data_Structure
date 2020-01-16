#include <stdio.h>
#include <stdlib.h>

#define Status      int
#define OK          1
#define ERROR       0
#define OVERFLOW    -2
#define TElemType   char

//----------- ����˫�״洢��ʾ -----------//
#define MAX_TREE_SIZE   100
typedef struct			//���ṹ
{
    TElemType data;
    int parent;			//˫�׵�λ����
}PTNode;

typedef struct			//���Ľṹ
{
    PTNode nodes[MAX_TREE_SIZE];
    int r,n;			//����λ�úͽ����
}PTree;

// �������ϵ��޸�����Ҷ�ӽ���λ�� 
const int parentArr[] = {-1, 0, 0, 0, 1, 3, 5, 5, 1, 5};
const char dataArr[] = {'R', 'A', 'B', 'C', 'D',  'F', 'G', 'H', 'E','K'};
const int m = 10; //dataArr ���鳤��

void CreateTree(PTree &P)
{
    int i;
    P.n = m;
    for(i = 0; i < m; ++i)	{
        P.nodes[i].data = dataArr[i];
        P.nodes[i].parent = parentArr[i];
        if(-1 == P.nodes[i].parent)
            P.r = i;
    }
}

int DepthTree(PTree P)
{
    int max = 0, i, j, temp = 0;
    
    for(i = 0;i < P.n; ++i){
        // j��˫�׵��±ֻ꣬Ҫ j != -1 ��ô��Ȳ�Ϊ0�����temp��1��ʼ
        for(j = P.nodes[i].parent, temp = 1; -1 != j; j = P.nodes[j].parent){
            temp++;
        }
        if(max < temp)
            max = temp;
    }
    return max;
}

int CountLeaf(PTree P) //defnett
{
    int i, k, length = 0;
    int* temp = (int*)malloc(P.n * sizeof(int));
    temp[length++] = P.nodes[0].parent;
    for(i = 0; i < P.n; ++i) {
        // ��temp[]���ҵ���parent��ȵ�break
        for(k = 0;k < length;k++)
            if(P.nodes[i].parent == temp[k])  
                break;
        // ��û����ȵ�
        if(k >= length)
               temp[length++] = P.nodes[i].parent;
    }
    free(temp);
    // ��Ϊ�������˫����-1���������Ľ�㣬���length�ټ�1
    length -= 1;
    return P.n - length;
}

Status Visit(TElemType e)
{
    if(!e)
        return ERROR;
    printf("%c ",e);
    return OK;
}

// �� cur_e �� T �ķǸ���㣬�򷵻�����˫  
// �����������е��±꣬������ֵΪ���ա��� 
int Parent(PTree P,TElemType cur_e) {
    int i;
    for(i = 0;i < P.n && P.nodes[i].data != cur_e; ++i);
    // ����û��cur_e����cur_e���ڽ��Ϊ����㷵�� ERROR 
    if(i >= P.n || P.nodes[i].parent == -1)
        return ERROR;
    return P.nodes[i].parent;
}


Status Assign(PTree &P,TElemType cur_e,TElemType value)
{ /* ��ʼ����: ��T����,cur_e����T�н���ֵ���������: ��cur_eΪvalue */
    int i;
    for(i = 0;i < P.n;i++)
    {
        if(P.nodes[i].data == cur_e)
        {
            P.nodes[i].data = value;
            return OK;
        }
    }
    return ERROR;
}


int CountDegree(PTree P) //defnett
{
    int i, j, max = -1;
    int temp[20] = { 0 };
     
    for(i = 0; i < P.n; ++i) {
        for(j = 0; j < P.n; ++j){
            if(i == P.nodes[j].parent)
                temp[i]++;
        }
    }
    for(i = 0; i < P.n; ++i)
        if(temp[i] > max)
            max = temp[i];
    // ��Ϊ�������˫����-1���������Ľ�㣬���length�ټ�1

    return max;
}

// ���Ĳ�α���
Status LevelOrderTraverse(PTree P,Status (*pvisit)(TElemType e)){
    int i, j, rear = 0, front = 0;
    //������һ�����У������洢ÿ��Ľ�㣬���ڶ���ΪP.n�㹻���������ܷ���
    int* temp = (int*)malloc(P.n * sizeof(int));
    temp[rear] = P.r;
    rear = (rear + 1) % P.n;
    while(rear != front){
        i = temp[front];
        front = (front + 1) % P.n;
        if(!pvisit(P.nodes[i].data))
            return ERROR;
        // һ������£�˫�׿϶��ں��ӵ�ǰ�棬��Ϊ��
        // ˫���ں���Ļ������ӽ���parent��û��д
        // j ���Դ�i��ʼ  
        for(j = i; j < P.n; ++j)
        {
            if(P.nodes[j].parent == i){
                temp[rear] = j;
                rear = (rear + 1) % P.n;
            }
        }
    }
    free(temp);
    printf("\n");
    return OK;
}




int main(void)
{
    PTree p;
    CreateTree(p);
    LevelOrderTraverse(p ,Visit);
    Assign(p ,'F','X');
    LevelOrderTraverse(p ,Visit);
    printf("������ȣ�%d \n" ,DepthTree(p));
    printf("����Ҷ�ӣ�%d \n" ,CountLeaf(p));
    printf("���� �ȣ�%d \n" ,CountDegree(p));

    return 0;
}

