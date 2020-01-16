#include <stdio.h>
#include <stdlib.h>

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

#define VexNum  6
#define ArcNum  10
VertexType Vex[6] = {'1','2','3','4','5','6'};	//������Ϊ��'1'����v1���Դ�����
typedef struct 
{
	char v1,v2;
	int w;
}VVW;
VVW vvw[10] = {		//ÿ�����������㼰Ȩֵ(Ȩֵ�Ǽ����)
			/*V1*/	{'1','2',6},{'1','3',1},{'1','4',5},
			/*V2*/	{'2','3',5},
			/*V3*/	{'3','4',5},
			/*V4*/	{'4','6',2},
			/*V5*/	{'5','2',3},{'5','3',6},
			/*V6*/	{'6','5',6},{'6','3',4}
};


typedef struct
{
	VertexType vexs[MAX_VERTEX_NUM];//��������{��1','2','3'...}������Ǿ�������д����Ǹ�����
	AdjMatrix arcs;					//�ڽӾ���
	int vexnum, arcnum;				//ͼ�ĵ�ǰ�������ͻ���
	GraphKind kind;					//ͼ�������־
}MGraph;

typedef struct
{
	VertexType adjvex;		//��С�������ж������֣��磺v1
	VRType lowcost;			//��С������������Ȩֵ
}Closedge[MAX_VERTEX_NUM];	//����������С�������Ľṹ����
Closedge closedge;


int LocateVex(MGraph G,char v)
{
	int i;
	for (i = 0; i < G.vexnum; i++)
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
		i = LocateVex(G,vvw[k].v1);//ȷ������v1��v2��G.vexs�е�λ��
		j = LocateVex(G,vvw[k].v2);
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
		i = LocateVex(G,vvw[k].v1);//ȷ��v1��v2��G.vexs�е�λ��
		j = LocateVex(G,vvw[k].v2);
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
		i = LocateVex(G,vvw[k].v1);//ȷ��v1��v2��G.vexs�е�λ��
		j = LocateVex(G,vvw[k].v2);
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
		i = LocateVex(G,vvw[k].v1);//ȷ��v1��v2��G.vexs�е�λ��
		j = LocateVex(G,vvw[k].v2);
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

int minimum(int vexnum,Closedge closedge)
	//��ȡ����ǰ�������Сֵ
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
	//������ķ�㷨�ӵ�u���������������G����С������T�����T�ĸ����ߡ�
	//��¼�Ӷ��㼯U��V-U�Ĵ�����С�ıߵĸ������鶨�壻
	//closedge[j].lowcost��ʾ�ڼ���U�ж������j�������Ӧ��СȨֵ
{
	int k, j, i;
	k = LocateVex(G,u);
	for (j = 0; j < G.vexnum; ++j)	//��������ĳ�ʼ��
		if(j != k)
		{
			closedge[j].adjvex = u;
			closedge[j].lowcost = G.arcs[k][j].adj;	//��ȡ�ڽӾ����k������Ԫ�ظ���closedge[j!= k].lowcost
		}
	closedge[k].lowcost = 0;		//��ʼ��U = {u};   !!!�����˴����бߵ�Ȩֵ����Ϊ0
									//��Ϊ�����0��������Ѿ�������U��������
	PrintClosedge(closedge,G.vexnum);
	for (i = 1; i < G.vexnum; ++i)	//ѡ������G.vexnum-1�����㣬���i��1��ʼѭ��
	{
		k = minimum(G.vexnum,closedge);		//�����С����������һ����㣺��k����
		PrintMiniTree_PRIM(G, closedge, k); //����������ı�
		closedge[k].lowcost = 0;			//��k���㲢��U��
		PrintClosedge(closedge,G.vexnum);
		for(j = 0;j < G.vexnum; ++j)
		{                                               //closedge[j].lowcost��ʾ�ڼ���U�ж������j�������Ӧ��СȨֵ
			if(G.arcs[k][j].adj < closedge[j].lowcost)	//�Ƚϵ�k������͵�j������Ȩֵ�Ƿ�С��closedge[j].lowcost
			{
				closedge[j].adjvex = G.vexs[k];			//�滻closedge[j]
				closedge[j].lowcost = G.arcs[k][j].adj;
				PrintClosedge(closedge,G.vexnum);
			}
		}
	}
}

int main(void)
{
	MGraph G;
	CreateGraph(G,UDN);	//������ͨ������������
	PrintG(G);
	MiniSpanTree_PRIM(G, '3');


	return 0;
}