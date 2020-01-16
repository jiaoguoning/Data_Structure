#include <stdio.h>
#include <stdlib.h>

#define Status      int
#define OK          1
#define ERROR       0
#define OVERFLOW    -2
#define FALSE       0
#define TRUE        1

//---ͼ�����飨�ڽӾ��󣩴洢��ʾ---
#define	INFINITY INT_MAX	//���͵����ֵ��
//ʵ���� INT_MAX == 2147483647 maximum (signed) int value 
#define MAX_VERTEX_NUM 20	//��󶥵����
typedef int PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef int ShortPathTable[MAX_VERTEX_NUM];

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


VertexType Vex[8] = {'1','2','3','4','5','6','7','8'};	//������Ϊ��'1'����v1���Դ�����
typedef struct  {
    char v1,v2;
    int w;
}VVW;
VVW vvw[9] = {		//ÿ�����������㼰Ȩֵ(Ȩֵ�Ǽ����)
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
    exit(OVERFLOW);
}

Status CreateDN(MGraph &G)
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
            i = LocateVex(G,vvw[k].v1,G.vexnum);//ȷ��v1��v2��G.vexs�е�λ��
            j = LocateVex(G,vvw[k].v2,G.vexnum);
            G.arcs[i][j].adj = vvw[k].w;		//��<v1,v2>��Ȩֵ
            if(IncInfo)
                *G.arcs[i][j].info = 0;			//��������������Ϣ��������
        }
        return OK;
}

Status CreateUDN(MGraph &G)
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
        return OK;
}

Status CreateDG(MGraph &G)
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
        return OK;
}

Status CreateUDG(MGraph &G)
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
        return OK;
}

Status CreateGraph(MGraph &G,GraphKind Kind)
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

int visited[20];				//���ʱ�־���飬δ������0�����ʹ���1
int VisitFunc(MGraph G,int i)	//�������� i��������int,��˼�������i������
{
	printf("V%c  ",G.vexs[i]);
	return 1;
}


//-------------- ��  �� ---------------
#define QElemType int

//---�������С������е���ʽ�洢�ṹ(��ͷ���)---
typedef struct QNode
{
	QElemType data;
	struct QNode *next;
}QNode, *QueuePtr;

typedef struct
{
	QueuePtr front;	//��ͷָ��
	QueuePtr rear;	//��βָ��
}LinkQueue;

Status InitQueue(LinkQueue &Q)	//��ͷ���Ķ���
{
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));	//��ͷ���Ķ���
	if(!Q.front)	//�洢����ʧ��
		exit(-1);
	Q.front->next = NULL;
	return OK;
}
Status EnQueue(LinkQueue &Q, QElemType e)
{	//����Ԫ��eΪQ���µĶ�βԪ��
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if(!p)		//�洢����ʧ��
		exit(OVERFLOW);
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	return OK;
}

Status DeQueue(LinkQueue &Q, QElemType &e)
{	//�����в��գ���ɾ��Q�Ķ�ͷԪ�أ���e������ֵ��������1
	//���򷵻�0
	QueuePtr p;
	if(Q.front == Q.rear)
		return ERROR;
	p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;
	if(Q.rear == p)
		Q.rear = Q.front;
	free(p);
	return OK;
}

//-------------------------------------

int FirstAdjVex(MGraph G,int i)
{
	int j;
	for ( j = 0; j < G.vexnum; ++j)
	{
		if(G.kind == DG || G.kind == UDG)			//����ͼ�����
		{
			if(G.arcs[i][j].adj == 1)				//��֮�ڽ�
				return j;
		}else										//�����������
		{											//�����Ȩֵ��δ�����ʹ��ļ�������
			if(G.arcs[i][j].adj != INT_MAX)
				return j;
		}
	}
	return -1;	//ע���ʱ��������е�������������0
}

int NextAdjVex(MGraph G,int i,int w)
	//w����Ĳ��ǵ�w�����㣬����adjvexΪw�Ľ��
	//���ص�i��ͷ��㣨���㣩��Ӧ�ı�����adjvexֵΪw�Ľ�����һ������adjvexֵ�����û�з���-1
{
	
	int j;
	for ( j = w + 1; j < G.vexnum; ++j)
	{
		if(G.kind == DG || G.kind == UDG)			//����ͼ�����
		{
			if(G.arcs[i][j].adj == 1)				//��֮�ڽ�
				return j;
		}else										//�����������
		{											//�����Ȩֵ��δ�����ʹ��ļ�������
			if(G.arcs[i][j].adj != INT_MAX)
				return j;
		}
	}
	return -1;	//ע���ʱ��������е�������������0
}


void BFSTraverse(MGraph G,int (* VisitFunc)(MGraph G, int i))
{	//��ͼ��������ȱ�������������ȷǵݹ����ͼG��ʹ�ø�������Q�ͷ��ʱ�־����visited��
	LinkQueue Q;
	int i,u;
	for(i = 0; i < G.vexnum; ++i)
		visited[i] = 0;
	InitQueue(Q);	//�ÿյĸ�������
	for(i = 0; i < G.vexnum; ++i)	//�ӵ�0�����㿪ʼ��
		if(!visited[i])
		{
			VisitFunc(G,i);
			visited[i] = 1;
			EnQueue(Q,i);
			while (Q.front != Q.rear)
			{
				int w;
				DeQueue(Q,u);	//��ͷԪ�س��ӣ�����ֵ��u
				for(w = FirstAdjVex(G, u); w >= 0; w = NextAdjVex(G, u, w))
					if(!visited[w])
					{
						VisitFunc(G,w);
						visited[w] = 1;
						EnQueue(Q,w);
					}//if
			}//while
		}//if
}



int main(void)
{
    MGraph G;
    CreateGraph(G,UDG);
    PrintG(G);
    printf("\n");
	BFSTraverse(G,VisitFunc);
    printf("\n");

   


    return 0;
}