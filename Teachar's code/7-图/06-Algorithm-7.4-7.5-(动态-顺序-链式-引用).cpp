#include <stdio.h>
#include <stdlib.h>

#define Status      int
#define OK          1
#define ERROR       0
#define OVERFLOW    -2
#define FALSE       0
#define TRUE        1

//---ͼ���ڽӱ�洢��ʾ---
#define MAX_VERTEX_NUM  20
#define InfoType        int	//�û������Ϣ��ָ�루������Ϣ�������������int���ͣ�
#define VertexType      char	//�������ͣ�����ÿ��������һ���ַ���ʾ��

typedef enum
{
    DG,DN,UDG,UDN			//����ͼ��������������ͼ��������
}GraphKind;		

typedef struct ArcNode {    //��������
    int adjvex;				//�û�ָ�򶥵�λ�� 0,1,2,3...
    //���λ��ָ�����ڽӵĶ����ڱ�ͷ�����е�λ��
    struct ArcNode * nextarc;	//ָ����һ������ָ��
    InfoType *info;				//�û������Ϣ��ָ��
}ArcNode;

typedef struct VNode {  //ͷ�������
    VertexType data;	//������Ϣ��VertexTypeʵ�����Ƕ������ͣ�
    ArcNode *firstarc;	//ָ���һ�������ö���Ļ���ָ��
}VNode, AdjList[MAX_VERTEX_NUM];

typedef struct	{	    //�ڽӱ�����
    AdjList vertices;	
    int vexnum;	//ͼ�Ķ�����
    int arcnum;	//ͼ�Ļ���
    GraphKind kind;			//ͼ�����ͱ�־
}ALGraph;


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

int LocateVex(ALGraph G,char v,int vexnum)
{
    int i;
    for (i = 0; i < vexnum; i++)
    {
        if(v == G.vertices[i].data)
            return i;
    }
    printf("���붥�����󣬶�λʧ�ܣ�\n");
    exit(OVERFLOW);
}

Status ALCreateDG(ALGraph &G)	//��������ע�⣺��ͬһ��������������У����������Բ�ͬ
    //�ڽӱ���������ͼ
{
    int i;
    G.vexnum = VexNum;
    G.arcnum = ArcNum;
    for (i = 0;  i < G.vexnum; ++i)
    {
        G.vertices[i].data = Vex[i];
        G.vertices[i].firstarc = NULL;
    }
    for(i = 0;i < G.vexnum; ++i)	//�����ڽӱ�������㣬���δ�������
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
                newNode->adjvex = LocateVex(G,vvw[k].v2,G.vexnum);//ȷ������v2��G.vertices�е�λ��
                newNode->nextarc = NULL;
                newNode->info = (InfoType *)malloc(sizeof(InfoType) * 1);
                newNode->info[0] = vvw[k].w;	//�˴����Է�������������������Ȩֵ
                p = G.vertices[i].firstarc;		//pָ���i������Ķ�Ӧ�ĵ�1�������
                if(!p)	//���p�ǿյĻ���ֱ�Ӹ�ֵ
                {
                    G.vertices[i].firstarc = newNode;
                }else	//��p��Ϊ��
                {
                    while(p->nextarc)
                        p = p->nextarc;				//ͨ��ѭ����pָ���i����������1������
                    p->nextarc = newNode;			//ͬһ������ı��������Բ�ͬ
                }
            }
        }
    }
    return OK;
}

Status ALCreateUDG(ALGraph &G)	//��������ע�⣺��ͬһ��������������У����������Բ�ͬ
    //�ڽӱ���������ͼ
{
    int i;
    G.vexnum = VexNum;
    G.arcnum = ArcNum;
    for (i = 0;  i < G.vexnum; ++i)
    {
        G.vertices[i].data = Vex[i];
        G.vertices[i].firstarc = NULL;
    }
    for(i = 0;i < G.vexnum; ++i)	//�����ڽӱ�������㣬���δ�������
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
                    newNode->adjvex = LocateVex(G,vvw[k].v2,G.vexnum);//ȷ������v2��G.vertices�е�λ��
                else
                    newNode->adjvex = LocateVex(G,vvw[k].v1,G.vexnum);//ȷ������v1��G.vertices�е�λ��
                newNode->nextarc = NULL;
                newNode->info = (InfoType *)malloc(sizeof(InfoType) * 1);
                newNode->info[0] = vvw[k].w;	//�˴����Է�������������������Ȩֵ
                p = G.vertices[i].firstarc;		//pָ���i������Ķ�Ӧ�ĵ�1�������
                if(!p)	//���p�ǿյĻ���ֱ�Ӹ�ֵ
                {
                    G.vertices[i].firstarc = newNode;	//!!!ע��˴���������p = newNode��Ϊp����ָ��
                    //G.vertices[i].firstarc��ָ�룬ֻ�Ǻ���ͬ��ı���
                }else	//��p��Ϊ��
                {
                    while(p->nextarc)
                        p = p->nextarc;				//ͨ��ѭ����pָ���i����������1������
                    p->nextarc = newNode;			//ͬһ������ı��������Բ�ͬ
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
    case DG:	//��������ͼG
        return ALCreateDG(G);
    case UDG:	//��������ͼG
        return ALCreateUDG(G);
    default:
        return ERROR;
    }
}

int visited[20];				//���ʱ�־���飬δ������0�����ʹ���1
Status VisitFunc(ALGraph G,int i)	//�������� i��������int,��˼�������i������
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
    //w����Ĳ��ǵ�w�����㣬����adjvexΪw�Ľ��
    //���ص�i��ͷ��㣨���㣩��Ӧ�ı�����adjvexֵΪw�Ľ�����һ������adjvexֵ�����û�з���-1
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
{   //�ӵ�v����������ݹ��������ȱ���ͼ������G��
    int w;

    VisitFunc(G,v);	//���ʵ�i�����
    visited[v] = 1;	//���ʹ��Ľ�㣬�±�λ�ñ��1

    for(w = FirstAdjVex(G,v); w >= 0; w = NextAdjVex(G,v,w))
        if(!visited[w])//��֮�ڽ���δ�����ʹ��ļ�������
            DFS(G,w);
}

void DFSTraverse(ALGraph G,int (* VisitFunc)(ALGraph G, int i))
 {  //��ͼG��������ȱ�����
    //ʹ��ȫ�ֱ���VisitFunc��ʹDFS�����躯��ָ�����

    int i;
    for(i = 0; i < G.vexnum; ++i)
        visited[i] = 0;	//���ʱ�־�����ʼ��
    for(i = 0; i < G.vexnum; ++i)
        if(!visited[i])
            DFS(G,i);	//����δ���ʵĶ������DFS
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