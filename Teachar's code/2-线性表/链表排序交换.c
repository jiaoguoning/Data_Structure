#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
	char ID[20];//Ñ§ºÅ
	int Score;  //³É¼¨
	struct node *Next;
}Node,*List;

int Insert(List *L,Node e)
{
	Node *p = (*L);
	Node * newNode = (List)malloc(sizeof(Node));
	if(!newNode)      
		return 0;
	strcpy(newNode->ID,e.ID);
	newNode->Score = e.Score;
	newNode->Next = NULL;
	while (p->Next)
	{
		p = p->Next;
	}
	p->Next = newNode;

	return 1;
}

void Swap(List *L,int i,int j)
{
	Node *p = (*L);
	int l = 0,k = 1;
	int t;
	char s[20];
	Node *temp1;
	Node *temp2;
	while (p->Next)
	{
		p = p->Next;
		l++;
	}
	p = (*L);
	if (i > 0 && i <= l && j>0 && j<=l)
	{
		while (p->Next && k <= i)
		{
			p = p->Next;
			k++;
		}
		temp1 = p;
		k = 1;
		p = (*L);
		while (p->Next && k<= j)
		{
			p = p->Next;
			k++;
		}
		temp2 = p;
		t = temp1->Score;	strcpy(s,temp1->ID);
		temp1->Score = temp2->Score;	strcpy(temp1->ID,temp2->ID);
		temp2->Score = t;	strcpy(temp2->ID,s);
	}
}


void Sort(List *L)
{
	int i,j,l = 0,t;
	char s[20];
	Node *p = (*L);
	Node *temp1;
	Node *temp2;
	while (p->Next)
	{
		p = p->Next;
		l++;
	}
	for (i = 0; i < l-1; i++)
	{
		p = (*L)->Next;
		for ( j = 0; j < l-i-1; j++)
		{
			temp1 = p;
			temp2 = p->Next;
			if(temp1->Score > temp2->Score)
			{
				t = temp1->Score;	strcpy(s,temp1->ID);
				temp1->Score = temp2->Score;	strcpy(temp1->ID,temp2->ID);
				temp2->Score = t;	strcpy(temp2->ID,s);
			}
			p = p->Next;
		}
	}
}



int main(void)
{
	List L = (List)malloc(sizeof(Node));List p;
	int i = 0;

	Node stu[5] = { {"2018011460",80} ,{"2018011427",77},{"2018011429",73}
	,{"2018011430",55},{"2018011431",69}};
	L->Next = NULL;
	for (i = 0; i < 5; i++)
	{
		Insert(&L,stu[i]);
	}
	Swap(&L,2,4);
	for(p = L->Next;p;p = p->Next)
	{
		printf("%d\n",p->Score);
	}

	return 0;
}
