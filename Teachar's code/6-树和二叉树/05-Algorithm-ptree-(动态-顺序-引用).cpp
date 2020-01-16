#include <stdio.h>
#include <stdlib.h>

#define Status      int
#define OK          1
#define ERROR       0
#define OVERFLOW    -2
#define TElemType   char

//----------- 树的双亲存储表示 -----------//
#define MAX_TREE_SIZE   100
typedef struct			//结点结构
{
    TElemType data;
    int parent;			//双亲的位置域
}PTNode;

typedef struct			//树的结构
{
    PTNode nodes[MAX_TREE_SIZE];
    int r,n;			//根的位置和结点数
}PTree;

// 根据书上的修改了下叶子结点的位置 
const int parentArr[] = {-1, 0, 0, 0, 1, 3, 5, 5, 1, 5};
const char dataArr[] = {'R', 'A', 'B', 'C', 'D',  'F', 'G', 'H', 'E','K'};
const int m = 10; //dataArr 数组长度

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
        // j是双亲的下标，只要 j != -1 那么深度不为0，因此temp从1开始
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
        // 在temp[]中找到与parent相等的break
        for(k = 0;k < length;k++)
            if(P.nodes[i].parent == temp[k])  
                break;
        // 若没有相等的
        if(k >= length)
               temp[length++] = P.nodes[i].parent;
    }
    free(temp);
    // 因为根结点中双亲是-1，不是树的结点，因此length再减1
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

// 若 cur_e 是 T 的非根结点，则返回它的双  
// 亲所在数组中的下标，否则函数值为“空”。 
int Parent(PTree P,TElemType cur_e) {
    int i;
    for(i = 0;i < P.n && P.nodes[i].data != cur_e; ++i);
    // 若是没有cur_e或者cur_e所在结点为根结点返回 ERROR 
    if(i >= P.n || P.nodes[i].parent == -1)
        return ERROR;
    return P.nodes[i].parent;
}


Status Assign(PTree &P,TElemType cur_e,TElemType value)
{ /* 初始条件: 树T存在,cur_e是树T中结点的值。操作结果: 改cur_e为value */
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
    // 因为根结点中双亲是-1，不是树的结点，因此length再减1

    return max;
}

// 树的层次遍历
Status LevelOrderTraverse(PTree P,Status (*pvisit)(TElemType e)){
    int i, j, rear = 0, front = 0;
    //类似于一个队列，用来存储每层的结点，由于队列为P.n足够长，不可能放满
    int* temp = (int*)malloc(P.n * sizeof(int));
    temp[rear] = P.r;
    rear = (rear + 1) % P.n;
    while(rear != front){
        i = temp[front];
        front = (front + 1) % P.n;
        if(!pvisit(P.nodes[i].data))
            return ERROR;
        // 一般情况下，双亲肯定在孩子的前面，因为若
        // 双亲在后面的话，孩子结点的parent域没法写
        // j 可以从i开始  
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
    printf("树的深度：%d \n" ,DepthTree(p));
    printf("树的叶子：%d \n" ,CountLeaf(p));
    printf("树的 度：%d \n" ,CountDegree(p));

    return 0;
}

