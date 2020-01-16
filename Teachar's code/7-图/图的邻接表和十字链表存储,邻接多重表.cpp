#include <stdio.h>
#include <stdlib.h>

//---ͼ���ڽӱ�洢��ʾ---
#define MAX_VERTEX_NUM 20
#define InfoType int	//�û������Ϣ��ָ�루������Ϣ�������������int���ͣ�
#define VertexType char	//�������ͣ�����ÿ��������һ���ַ���ʾ��
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
	int vexnum, arcnum;	//ͼ�Ķ������ͻ���
	int kind;			//ͼ�����ͱ�־
}ALGraph;


//---����ͼ��ʮ������洢��ʾ---
typedef struct ArcBox	//�����Ľṹ
{
	int tailvex, headvex;		//�û���β��ͷ�����λ��
	struct ArcBox *hlink,*tlink;//�ֱ�Ϊ��ͷ��ͬ�ͻ�β��ͬ�Ļ�������
	InfoType *info;				//�û������Ϣ��ָ��
}ArcBox;

typedef struct VexNode	//������ṹ
{
	VertexType data;			//������Ϣ��VertexTypeʵ�����Ƕ������ͣ�
	ArcBox *firstin, *firstout;	//�ֱ�ָ��ö����һ���뻡�ͳ���
}VexNode;

typedef struct			//ʮ������ṹ
{
	VexNode xlist[MAX_VERTEX_NUM];//��ͷ����
	int vexnum, arcnum;			  //����ͼ�ĵ�ǰ�������ͻ���
}OLGraph;

//---����ͼ���ڽӶ��ر�洢��ʾ---
typedef enum
{
	unvisited, visited
} VisitIf;

typedef struct EBox		//�߽��Ľṹ
{
	VisitIf mark;				//���ʱ��
	int ivex, jvex;				//�ñ����������������λ��
	struct EBox *ilink, *jlink;	//�ֱ�ָ�������������������һ����
	InfoType *info;				//�ñ���Ϣָ��
}EBox;

typedef struct VexBox	//������Ľṹ
{
	VertexType data;
	EBox *firstedge;			//ָ���һ�������ö���ı�
}VexBox;

typedef struct			//�ڽӶ��ر�ṹ
{
	VexBox adjmulist[MAX_VERTEX_NUM];
	int vexnum, adgenum;		//����ͼ�ĵ�ǰ�������ͱ���
}AMLGraph;