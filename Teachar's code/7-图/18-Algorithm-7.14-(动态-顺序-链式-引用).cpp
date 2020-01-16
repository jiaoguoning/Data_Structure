#include <stdio.h>
#include <stdlib.h>

//---图的邻接表存储表示---
#define MAX_VERTEX_NUM 20
#define InfoType int	//该弧相关信息的指针（假设信息是整数，因此用int类型）
#define VertexType char	//顶点类型（假设每个顶点是一个字符表示）

typedef enum
{
	DG,DN,UDG,UDN			//有向图，有向网，无向图，无向网
}GraphKind;		

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
	int vexnum;	//图的顶点数
	int arcnum;	//图的弧数
	GraphKind kind;			//图的类型标志
}ALGraph;


VertexType Vex[9] = {'1','2','3','4','5','6','7','8','9'};	//以书上为例'1'代表v1，以此类推
typedef struct 
{
	char v1,v2;
	int w;
}VVW;
VVW vvw[11] = {		//每条边依附顶点及权值(权值是假设的)
			/*V1*/	{'1','2',6},{'1','3',4},{'1','4',5},
			/*V2*/	{'2','5',1},
			/*V3*/	{'3','5',1},
			/*V4*/	{'4','6',2},
			/*V5*/	{'5','7',9},{'5','8',7},
			/*V6*/	{'6','8',4},
			/*V7*/	{'7','9',2},
			/*V8*/	{'8','9',4}
};

#define VexNum  9
#define ArcNum  11

int LocateVex(ALGraph G,char v,int vexnum)
{
	int i;
	for (i = 0; i < vexnum; i++)
	{
		if(v == G.vertices[i].data)
			return i;
	}
	printf("输入顶点有误，定位失败！\n");
	exit(-1);
}

int ALCreateDG(ALGraph &G)	//！！！！注意：在同一个顶点表结点链表中，表结点次序可以不同
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
	return 1;
}

int ALCreateDN(ALGraph &G)
	//采用数组（邻接矩阵）表示法，构造有向网G。
{
	int i, k, IncInfo = 0;		//IncInfo为0则各弧不含其它信息
	G.vexnum = VexNum;
	G.arcnum = ArcNum;
	for(i = 0;i < G.vexnum; ++i)
	{
		G.vertices[i].data = Vex[i];	//构造顶点向量
		G.vertices[i].firstarc = NULL;
	}
	for(i = 0;i < G.vexnum; ++i)	//遍历邻接表各个顶点，依次创建表结点
	{		

		for(k = 0; k < G.arcnum; ++k)	//构造邻接矩阵
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
	return 1;
}

int ALCreateGraph(ALGraph &G,GraphKind Kind)
{
	G.kind = Kind;
	switch (G.kind)
	{
	case DN:	//构造有向网G
		return ALCreateDN(G);
	default:
		return 0;
	}
}

int VisitFunc(ALGraph G,int i)	//函数变量 i的类型是int,意思是输出第i个顶点
{
	printf("V%c  ",G.vertices[i].data);
	return 1;
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
			 printf("-|->|%d|",p->adjvex);
			 p = p->nextarc;
		 }
		 printf("^|\n");
	}
}

//------------ 栈 的 操 作 --------------//
#define STACK_INIT_SIZE 20
#define STACKINCREMENT 5
#define ElemType int
typedef struct {
	ElemType *base;
	ElemType *top;
	int stacksize;
}SqStack;

//因为要修改栈S内存中数据成员的值，因此必须传递S的地址
int InitStack(SqStack *S)
{
	S->base = (ElemType*)malloc(sizeof(ElemType) * STACK_INIT_SIZE);
	if (!S->base)
	{
		printf("初始化失败！\n");
		return 0;
	}
	S->top = S->base;
	S->stacksize = STACK_INIT_SIZE;
	return 1;
}

void PrintStack(SqStack S)
{
	ElemType *p = S.base;
	printf("\n||");
	while(p < S.top)
	{
		printf(" %d ",*p);
		++p;
	}
	printf(" ||\n");
}

int push(SqStack *S,ElemType e)
{
	if ((S->top - S->base) >= S->stacksize)
	{
		S->base = (ElemType *)realloc(S->base,S->stacksize+STACKINCREMENT);
		if (!S->base)
		{
			printf("追加失败!\n");
			return 0;
		}
		S->top = S->base + S->stacksize;
		S->stacksize += STACKINCREMENT;
	}
	*S->top++ = e;
	// PrintStack(*S);
	return 1;
}

int pop(SqStack *S,ElemType *e)
{
	if (S->top == S->base)
	{
		printf("出栈失败，栈为空!\n");
		return 0;
	}
	*e = *--S->top;
	// PrintStack(*S);
	return 1;
}

int GetTop(SqStack S,ElemType *e)
{
	if(S.base == S.top)
		return 0;
	*e = *(S.top - 1);
	return 1;
}


//--------------------------------------//



int FindOutDegree(ALGraph G,int *indegree)
{
	int i,ind = 0;
	for(i = 0; i < G.vexnum; ++i)
	{
		 ArcNode *p = G.vertices[i].firstarc;
		 while (p)
		 {
			 p = p->nextarc;
			 ++ind;
		 }
		 indegree[i] = ind;
	}
	return 1;
}

int FindInDegree(ALGraph G,int *indegree)
{
	int i, k ;
	for(k = 0; k < G.vexnum; ++k)
	{
		int ind = 0;
		for(i = 0; i < G.vexnum; ++i)
		{
			ArcNode *p = G.vertices[i].firstarc;
			while (p)
			{
				int kkk = LocateVex(G,G.vertices[k].data,G.vexnum);
				if(p->adjvex == LocateVex(G,G.vertices[k].data,G.vexnum))
					++ind;
				p = p->nextarc;
			}

		}
		indegree[k] = ind;
	}
	return 1;
}

int TopologicalSort(ALGraph G)
	//有向图G采用邻接表存储结构。
	//若G无回路，则输出G的顶点的一个拓扑序列并返回1，否则返回0.
	//输出次序按照栈的后进先出原则，删除顶点，输出遍历
{
	SqStack S;
	int i, count;
	int *indegree1 = (int *)malloc(sizeof(int) * G.vexnum);
	int indegree[12] = {0};
	FindInDegree(G, indegree);	//求个顶点的入度下标从0开始
	InitStack(&S);
	//PrintStack(S);
	for(i = 0; i < G.vexnum; ++i)
		if(!indegree[i])	//建0入度顶点栈S
			push(&S,i);		//入度为0者进栈
	count = 0;				//对输出顶点计数
	while (S.base != S.top)
	{
		ArcNode* p;
		pop(&S,&i);
		VisitFunc(G,i);			//第i个输出栈顶元素对应的顶点，也就是最后进来的顶点	
		++count;				//输出i号顶点并计数
		for(p = G.vertices[i].firstarc; p; p = p->nextarc)
		{	//通过循环遍历第i个顶点的表结点，将表结点中入度都减1
			int k = p->adjvex;	//对i号顶点的每个邻接点的入度减1
			if(!(--indegree[k]))
				push(&S,k);		//若入度减为0，则入栈
		}//for
	}//while
	if(count < G.vexnum)
	{
		printf("\n该有向图有回路!\n");
		return 0;	//该有向图有回路
	}
	else
	{
		printf("\n该有向图没有回路!\n");
		return 1;
	}
}
int ve[VexNum];
int TopologicalOrder(ALGraph G, SqStack &T)
	//有向网G采用邻接表存储结构，求各顶点时间的最早发生时间ve（全局变量）
	//T为拓扑序列顶点栈，S为零入度顶点栈。
	//若G无回路，则用栈T返回G的一个拓扑序列，且函数值为OK，否则为ERROR
{
	int i,j;
	int indegree[VexNum] = {0};
	FindInDegree(G, indegree);	//求个顶点的入度下标从0开始
	//建零入度顶点栈S；
	SqStack S;
	InitStack(&S);

	for(i = 0; i < G.vexnum; ++i)
		if(!indegree[i])	//建0入度顶点栈S
			push(&S,i);		//入度为0者进栈
	InitStack(&T);	int count = 0;
	while (S.base != S.top)
	{
		ArcNode* p;
		pop(&S, &j);	push(&T, j);
		VisitFunc(G,j);			//第i个输出栈顶元素对应的顶点，也就是最后进来的顶点	
		++count;				//输出i号顶点并计数
		for(p = G.vertices[j].firstarc; p; p = p->nextarc)
		{	//通过循环遍历第i个顶点的表结点，将表结点中入度都减1
			int k = p->adjvex;	//对i号顶点的每个邻接点的入度减1
			if(!(--indegree[k]))
				push(&S,k);		//若入度减为0，则入栈
			if(ve[j] + *(p->info) > ve[k])
				ve[k] = ve[j] + *(p->info);
		}//for  *(p->info) = dut(<j, k>)
	}//while
	if(count < G.vexnum)
	{
		printf("\n该有向图有回路!\n");
		return 0;	//该有向图有回路
	}
	else
	{
		printf("\n该有向图没有回路!\n");
		return 1;
	}

}
void PrintCriticalActivity(ALGraph G,int j,int k,int dut,int ee,int el,char tag)
{
	if(tag == '*')
		printf("关键路径：V%c --> V%c ,活动时间：%d ,最早开始：%2d,最晚开始：%2d\n",G.vertices[j].data,
							G.vertices[k].data,dut,ee,el);
	else
		printf("一般路径：V%c --> V%c ,活动区间：%d ,最早开始：%2d,最晚开始：%2d\n",G.vertices[j].data,
							G.vertices[k].data,dut,ee,el);
}
int CriticalPath(ALGraph G)
{	//因为G是有向网，输出G的各项关键活动
	SqStack T;
	int i, j;	ArcNode* p;
	int k , dut;
	if(!TopologicalOrder(G,T))
		return 0;
	int vl[VexNum];
	for (i = 0; i < VexNum; i++)
		vl[i] = ve[VexNum - 1];		//初始化顶点事件的最迟发生时间
	while (T.base != T.top)			//按拓扑逆序求各顶点的vl值
	{
		
		for(pop(&T, &j), p = G.vertices[j].firstarc; p; p = p->nextarc)
		{
			k = p->adjvex;	dut = *(p->info);	//dut<j, k>
			if(vl[k] - dut < vl[j])
				vl[j] = vl[k] - dut;
		}//for
	}//while
	for(j = 0; j < G.vexnum; ++j)	//求ee,el和关键活动
	{
		for (p = G.vertices[j].firstarc; p; p = p->nextarc)
		{
			int ee, el;		char tag;
			k = p->adjvex;	dut = *(p->info);
			ee = ve[j];	el = vl[k] - dut;
			tag = (ee == el) ? '*' : ' ';
			PrintCriticalActivity(G,j,k,dut,ee,el,tag);
		}
	}
	return 1;
}

int main(void)
{
	ALGraph G;
	SqStack T;
	ALCreateGraph(G,DN);
	PrintVertices(G);
	TopologicalOrder(G,T);
	PrintStack(T);
	CriticalPath(G);

	return 0;
}


