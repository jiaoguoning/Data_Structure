#include <stdio.h>
#include <stdlib.h>

#define Status      int
#define OK          1
#define ERROR       0
#define OVERFLOW    -2
#define FALSE       0
#define TRUE        1

//---图的邻接表存储表示---
#define MAX_VERTEX_NUM  20
#define InfoType        int	//该弧相关信息的指针（假设信息是整数，因此用int类型）
#define VertexType      char	//顶点类型（假设每个顶点是一个字符表示）

typedef enum
{
    DG,DN,UDG,UDN			//有向图，有向网，无向图，无向网
}GraphKind;		

typedef struct ArcNode {    //表结点类型
    int adjvex;				//该弧指向顶点位置 0,1,2,3...
    //这个位置指的是邻接的顶点在表头数组中的位置
    struct ArcNode * nextarc;	//指向下一条弧的指针
    InfoType *info;				//该弧相关信息的指针
}ArcNode;

typedef struct VNode {  //头结点类型
    VertexType data;	//顶点信息（VertexType实际上是顶点类型）
    ArcNode *firstarc;	//指向第一条依附该顶点的弧的指针
}VNode, AdjList[MAX_VERTEX_NUM];

typedef struct	{	    //邻接表类型
    AdjList vertices;	
    int vexnum;	//图的顶点数
    int arcnum;	//图的弧数
    GraphKind kind;			//图的类型标志
}ALGraph;


VertexType Vex[8] = {'1','2','3','4','5','6','7','8'};	//以书上为例'1'代表v1，以此类推
typedef struct  {
    char v1,v2;
    int w;
}VVW;
VVW vvw[9] = {		//每条边依附顶点及权值(权值是假设的)
    /*V1*/	{'1','2',5},{'1','3',2},
    /*V2*/	{'2','4',4},
    /*V3*/	{'3','6',9},{'3','7',5},
    /*V4*/	{'4','8',6},
    /*V5*/	{'5','2',8},{'5','8',5},
    /*V6*/	{'6','7',3}
    /*V7*/
    /*V8*/
};

#define VexNum  8
#define ArcNum  9

int LocateVex(ALGraph G,char v,int vexnum)
{
    int i;
    for (i = 0; i < vexnum; i++)
    {
        if(v == G.vertices[i].data)
            return i;
    }
    printf("输入顶点有误，定位失败！\n");
    exit(OVERFLOW);
}

Status ALCreateDG(ALGraph &G)	//！！！！注意：在同一个顶点表结点链表中，表结点次序可以不同
    //邻接表法创建有向图
{
    int i;
    G.vexnum = VexNum;
    G.arcnum = ArcNum;
    for (i = 0;  i < G.vexnum; ++i)
    {
        G.vertices[i].data = Vex[i];
        G.vertices[i].firstarc = NULL;
    }
    for(i = 0;i < G.vexnum; ++i)	//遍历邻接表各个顶点，依次创建表结点
    {		
        int k;
        for(k = 0; k < G.arcnum; ++k)
        {
            ArcNode *p, *newNode; 
            if(G.vertices[i].data == vvw[k].v1)
            {
                newNode = (ArcNode *)malloc(sizeof(ArcNode));
                if(!newNode)
                    return 0;
                newNode->adjvex = LocateVex(G,vvw[k].v2,G.vexnum);//确定顶点v2在G.vertices中的位置
                newNode->nextarc = NULL;
                newNode->info = (InfoType *)malloc(sizeof(InfoType) * 1);
                newNode->info[0] = vvw[k].w;	//此处可以放有向网或者无向网的权值
                p = G.vertices[i].firstarc;		//p指向第i个顶点的对应的第1个都结点
                if(!p)	//如果p是空的话，直接赋值
                {
                    G.vertices[i].firstarc = newNode;
                }else	//若p不为空
                {
                    while(p->nextarc)
                        p = p->nextarc;				//通过循环让p指向第i个顶点的最后1个表结点
                    p->nextarc = newNode;			//同一个顶点的表结点次序可以不同
                }
            }
        }
    }
    return OK;
}

Status ALCreateUDG(ALGraph &G)	//！！！！注意：在同一个顶点表结点链表中，表结点次序可以不同
    //邻接表法创建无向图
{
    int i;
    G.vexnum = VexNum;
    G.arcnum = ArcNum;
    for (i = 0;  i < G.vexnum; ++i)
    {
        G.vertices[i].data = Vex[i];
        G.vertices[i].firstarc = NULL;
    }
    for(i = 0;i < G.vexnum; ++i)	//遍历邻接表各个顶点，依次创建表结点
    {		
        int k;
        for(k = 0; k < G.arcnum; ++k)
        {
            ArcNode *p, *newNode; 
            if(G.vertices[i].data == vvw[k].v1 || G.vertices[i].data == vvw[k].v2)
            {
                newNode = (ArcNode *)malloc(sizeof(ArcNode));
                if(!newNode)
                    return 0;
                if(G.vertices[i].data == vvw[k].v1)
                    newNode->adjvex = LocateVex(G,vvw[k].v2,G.vexnum);//确定顶点v2在G.vertices中的位置
                else
                    newNode->adjvex = LocateVex(G,vvw[k].v1,G.vexnum);//确定顶点v1在G.vertices中的位置
                newNode->nextarc = NULL;
                newNode->info = (InfoType *)malloc(sizeof(InfoType) * 1);
                newNode->info[0] = vvw[k].w;	//此处可以放有向网或者无向网的权值
                p = G.vertices[i].firstarc;		//p指向第i个顶点的对应的第1个都结点
                if(!p)	//如果p是空的话，直接赋值
                {
                    G.vertices[i].firstarc = newNode;	//!!!注意此处不可以用p = newNode因为p不是指向
                    //G.vertices[i].firstarc的指针，只是和它同类的变量
                }else	//若p不为空
                {
                    while(p->nextarc)
                        p = p->nextarc;				//通过循环让p指向第i个顶点的最后1个表结点
                    p->nextarc = newNode;			//同一个顶点的表结点次序可以不同
                }
            }
        }
    }
    return OK;
}

Status ALCreateGraph(ALGraph &G,GraphKind Kind)
{
    G.kind = Kind;
    switch (G.kind)
    {
    case DG:	//构造有向图G
        return ALCreateDG(G);
    case UDG:	//构造无向图G
        return ALCreateUDG(G);
    default:
        return ERROR;
    }
}

int visited[20];				//访问标志数组，未访问是0，访问过是1
Status VisitFunc(ALGraph G,int i)	//函数变量 i的类型是int,意思是输出第i个顶点
{
    printf("V%c  ",G.vertices[i].data);
    return OK;
}

void PrintVertices(ALGraph G)
{
    int i;
    for (i = 0; i < G.vexnum; ++i)
    {
        printf("|V%c|",G.vertices[i].data);
        ArcNode *p = G.vertices[i].firstarc;
        while (p)
        {
            printf("-|-> |%d|",p->adjvex);
            p = p->nextarc;
        }
        printf("^|\n");
    }
}

int FirstAdjVex(ALGraph G,int i)
{
    if(!G.vertices[i].firstarc)
        return -1;
    else
        return G.vertices[i].firstarc->adjvex;
}

int NextAdjVex(ALGraph G,int v,int w)
    //w代表的不是第w个表结点，而是adjvex为w的结点
    //返回第i个头结点（顶点）对应的表结点中adjvex值为w的结点的下一个结点的adjvex值，如果没有返回-1
{
    ArcNode *p = G.vertices[v].firstarc;
    while(p && p->adjvex != w)
    {
        p = p->nextarc;
    }
    if(!p || !p->nextarc)
        return -1;
    return p->nextarc->adjvex;
}

void DFS(ALGraph G,int v)
{   //从第v个顶点出发递归地深度优先遍历图或者网G。
    int w;

    VisitFunc(G,v);	//访问第i个结点
    visited[v] = 1;	//访问过的结点，下标位置标记1

    for(w = FirstAdjVex(G,v); w >= 0; w = NextAdjVex(G,v,w))
        if(!visited[w])//与之邻接且未被访问过的继续访问
            DFS(G,w);
}

void DFSTraverse(ALGraph G,int (* VisitFunc)(ALGraph G, int i))
 {  //对图G作深度优先遍历。
    //使用全局变量VisitFunc，使DFS不必设函数指针参数

    int i;
    for(i = 0; i < G.vexnum; ++i)
        visited[i] = 0;	//访问标志数组初始化
    for(i = 0; i < G.vexnum; ++i)
        if(!visited[i])
            DFS(G,i);	//对尚未访问的顶点调用DFS
}


int main(void)
{
    ALGraph G;
    ALCreateGraph(G,UDG);
    PrintVertices(G);
    printf("\n");
    DFSTraverse(G,VisitFunc);
    printf("\n");


    return 0;
}