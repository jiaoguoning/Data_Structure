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


VertexType Vex[9] = {'1','2','3','4','5','6','7','8','9'};	//������Ϊ��'1'����v1���Դ�����
typedef struct 
{
	char v1,v2;
	int w;
}VVW;
VVW vvw[11] = {		//ÿ�����������㼰Ȩֵ(Ȩֵ�Ǽ����)
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

int ALCreateDN(ALGraph &G)
	//�������飨�ڽӾ��󣩱�ʾ��������������G��
{
	int i, k, IncInfo = 0;		//IncInfoΪ0���������������Ϣ
	G.vexnum = VexNum;
	G.arcnum = ArcNum;
	for(i = 0;i < G.vexnum; ++i)
	{
		G.vertices[i].data = Vex[i];	//���춥������
		G.vertices[i].firstarc = NULL;
	}
	for(i = 0;i < G.vexnum; ++i)	//�����ڽӱ�������㣬���δ�������
	{		

		for(k = 0; k < G.arcnum; ++k)	//�����ڽӾ���
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

int ALCreateGraph(ALGraph &G,GraphKind Kind)
{
	G.kind = Kind;
	switch (G.kind)
	{
	case DN:	//����������G
		return ALCreateDN(G);
	default:
		return 0;
	}
}

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
			printf("׷��ʧ��!\n");
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
		printf("��ջʧ�ܣ�ջΪ��!\n");
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
	//PrintStack(S);
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
int ve[VexNum];
int TopologicalOrder(ALGraph G, SqStack &T)
	//������G�����ڽӱ�洢�ṹ���������ʱ������緢��ʱ��ve��ȫ�ֱ�����
	//TΪ�������ж���ջ��SΪ����ȶ���ջ��
	//��G�޻�·������ջT����G��һ���������У��Һ���ֵΪOK������ΪERROR
{
	int i,j;
	int indegree[VexNum] = {0};
	FindInDegree(G, indegree);	//������������±��0��ʼ
	//������ȶ���ջS��
	SqStack S;
	InitStack(&S);

	for(i = 0; i < G.vexnum; ++i)
		if(!indegree[i])	//��0��ȶ���ջS
			push(&S,i);		//���Ϊ0�߽�ջ
	InitStack(&T);	int count = 0;
	while (S.base != S.top)
	{
		ArcNode* p;
		pop(&S, &j);	push(&T, j);
		VisitFunc(G,j);			//��i�����ջ��Ԫ�ض�Ӧ�Ķ��㣬Ҳ�����������Ķ���	
		++count;				//���i�Ŷ��㲢����
		for(p = G.vertices[j].firstarc; p; p = p->nextarc)
		{	//ͨ��ѭ��������i������ı��㣬����������ȶ���1
			int k = p->adjvex;	//��i�Ŷ����ÿ���ڽӵ����ȼ�1
			if(!(--indegree[k]))
				push(&S,k);		//����ȼ�Ϊ0������ջ
			if(ve[j] + *(p->info) > ve[k])
				ve[k] = ve[j] + *(p->info);
		}//for  *(p->info) = dut(<j, k>)
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
void PrintCriticalActivity(ALGraph G,int j,int k,int dut,int ee,int el,char tag)
{
	if(tag == '*')
		printf("�ؼ�·����V%c --> V%c ,�ʱ�䣺%d ,���翪ʼ��%2d,����ʼ��%2d\n",G.vertices[j].data,
							G.vertices[k].data,dut,ee,el);
	else
		printf("һ��·����V%c --> V%c ,����䣺%d ,���翪ʼ��%2d,����ʼ��%2d\n",G.vertices[j].data,
							G.vertices[k].data,dut,ee,el);
}
int CriticalPath(ALGraph G)
{	//��ΪG�������������G�ĸ���ؼ��
	SqStack T;
	int i, j;	ArcNode* p;
	int k , dut;
	if(!TopologicalOrder(G,T))
		return 0;
	int vl[VexNum];
	for (i = 0; i < VexNum; i++)
		vl[i] = ve[VexNum - 1];		//��ʼ�������¼�����ٷ���ʱ��
	while (T.base != T.top)			//������������������vlֵ
	{
		
		for(pop(&T, &j), p = G.vertices[j].firstarc; p; p = p->nextarc)
		{
			k = p->adjvex;	dut = *(p->info);	//dut<j, k>
			if(vl[k] - dut < vl[j])
				vl[j] = vl[k] - dut;
		}//for
	}//while
	for(j = 0; j < G.vexnum; ++j)	//��ee,el�͹ؼ��
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


