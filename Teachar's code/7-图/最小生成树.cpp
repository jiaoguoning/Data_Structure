#include <stdio.h>
#include <stdlib.h>

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

#define VexNum  6
#define ArcNum  10
VertexType Vex[6] = {'1','2','3','4','5','6'};	//以书上为例'1'代表v1，以此类推
typedef struct 
{
	char v1,v2;
	int w;
}VVW;
VVW vvw[10] = {		//每条边依附顶点及权值(权值是假设的)
			/*V1*/	{'1','2',6},{'1','3',1},{'1','4',5},
			/*V2*/	{'2','3',5},
			/*V3*/	{'3','4',5},
			/*V4*/	{'4','6',2},
			/*V5*/	{'5','2',3},{'5','3',6},
			/*V6*/	{'6','5',6},{'6','3',4}
};


typedef struct
{
	VertexType vexs[MAX_VERTEX_NUM];//顶点向量{’1','2','3'...}用来标记矩阵的行列代表那个顶点
	AdjMatrix arcs;					//邻接矩阵
	int vexnum, arcnum;				//图的当前顶点数和弧数
	GraphKind kind;					//图的种类标志
}MGraph;

typedef struct
{
	VertexType adjvex;		//最小生成树中顶点名字，如：v1
	VRType lowcost;			//最小生成树顶点间的权值
}Closedge[MAX_VERTEX_NUM];	//该数组存放最小生成树的结构类型
Closedge closedge;


int LocateVex(MGraph G,char v)
{
	int i;
	for (i = 0; i < G.vexnum; i++)
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
		i = LocateVex(G,vvw[k].v1);//确定顶点v1和v2在G.vexs中的位置
		j = LocateVex(G,vvw[k].v2);
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
		i = LocateVex(G,vvw[k].v1);//确定v1和v2在G.vexs中的位置
		j = LocateVex(G,vvw[k].v2);
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
		i = LocateVex(G,vvw[k].v1);//确定v1和v2在G.vexs中的位置
		j = LocateVex(G,vvw[k].v2);
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
		i = LocateVex(G,vvw[k].v1);//确定v1和v2在G.vexs中的位置
		j = LocateVex(G,vvw[k].v2);
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

int minimum(int vexnum,Closedge closedge)
	//获取除当前顶点的最小值
{
	int j, r ,min = INFINITY;
	for(j = 0; j < vexnum; ++j)
		if(closedge[j].lowcost <= min && closedge[j].lowcost != 0)
		{
			min = closedge[j].lowcost;
			r = j;
		}
	return r;
}

void PrintMiniTree_PRIM(MGraph G,Closedge closedge,int k)
{
	printf("V%c --%1d--> V%c",closedge[k].adjvex,closedge[k].lowcost,G.vexs[k]);
	printf("\n");
}

void PrintClosedge(Closedge closedge,int vexnum)
{
	//int j;
	//printf("|");
	//for(j = 0; j < vexnum; ++j)
	//	printf("(%d,%2d) ",j,closedge[j].lowcost);
	//printf("|\n");
}

void MiniSpanTree_PRIM(MGraph G,VertexType u)
	//用普里姆算法从第u个顶点出发构造网G的最小生成树T，输出T的各条边。
	//记录从顶点集U到V-U的代价最小的边的辅助数组定义；
	//closedge[j].lowcost表示在集合U中顶点与第j个顶点对应最小权值
{
	int k, j, i;
	k = LocateVex(G,u);
	for (j = 0; j < G.vexnum; ++j)	//辅助数组的初始化
		if(j != k)
		{
			closedge[j].adjvex = u;
			closedge[j].lowcost = G.arcs[k][j].adj;	//获取邻接矩阵第k行所有元素赋给closedge[j!= k].lowcost
		}
	closedge[k].lowcost = 0;		//初始，U = {u};   !!!决定了此网中边的权值不能为0
									//因为如果是0，则表明已经被放入U集合中了
	PrintClosedge(closedge,G.vexnum);
	for (i = 1; i < G.vexnum; ++i)	//选择其余G.vexnum-1个顶点，因此i从1开始循环
	{
		k = minimum(G.vexnum,closedge);		//求出最小生成树的下一个结点：第k顶点
		PrintMiniTree_PRIM(G, closedge, k); //输出生成树的边
		closedge[k].lowcost = 0;			//第k顶点并入U集
		PrintClosedge(closedge,G.vexnum);
		for(j = 0;j < G.vexnum; ++j)
		{                                               //closedge[j].lowcost表示在集合U中顶点与第j个顶点对应最小权值
			if(G.arcs[k][j].adj < closedge[j].lowcost)	//比较第k个顶点和第j个顶点权值是否小于closedge[j].lowcost
			{
				closedge[j].adjvex = G.vexs[k];			//替换closedge[j]
				closedge[j].lowcost = G.arcs[k][j].adj;
				PrintClosedge(closedge,G.vexnum);
			}
		}
	}
}

int main(void)
{
	MGraph G;
	CreateGraph(G,UDN);	//创建连通网（无向网）
	PrintG(G);
	MiniSpanTree_PRIM(G, '3');


	return 0;
}