/***
*DynaLnkList.h - ��̬����Ķ���
*	
****/

#if !defined(DYNALNKLIST_H)
#define DYNALNKLIST_H

#include "ElemType.h"

/*------------------------------------------------------------
// ����ṹ�Ķ���
------------------------------------------------------------*/
typedef struct Node
{
	ElemType data;				// Ԫ������
	struct Node *next;			// �����н��Ԫ�ص�ָ��
} LNode, *LinkList;

/*------------------------------------------------------------
// ����Ļ�������
------------------------------------------------------------*/

bool InitList(LinkList *L);
void DestroyList(LinkList *L);
void ListTraverse(LinkList L, void (*fp)(ElemType));
bool ListInsert(LinkList L, int i, ElemType e);
bool ListDelete(LinkList L, int i, ElemType *e);
int  ListLength(LinkList L);
bool Inverse(LinkList L);
#endif /* DYNALNKLIST_H */