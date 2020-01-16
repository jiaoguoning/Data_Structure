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

VertexType Vex[6] = {'1','2','3','4','5','6'};	//������Ϊ��'1'����v1���Դ�����
typedef struct 
{
	char v1,v2;
	int w;
}VVW;
VVW vvw[10] = {		//ÿ�����������㼰Ȩֵ
				{'1','2',5},{'1','4',7},
				{'2','3',4},
				{'3','1',8},{'3','6',9},
				{'4','3',5},{'4','6',6},
				{'5','4',5},		
				{'6','1',3},{'6','5',1}
};	


typedef struct
{
	VertexType vexs[MAX_VERTEX_NUM];//��������{��1','2','3'...}������Ǿ�������д����Ǹ�����
	AdjMatrix arcs;					//�ڽӾ���
	int vexnum, arcnum;				//ͼ�ĵ�ǰ�������ͻ���
	GraphKind kind;					//ͼ�������־
}MGraph;

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
	G.vexnum = 6;
	G.arcnum = 10;
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
			*G.arcs[i][j].info = 0;			//��������������Ϣ��������
	}
	return 1;
}

int CreateUDN(MGraph &G)
	//�������飨�ڽӾ��󣩱�ʾ��������������G��
{
	int i, j, k, IncInfo = 0;		//IncInfoΪ0����߲���������Ϣ
	G.vexnum = 6;
	G.arcnum = 10;
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
	G.vexnum = 6;
	G.arcnum = 10;
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
	G.vexnum = 6;
	G.arcnum = 10;
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

int main(void)
{
	MGraph G;
	CreateGraph(G,DN);
	PrintG(G);
	return 0;
}