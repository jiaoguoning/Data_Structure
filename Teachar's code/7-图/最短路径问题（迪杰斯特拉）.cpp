#include <stdio.h>
#include <stdlib.h>
#define Status int
#define FALSE 0
#define TRUE 1
#define MAX_VERTEX_NUM 20    /* ��󶥵���� */
typedef int PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef int ShortPathTable[MAX_VERTEX_NUM];


//---ͼ�����飨�ڽӾ��󣩴洢��ʾ---
#define	INFINITY INT_MAX	//���͵����ֵ��
//ʵ���� INT_MAX == 2147483647 maximum (signed) int value 
#define MAX_VERTEX_NUM 20	//��󶥵����
#define VRType int			//�����ϵ����
#define InfoType int		//�������Ϣ����
#define VertexType char		//������������
typedef enum
{
	DG,DN,UDG,UDN			//����ͼ��������������ͼ��������
}GraphKind;					

typedef struct 
{
	VRType adj;		//VRType�Ƕ����ϵ���͡�����Ȩͼ����1��0��ʾ�Ƿ��ڽӣ�
					//����Ȩͼ����ΪȨֵ���͡�
	InfoType *info;	//�û������Ϣ��ָ��
} ARCCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct
{
	VertexType vexs[MAX_VERTEX_NUM];//��������{��1','2','3'...}������Ǿ�������д����Ǹ�����
	AdjMatrix arcs;					//�ڽӾ���
	int vexnum, arcnum;				//ͼ�ĵ�ǰ�������ͻ���
	GraphKind kind;					//ͼ�������־
}MGraph;




//VertexType Vex[6] = {'1','2','3','4','5','6'};	//������Ϊ��'1'����v1���Դ�����
//typedef struct 
//{
//	char v1,v2;
//	int w;
//}VVW;
//VVW vvw[10] = {		//ÿ�����������㼰Ȩֵ
//				{'1','2',5},{'1','4',7},
//				{'2','3',4},
//				{'3','1',8},{'3','6',9},
//				{'4','3',5},{'4','6',6},
//				{'5','4',5},		
//				{'6','1',3},{'6','5',1}
//};	
#define VexNum  6
#define ArcNum  8
VertexType Vex[6] = {'0','1','2','3','4','5'};	//������Ϊ��'1'����v1���Դ�����
typedef struct 
{
	char v1,v2;
	int w;
}VVW;
VVW vvw[ArcNum] = {		//ÿ�����������㼰Ȩֵ(Ȩֵ�Ǽ����)
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
	printf("���붥�����󣬶�λʧ�ܣ�\n");
	exit(-1);
}

int CreateDN(MGraph &G)
	//�������飨�ڽӾ��󣩱�ʾ��������������G��
{
	int i, j, k, IncInfo = 0;		//IncInfoΪ0���������������Ϣ
	G.vexnum = VexNum;
	G.arcnum = ArcNum;
	for(i = 0;i < G.vexnum; ++i)
		G.vexs[i] = Vex[i];			//���춥������
	for(i = 0;i < G.vexnum; ++i)	//��ʼ���ڽӾ���
		for(j = 0; j < G.vexnum; ++j)
		{
			G.arcs[i][j].adj = INFINITY;
			G.arcs[i][j].info = NULL;
		}
	for(k = 0; k < G.arcnum; ++k)	//�����ڽӾ���
	{
		i = LocateVex(G,vvw[k].v1,G.vexnum);//ȷ������v1��v2��G.vexs�е�λ��
		j = LocateVex(G,vvw[k].v2,G.vexnum);
		G.arcs[i][j].adj = vvw[k].w;		//��<v1,v2>��Ȩֵ
		if(IncInfo)
			*G.arcs[i][j].info = 0;			//��������������Ϣ��������
	}
	return 1;
}

int CreateUDN(MGraph &G)
	//�������飨�ڽӾ��󣩱�ʾ��������������G��
{
	int i, j, k, IncInfo = 0;		//IncInfoΪ0����߲���������Ϣ
	G.vexnum = VexNum;
	G.arcnum = ArcNum;
	for(i = 0;i < G.vexnum; ++i)
		G.vexs[i] = Vex[i];			//���춥������
	for(i = 0;i < G.vexnum; ++i)	//��ʼ���ڽӾ���
		for(j = 0; j < G.vexnum; ++j)
		{
			G.arcs[i][j].adj = INFINITY;
			G.arcs[i][j].info = NULL;
		}
	for(k = 0; k < G.arcnum; ++k)	//�����ڽӾ���
	{
		i = LocateVex(G,vvw[k].v1,G.vexnum);//ȷ��v1��v2��G.vexs�е�λ��
		j = LocateVex(G,vvw[k].v2,G.vexnum);
		G.arcs[i][j].adj = vvw[k].w;		//��<v1,v2>��Ȩֵ
		if(IncInfo)
			*G.arcs[i][j].info = 0;			//����ߺ��������Ϣ��������
		G.arcs[j][i] = G.arcs[i][j];		//��<v1,v2>�ĶԳƻ�<v2,v1>
											//��Ϊ������������ֻ�����˵�������ݣ�û�ѶԳƵ����ݸ���
											//���������������ڷ�����������ڽӾ���Գ��ԣ��ҳ���Ӧ��һ������
											
	}
	return 1;
}

int CreateDG(MGraph &G)
	//�������飨�ڽӾ��󣩱�ʾ������������ͼG��
{
	int i, j, k, IncInfo = 0;		//IncInfoΪ0���������������Ϣ
	G.vexnum = VexNum;
	G.arcnum = ArcNum;
	for(i = 0;i < G.vexnum; ++i)
		G.vexs[i] = Vex[i];			//���춥������
	for(i = 0;i < G.vexnum; ++i)	//��ʼ���ڽӾ���
		for(j = 0; j < G.vexnum; ++j)
		{
			G.arcs[i][j].adj = 0;	
			G.arcs[i][j].info = NULL;
		}
	for(k = 0; k < G.arcnum; ++k)	//�����ڽӾ���
	{
		i = LocateVex(G,vvw[k].v1,G.vexnum);//ȷ��v1��v2��G.vexs�е�λ��
		j = LocateVex(G,vvw[k].v2,G.vexnum);
		G.arcs[i][j].adj = 1;		//��<v1,v2>��Ȩֵ����1
		if(IncInfo)
			*G.arcs[i][j].info = 0;			//��������������Ϣ��������
	}
	return 1;
}

int CreateUDG(MGraph &G)
	//�������飨�ڽӾ��󣩱�ʾ������������ͼG��
{
	int i, j, k, IncInfo = 0;		//IncInfoΪ0����߲���������Ϣ
	G.vexnum = VexNum;
	G.arcnum = ArcNum;
	for(i = 0;i < G.vexnum; ++i)
		G.vexs[i] = Vex[i];			//���춥������
	for(i = 0;i < G.vexnum; ++i)	//��ʼ���ڽӾ���
		for(j = 0; j < G.vexnum; ++j)
		{
			G.arcs[i][j].adj = 0;
			G.arcs[i][j].info = NULL;
		}
	for(k = 0; k < G.arcnum; ++k)	//�����ڽӾ���
	{
		i = LocateVex(G,vvw[k].v1,G.vexnum);//ȷ��v1��v2��G.vexs�е�λ��
		j = LocateVex(G,vvw[k].v2,G.vexnum);
		G.arcs[i][j].adj = 1;				//��<v1,v2>��Ȩֵ��1
		if(IncInfo)
			*G.arcs[i][j].info = 0;			//����ߺ��������Ϣ��������
		G.arcs[j][i] = G.arcs[i][j];		//��<v1,v2>�ĶԳƻ�<v2,v1>
											//��Ϊ������������ֻ�����˵�������ݣ�û�ѶԳƵ����ݸ���
											//���������������ڷ�����������ڽӾ���Գ��ԣ��ҳ���Ӧ��һ������
											
	}
	return 1;
}

int CreateGraph(MGraph &G,GraphKind Kind)
{
	G.kind = Kind;
	switch (G.kind)
	{
	case DG:	//��������ͼG
		return CreateDG(G);
	case DN:	//����������G
		return CreateDN(G);
	case UDG:	//��������ͼG
		return CreateUDG(G);
	case UDN:	//����������G
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
 { // ��Dijkstra�㷨�������� G �� v0 ���㵽���ඥ��v�����·��P[v]����Ȩ����D[v]��
   // ��P[v][w]ΪTRUE,�� w �Ǵ� v0 �� v ��ǰ������·���ϵĶ��㡣  P�Ǵ�����·���ľ��󣬾���������TRUE
   // final[v]ΪTRUE���ҽ��� v��S,���Ѿ���ô�v0��v�����·����
   int v,w,i,j,min;
   Status final[MAX_VERTEX_NUM];
   for(v = 0 ;v < G.vexnum ;++v)
   {
     final[v] = FALSE;
     D[v] = G.arcs[v0][v].adj;		//�������������±��Ӧ�� v0 �� v�ľ������D[v]
     for(w = 0;w < G.vexnum; ++w)
       P[v][w] = FALSE;				//���·��
     if(D[v] < INFINITY)
     {
       P[v][v0] = TRUE;
       P[v][v] = TRUE;
     }
   }
   D[v0]=0;
   final[v0]= TRUE; /* ��ʼ��,v0��������S�� */
   for(i = 1;i < G.vexnum; ++i) /* ����G.vexnum-1������ */
   { /* ��ʼ��ѭ��,ÿ�����v0��ĳ��v��������·��,����v��S�� */
     min = INFINITY; /* ��ǰ��֪��v0������������ */
     for(w = 0;w < G.vexnum; ++w)
       if(!final[w]) /* w������V-S�� */
	 if(D[w] < min)
	 {
	   v = w;
	   min = D[w];
	 } /* w������v0������� */
     final[v] = TRUE; /* ��v0���������v����S�� */
     for(w = 0;w < G.vexnum; ++w) /* ���µ�ǰ���·�������� */
     {
       if(!final[w] && min < INFINITY && G.arcs[v][w].adj < INFINITY && (min + G.arcs[v][w].adj < D[w]))
       { /* �޸�D[w]��P[w],w��V-S */
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
				printf("V%c --> V%c�����·��Ϊ��%2d ,�����Ķ����У�",G.vexs[0],G.vexs[i],d[i]);
				for(j = 0; j < G.vexnum; ++j)
					if((p[i][j] )  )
						printf("V%c ",G.vexs[j]);
				printf("\n");
			}
			else
				printf("V%c --> V%c������·��\n",G.vexs[0],G.vexs[i]);
		}
	}

	return 0;
}