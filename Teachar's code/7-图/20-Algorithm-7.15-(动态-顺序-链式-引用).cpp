#include <stdio.h>
#include <stdlib.h>
#define Status int
#define FALSE 0
#define TRUE 1
#define MAX_VERTEX_NUM 20    /* 最大顶点个数 */
typedef int PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef int ShortPathTable[MAX_VERTEX_NUM];


//---图的数组（邻接矩阵）存储表示---
#define	INFINITY INT_MAX	//整型的最大值∞
//实际上 INT_MAX == 2147483647 maximum (signed) int value 
#define MAX_VERTEX_NUM 20	//最大顶点个数
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
typedef struct
{
	VertexType vexs[MAX_VERTEX_NUM];//顶点向量{’1','2','3'...}用来标记矩阵的行列代表那个顶点
	AdjMatrix arcs;					//邻接矩阵
	int vexnum, arcnum;				//图的当前顶点数和弧数
	GraphKind kind;					//图的种类标志
}MGraph;




//VertexType Vex[6] = {'1','2','3','4','5','6'};	//以书上为例'1'代表v1，以此类推
//typedef struct 
//{
//	char v1,v2;
//	int w;
//}VVW;
//VVW vvw[10] = {		//每条边依附顶点及权值
//				{'1','2',5},{'1','4',7},
//				{'2','3',4},
//				{'3','1',8},{'3','6',9},
//				{'4','3',5},{'4','6',6},
//				{'5','4',5},		
//				{'6','1',3},{'6','5',1}
//};	
#define VexNum  6
#define ArcNum  8
VertexType Vex[6] = {'0','1','2','3','4','5'};	//以书上为例'1'代表v1，以此类推
typedef struct 
{
	char v1,v2;
	int w;
}VVW;
VVW vvw[ArcNum] = {		//每条边依附顶点及权值(权值是假设的)
			/*V0*/	{'0','2',10},{'0','4',30},{'0','5',100},
			/*V1*/	{'1','2',5},
			/*V2*/	{'2','3',50},
			/*V3*/	{'3','5',10},
			/*V4*/	{'4','3',20},{'4','5',60}
			/*V5*/	
};




int LocateVex(MGraph G,char v,int vexnum)
{
	int i;
	for (i = 0; i < vexnum; i++)
	{
		if(v == G.vexs[i])
			return i;
	}
	printf("输入顶点有误，定位失败！\n");
	exit(-1);
}

int CreateDN(MGraph &G)
	//采用数组（邻接矩阵）表示法，构造有向网G。
{
	int i, j, k, IncInfo = 0;		//IncInfo为0则各弧不含其它信息
	G.vexnum = VexNum;
	G.arcnum = ArcNum;
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
		i = LocateVex(G,vvw[k].v1,G.vexnum);//确定顶点v1和v2在G.vexs中的位置
		j = LocateVex(G,vvw[k].v2,G.vexnum);
		G.arcs[i][j].adj = vvw[k].w;		//弧<v1,v2>的权值
		if(IncInfo)
			*G.arcs[i][j].info = 0;			//如果弧含有相关信息，则输入
	}
	return 1;
}

int CreateUDN(MGraph &G)
	//采用数组（邻接矩阵）表示法，构造无向网G。
{
	int i, j, k, IncInfo = 0;		//IncInfo为0则各边不含其它信息
	G.vexnum = VexNum;
	G.arcnum = ArcNum;
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
	return 1;
}

int CreateDG(MGraph &G)
	//采用数组（邻接矩阵）表示法，构造有向图G。
{
	int i, j, k, IncInfo = 0;		//IncInfo为0则各弧不含其它信息
	G.vexnum = VexNum;
	G.arcnum = ArcNum;
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
	return 1;
}

int CreateUDG(MGraph &G)
	//采用数组（邻接矩阵）表示法，构造无向图G。
{
	int i, j, k, IncInfo = 0;		//IncInfo为0则各边不含其它信息
	G.vexnum = VexNum;
	G.arcnum = ArcNum;
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
	return 1;
}

int CreateGraph(MGraph &G,GraphKind Kind)
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
		return 0;
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

void ShortestPath_DIJ(MGraph G,int v0,PathMatrix &P,ShortPathTable &D)
 { // 用Dijkstra算法求有向网 G 的 v0 顶点到其余顶点v的最短路径P[v]及带权长度D[v]。
   // 若P[v][w]为TRUE,则 w 是从 v0 到 v 当前求得最短路径上的顶点。  P是存放最短路径的矩阵，经过顶点变成TRUE
   // final[v]为TRUE当且仅当 v∈S,即已经求得从v0到v的最短路径。
   int v,w,i,j,min;
   Status final[MAX_VERTEX_NUM];
   for(v = 0 ;v < G.vexnum ;++v)
   {
     final[v] = FALSE;
     D[v] = G.arcs[v0][v].adj;		//将顶点数组中下标对应是 v0 和 v的距离给了D[v]
     for(w = 0;w < G.vexnum; ++w)
       P[v][w] = FALSE;				//设空路径
     if(D[v] < INFINITY)
     {
       P[v][v0] = TRUE;
       P[v][v] = TRUE;
     }
   }
   D[v0]=0;
   final[v0]= TRUE; /* 初始化,v0顶点属于S集 */
   for(i = 1;i < G.vexnum; ++i) /* 其余G.vexnum-1个顶点 */
   { /* 开始主循环,每次求得v0到某个v顶点的最短路径,并加v到S集 */
     min = INFINITY; /* 当前所知离v0顶点的最近距离 */
     for(w = 0;w < G.vexnum; ++w)
       if(!final[w]) /* w顶点在V-S中 */
	 if(D[w] < min)
	 {
	   v = w;
	   min = D[w];
	 } /* w顶点离v0顶点更近 */
     final[v] = TRUE; /* 离v0顶点最近的v加入S集 */
     for(w = 0;w < G.vexnum; ++w) /* 更新当前最短路径及距离 */
     {
       if(!final[w] && min < INFINITY && G.arcs[v][w].adj < INFINITY && (min + G.arcs[v][w].adj < D[w]))
       { /* 修改D[w]和P[w],w∈V-S */
         D[w] = min + G.arcs[v][w].adj;
         for(j = 0;j < G.vexnum;++j)
           P[w][j] = P[v][j];
         P[w][w] = TRUE;
       }
     }
   }
 }


int main(void)
{
	MGraph G;
	PathMatrix p;
	ShortPathTable d;
	int i, j;
	CreateGraph(G,DN);
	PrintG(G);
	ShortestPath_DIJ(G, 0 ,p, d);
	for(i = 0; i < G.vexnum; ++i)
	{
		if(i != 0)
		{
			if(d[i] != INFINITY)
			{
				printf("V%c --> V%c的最短路径为：%2d ,经过的顶点有：",G.vexs[0],G.vexs[i],d[i]);
				for(j = 0; j < G.vexnum; ++j)
					if((p[i][j] )  )
						printf("V%c ",G.vexs[j]);
				printf("\n");
			}
			else
				printf("V%c --> V%c不存在路径\n",G.vexs[0],G.vexs[i]);
		}
	}

	return 0;
}