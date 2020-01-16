#include <stdio.h>
#include <stdlib.h>

//---图的邻接表存储表示---
#define MAX_VERTEX_NUM 20
#define InfoType int	//该弧相关信息的指针（假设信息是整数，因此用int类型）
#define VertexType char	//顶点类型（假设每个顶点是一个字符表示）
typedef struct ArcNode//表结点类型
{
	int   adjvex;				//该弧指向顶点位置 0,1,2,3...
								//这个位置指的是邻接的顶点在表头数组中的位置
	struct ArcNode * nextarc;	//指向下一条弧的指针
	InfoType *info;				//该弧相关信息的指针
}ArcNode;

typedef struct VNode//头结点类型
{
	VertexType data;	//顶点信息（VertexType实际上是顶点类型）
	ArcNode *firstarc;	//指向第一条依附该顶点的弧的指针
}VNode, AdjList[MAX_VERTEX_NUM];

typedef struct		//邻接表类型
{
	AdjList vertices;	
	int vexnum, arcnum;	//图的顶点数和弧数
	int kind;			//图的类型标志
}ALGraph;


//---有向图的十字链表存储表示---
typedef struct ArcBox	//弧结点的结构
{
	int tailvex, headvex;		//该弧的尾和头顶点的位置
	struct ArcBox *hlink,*tlink;//分别为弧头相同和弧尾相同的弧的链域
	InfoType *info;				//该弧相关信息的指针
}ArcBox;

typedef struct VexNode	//顶点结点结构
{
	VertexType data;			//顶点信息（VertexType实际上是顶点类型）
	ArcBox *firstin, *firstout;	//分别指向该顶点第一条入弧和出弧
}VexNode;

typedef struct			//十字链表结构
{
	VexNode xlist[MAX_VERTEX_NUM];//表头向量
	int vexnum, arcnum;			  //有向图的当前顶点数和弧数
}OLGraph;

//---无向图的邻接多重表存储表示---
typedef enum
{
	unvisited, visited
} VisitIf;

typedef struct EBox		//边结点的结构
{
	VisitIf mark;				//访问标记
	int ivex, jvex;				//该边依附的两个顶点的位置
	struct EBox *ilink, *jlink;	//分别指向依附这两个顶点的下一条边
	InfoType *info;				//该边信息指针
}EBox;

typedef struct VexBox	//顶点结点的结构
{
	VertexType data;
	EBox *firstedge;			//指向第一条依附该顶点的边
}VexBox;

typedef struct			//邻接多重表结构
{
	VexBox adjmulist[MAX_VERTEX_NUM];
	int vexnum, adgenum;		//无向图的当前顶点数和边数
}AMLGraph;