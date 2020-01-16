#include <stdio.h>
#include <stdlib.h>

#define Status      int
#define OK          1
#define ERROR       0
#define OVERFLOW    -2
#define FALSE       0
#define TRUE        1

//---图的数组（邻接矩阵）存储表示---
#define	INFINITY INT_MAX	//整型的最大值∞
//实际上 INT_MAX == 2147483647 maximum (signed) int value 
#define MAX_VERTEX_NUM 20	//最大顶点个数
typedef int PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef int ShortPathTable[MAX_VERTEX_NUM];

#define VRType int			//顶点关系类型
#define InfoType int		//弧相关信息类型
#define VertexType char		//顶点向量类型
typedef enum
{
    DG,DN,UDG,UDN			//有向图，有向网，无向图，无向网
}GraphKind;					

typedef struct 
{
    VRType adj;		//VRType是顶点关系类型。对无权图，用1或0表示是否邻接；
    //对有权图，则为权值类型。
    InfoType *info;	//该弧相关信息的指针
} ARCCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

VertexType Vex[6] = {'1','2','3','4','5','6'};	//以书上为例'1'代表v1，以此类推
typedef struct 
{
    char v1,v2;
    int w;
}VVW;
VVW vvw[10] = {		//每条边依附顶点及权值
    {'1','2',5},{'1','4',7},
    {'2','3',4},
    {'3','1',8},{'3','6',9},
    {'4','3',5},{'4','6',6},
    {'5','4',5},		
    {'6','1',3},{'6','5',1}
};	


typedef struct
{
    VertexType vexs[MAX_VERTEX_NUM];//顶点向量{’1','2','3'...}用来标记矩阵的行列代表那个顶点
    AdjMatrix arcs;					//邻接矩阵
    int vexnum, arcnum;				//图的当前顶点数和弧数
    GraphKind kind;					//图的种类标志
}MGraph;

int LocateVex(MGraph G,char v,int vexnum)
{
    int i;
    for (i = 0; i < vexnum; i++)
    {
        if(v == G.vexs[i])
            return i;
    }
    printf("输入顶点有误，定位失败！\n");
    exit(OVERFLOW);
}

Status CreateDN(MGraph &G)
    //采用数组（邻接矩阵）表示法，构造有向网G。
{
    int i, j, k, IncInfo = 0;		//IncInfo为0则各弧不含其它信息
    G.vexnum = 6;
    G.arcnum = 10;
    for(i = 0;i < G.vexnum; ++i)
        G.vexs[i] = Vex[i];			//构造顶点向量
    for(i = 0;i < G.vexnum; ++i)	//初始化邻接矩阵
        for(j = 0; j < G.vexnum; ++j)
        {
            G.arcs[i][j].adj = INFINITY;
            G.arcs[i][j].info = NULL;
        }
        for(k = 0; k < G.arcnum; ++k)	//构造邻接矩阵
        {
            i = LocateVex(G,vvw[k].v1,G.vexnum);//确定v1和v2在G.vexs中的位置
            j = LocateVex(G,vvw[k].v2,G.vexnum);
            G.arcs[i][j].adj = vvw[k].w;		//弧<v1,v2>的权值
            if(IncInfo)
                *G.arcs[i][j].info = 0;			//如果弧含有相关信息，则输入
        }
        return OK;
}

// 算法7.2 
Status CreateUDN(MGraph &G)
    //采用数组（邻接矩阵）表示法，构造无向网G。
{
    int i, j, k, IncInfo = 0;		//IncInfo为0则各边不含其它信息
    G.vexnum = 6;
    G.arcnum = 10;
    for(i = 0;i < G.vexnum; ++i)
        G.vexs[i] = Vex[i];			//构造顶点向量
    for(i = 0;i < G.vexnum; ++i)	//初始化邻接矩阵
        for(j = 0; j < G.vexnum; ++j)
        {
            G.arcs[i][j].adj = INFINITY;
            G.arcs[i][j].info = NULL;
        }
        for(k = 0; k < G.arcnum; ++k)	//构造邻接矩阵
        {
            i = LocateVex(G,vvw[k].v1,G.vexnum);//确定v1和v2在G.vexs中的位置
            j = LocateVex(G,vvw[k].v2,G.vexnum);
            G.arcs[i][j].adj = vvw[k].w;		//边<v1,v2>的权值
            if(IncInfo)
                *G.arcs[i][j].info = 0;			//如果边含有相关信息，则输入
            G.arcs[j][i] = G.arcs[i][j];		//置<v1,v2>的对称弧<v2,v1>
            //因为所给的数据中只给出了单向的数据，没把对称的数据给出
            //所以无向网不存在方向可以利用邻接矩阵对称性，找出对应另一半数据
        }
        return OK;
}

Status CreateDG(MGraph &G)
    //采用数组（邻接矩阵）表示法，构造有向图G。
{
    int i, j, k, IncInfo = 0;		//IncInfo为0则各弧不含其它信息
    G.vexnum = 6;
    G.arcnum = 10;
    for(i = 0;i < G.vexnum; ++i)
        G.vexs[i] = Vex[i];			//构造顶点向量
    for(i = 0;i < G.vexnum; ++i)	//初始化邻接矩阵
        for(j = 0; j < G.vexnum; ++j)
        {
            G.arcs[i][j].adj = 0;	
            G.arcs[i][j].info = NULL;
        }
        for(k = 0; k < G.arcnum; ++k)	//构造邻接矩阵
        {
            i = LocateVex(G,vvw[k].v1,G.vexnum);//确定v1和v2在G.vexs中的位置
            j = LocateVex(G,vvw[k].v2,G.vexnum);
            G.arcs[i][j].adj = 1;		//弧<v1,v2>的权值都是1
            if(IncInfo)
                *G.arcs[i][j].info = 0;			//如果弧含有相关信息，则输入
        }
        return OK;
}

Status CreateUDG(MGraph &G)
    //采用数组（邻接矩阵）表示法，构造无向图G。
{
    int i, j, k, IncInfo = 0;		//IncInfo为0则各边不含其它信息
    G.vexnum = 6;
    G.arcnum = 10;
    for(i = 0;i < G.vexnum; ++i)
        G.vexs[i] = Vex[i];			//构造顶点向量
    for(i = 0;i < G.vexnum; ++i)	//初始化邻接矩阵
        for(j = 0; j < G.vexnum; ++j)
        {
            G.arcs[i][j].adj = 0;
            G.arcs[i][j].info = NULL;
        }
        for(k = 0; k < G.arcnum; ++k)	//构造邻接矩阵
        {
            i = LocateVex(G,vvw[k].v1,G.vexnum);//确定v1和v2在G.vexs中的位置
            j = LocateVex(G,vvw[k].v2,G.vexnum);
            G.arcs[i][j].adj = 1;				//边<v1,v2>的权值是1
            if(IncInfo)
                *G.arcs[i][j].info = 0;			//如果边含有相关信息，则输入
            G.arcs[j][i] = G.arcs[i][j];		//置<v1,v2>的对称弧<v2,v1>
            //因为所给的数据中只给出了单向的数据，没把对称的数据给出
            //所以无向网不存在方向可以利用邻接矩阵对称性，找出对应另一半数据

        }
        return OK;
}


// 算法7.1  
Status CreateGraph(MGraph &G,GraphKind Kind)
{
    G.kind = Kind;
    switch (G.kind)
    {
    case DG:	//构造有向图G
        return CreateDG(G);
    case DN:	//构造有向网G
        return CreateDN(G);
    case UDG:	//构造无向图G
        return CreateUDG(G);
    case UDN:	//构造无向网G
        return CreateUDN(G);
    default:
        return ERROR;
    }

}

void PrintG(MGraph G)
{
    int i , j;
    printf("%4d\n",G.kind);
    for(i = 0;i < G.vexnum; ++i)
    {
        for(j = 0; j < G.vexnum; ++j)
        {
            if(G.arcs[i][j].adj == INFINITY) 
                printf(" %c  ",'-');
            else
                printf(" %d  ",G.arcs[i][j].adj);
        }
        printf("\n");
    }
}


int main(void)
{
    MGraph G;
	

    CreateGraph(G,DN);
    PrintG(G);
  

    return 0;
}