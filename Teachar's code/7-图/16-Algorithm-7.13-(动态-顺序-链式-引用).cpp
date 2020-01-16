#include <stdio.h>
#include <stdlib.h>

//---ͼ���ڽӱ�洢��ʾ---
#define MAX_VERTEX_NUM 20
#define InfoType int	//�û������Ϣ��ָ�루������Ϣ�������������int���ͣ�
#define VertexType char	//�������ͣ�����ÿ��������һ���ַ���ʾ��

typedef enum
{
	DG,DN,UDG,UDN			//����ͼ��������������ͼ��������
}GraphKind;		

typedef struct ArcNode//��������
{
	int   adjvex;				//�û�ָ�򶥵�λ�� 0,1,2,3...
								//���λ��ָ�����ڽӵĶ����ڱ�ͷ�����е�λ��
	struct ArcNode * nextarc;	//ָ����һ������ָ��
	InfoType *info;				//�û������Ϣ��ָ��
}ArcNode;

typedef struct VNode//ͷ�������
{
	VertexType data;	//������Ϣ��VertexTypeʵ�����Ƕ������ͣ�
	ArcNode *firstarc;	//ָ���һ�������ö���Ļ���ָ��
}VNode, AdjList[MAX_VERTEX_NUM];

typedef struct		//�ڽӱ�����
{
	AdjList vertices;	
	int vexnum;	//ͼ�Ķ�����
	int arcnum;	//ͼ�Ļ���
	GraphKind kind;			//ͼ�����ͱ�־
}ALGraph;

														//10  11  12
VertexType Vex[12] = {'1','2','3','4','5','6','7','8','9','A','B','C'};	//������Ϊ��'1'����v1��'A'����10���Դ�����
typedef struct 
{
	char v1,v2;
	int w;
}VVW;
VVW vvw[17] = {		//ÿ�����������㼰Ȩֵ(Ȩֵ�Ǽ����)
			/*V1*/	{'1','2',5},{'1','3',7},{'1','4',5},{'1','C',2},
			/*V2*/	{'2','3',4},
			/*V3*/	{'3','5',9},{'3','7',3},{'3','8',1},
			/*V4*/	{'4','5',6},
			/*V5*/	{'5','7',8},{'5','8',5},
			/*V6*/	{'6','8',3},
			/*V7*/	
			/*V8*/	
			/*V9*/	{'9','A',5},{'9','B',5},{'9','C',4},
			/*V10*/	{'A','C',3},
			/*V11*/	{'B','6',2}
			/*V12*/	
};

#define VexNum  12
#define ArcNum  17

int LocateVex(ALGraph G,char v,int vexnum)
{
	int i;
	for (i = 0; i < vexnum; i++)
	{
		if(v == G.vertices[i].data)
			return i;
	}
	printf("���붥�����󣬶�λʧ�ܣ�\n");
	exit(-1);
}

int ALCreateDG(ALGraph &G)	//��������ע�⣺��ͬһ��������������У����������Բ�ͬ
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
	return 1;
}

int ALCreateUDG(ALGraph &G)	//��������ע�⣺��ͬһ��������������У����������Բ�ͬ
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
	return 1;
}

int ALCreateGraph(ALGraph &G,GraphKind Kind)
{
	G.kind = Kind;
	switch (G.kind)
	{
	case DG:	//��������ͼG
		return ALCreateDG(G);
	case UDG:	//��������ͼG
		return ALCreateUDG(G);
	default:
		return 0;
	}
}

int visited[20];				//���ʱ�־���飬δ������0�����ʹ���1
int VisitFunc(ALGraph G,int i)	//�������� i��������int,��˼�������i������
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

//------------ ջ �� �� �� --------------//
#define STACK_INIT_SIZE 20
#define STACKINCREMENT 5
#define ElemType int
typedef struct {
	ElemType *base;
	ElemType *top;
	int stacksize;
}SqStack;

//��ΪҪ�޸�ջS�ڴ������ݳ�Ա��ֵ����˱��봫��S�ĵ�ַ
int InitStack(SqStack *S)
{
	S->base = (ElemType*)malloc(sizeof(ElemType) * STACK_INIT_SIZE);
	if (!S->base)
	{
		printf("��ʼ��ʧ�ܣ�\n");
		return 0;
	}
	S->top = S->base;
	S->stacksize = STACK_INIT_SIZE;
	return 1;
}

void PrintStack(SqStack S)
{
	/*ElemType *p = S.base;
	printf("\n||");
	while(p < S.top)
	{
		printf(" %d ",*p);
		++p;
	}
	printf(" ||\n");*/
}

int push(SqStack *S,ElemType e)
{
	if ((S->top - S->base) >= S->stacksize)
	{
		S->base = (ElemType *)realloc(S->base,S->stacksize+STACKINCREMENT);
		if (!S->base)
		{
			printf("׷��ʧ��!\n");
			return 0;
		}
		S->top = S->base + S->stacksize;
		S->stacksize += STACKINCREMENT;
	}
	*S->top++ = e;
	PrintStack(*S);
	return 1;
}

int pop(SqStack *S,ElemType *e)
{
	if (S->top == S->base)
	{
		printf("��ջʧ�ܣ�ջΪ��!\n");
		return 0;
	}
	*e = *--S->top;
	PrintStack(*S);
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
	//����ͼG�����ڽӱ�洢�ṹ��
	//��G�޻�·�������G�Ķ����һ���������в�����1�����򷵻�0.
	//���������ջ�ĺ���ȳ�ԭ��ɾ�����㣬�������
{
	SqStack S;
	int i, count;
	int *indegree1 = (int *)malloc(sizeof(int) * G.vexnum);
	int indegree[12] = {0};
	FindInDegree(G, indegree);	//������������±��0��ʼ
	InitStack(&S);
	PrintStack(S);
	for(i = 0; i < G.vexnum; ++i)
		if(!indegree[i])	//��0��ȶ���ջS
			push(&S,i);		//���Ϊ0�߽�ջ
	count = 0;				//������������
	while (S.base != S.top)
	{
		ArcNode* p;
		pop(&S,&i);
		VisitFunc(G,i);			//��i�����ջ��Ԫ�ض�Ӧ�Ķ��㣬Ҳ�����������Ķ���	
		++count;				//���i�Ŷ��㲢����
		for(p = G.vertices[i].firstarc; p; p = p->nextarc)
		{	//ͨ��ѭ��������i������ı��㣬����������ȶ���1
			int k = p->adjvex;	//��i�Ŷ����ÿ���ڽӵ����ȼ�1
			if(!(--indegree[k]))
				push(&S,k);		//����ȼ�Ϊ0������ջ
		}//for
	}//while
	if(count < G.vexnum)
	{
		printf("\n������ͼ�л�·!\n");
		return 0;	//������ͼ�л�·
	}
	else
	{
		printf("\n������ͼû�л�·!\n");
		return 1;
	}
}


int main(void)
{
	ALGraph G;
	ALCreateGraph(G,DG);
	PrintVertices(G);
	TopologicalSort(G);


	return 0;
}