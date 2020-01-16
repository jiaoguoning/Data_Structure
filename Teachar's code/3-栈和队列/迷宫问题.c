#include <stdio.h>
#include <stdlib.h>
#define STACK_INIT_SIZE 20
#define STACKINCREMENT 5
#define MazeType int (*)[10]




typedef struct {
	int X;		//�����꣺���ڵڼ���
	int Y;		//�����꣺���ڵڼ���
}PosType;

typedef struct
{
    int ord;		//ͨ������·���ϵġ���š�
    PosType seat;	//ͨ�������Թ��еġ�����λ�á�
    int di;			//�Ӵ�ͨ����������һͨ����ġ�����
					//1����    
}SElemType,ElemType;

typedef struct {
	ElemType *base;
	ElemType *top;
	int stacksize;
}SqStack;

int MazeMap[10][10] =    //�Թ���ͼΪȫ�ֱ���
{
   //x------------------
   //0,1,2,3,4,5,6,7,8,9
    {0,0,0,0,0,0,0,0,0,0}, //0 y
    {0,1,1,0,1,1,1,0,1,0}, //1 |
    {0,1,1,0,1,1,1,0,1,0}, //2 |
    {0,1,1,1,1,0,0,1,1,0}, //3 |
    {0,1,0,0,0,1,1,1,1,0}, //4 |
    {0,1,1,1,0,1,1,1,1,0}, //5 |
    {0,1,0,1,1,1,0,1,1,0}, //6 |
    {0,1,0,0,0,1,0,0,1,0}, //7 |
    {0,0,1,1,1,1,1,1,1,0}, //8 |
    {0,0,0,0,0,0,0,0,0,0}  //9 |
};

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
	return 1;
}

void printMaze(int map[10][10])
{
	int i,j;
	printf("�Թ����£�\n");

	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
			if (i == 1 && j == 1)
				printf(" S");
			else if (i == 8 && j == 8)
				printf(" E");
			else if ( map[i][j] == 0)
				printf(" M");
			else if (map[i][j] == 1000)
				printf(" X");
			else if (map[i][j] == 1)
				printf("  ");
			else
				printf(" o");
				
		printf("\n");
	}
}

int Pass(PosType pos)
{
	if(MazeMap[pos.Y][pos.X] == 1)
		return 1;
	return 0;
}
int FootPrint(PosType pos,int curstep)
{
	MazeMap[pos.Y][pos.X] = curstep;
	return 0;
}

PosType NextPos(PosType pos,int di)
{
	switch (di)
	{
	case 1:
		++pos.X;	//��
		break;
	case 2:
		++pos.Y;	//��
		break;
	case 3:
		--pos.X;	//��
		break;
	case 4:
		--pos.Y;	//��
		break;
	default:
		printf("��������\n");
		break;
	}
	return pos;
}

int MarkPrint(PosType seat)
{
	printf("(%d,%d)�߲�ͨ\n",seat.Y,seat.X);
	MazeMap[seat.Y][seat.X] = 1000;
	return 0;
}

void PrintStep()
{
	system("cls");
	printMaze(MazeMap);
	system("pause");
}


int MazePath(PosType start,PosType end)
	//���Թ�maze�д������start������end��ͨ���������һ�������ջ�У���ջ��
	//��ջ������������TRUE�����򷵻�FALSE
{
	SqStack *S = (SqStack*)malloc(sizeof(SqStack));
	ElemType e;
	PosType curpos = start;
	int curstep = 1;
	InitStack(S);
	do{
		if(Pass(curpos))//����ͨ��
		{
			e.ord = curstep;
			e.seat = curpos;
			e.di = 1;
			FootPrint(curpos,curstep);
			push(S,e);
			if (curpos.X == end.X && curpos.Y == end.Y)
				return 1;
			curpos = NextPos(curpos,1);//��һ��λ��������
			PrintStep();
			curstep++;
		}
		else//������ͨ��
		{
			if(S->base != S->top)
			{
				pop(S,&e);
				while (e.di == 4 && S->base != S->top)//���з���̽����϶����У�ֻ�ܺ���
				{
					MarkPrint(e.seat);
					pop(S,&e);
					PrintStep();
					curstep--;
                    printf("���˵�(%3d,%3d)\n",e.seat.Y,e.seat.X);
				}
				if(e.di < 4){
                    ++e.di;  //����һ������̽��
                    push(S,e);
                    curpos = NextPos(e.seat,e.di); //�趨��ǰλ���Ǹ��·����ϵ����ڿ�
                }//if
			}//if
		}//else
	}while(S->base != S->top);
	printf("û�ҵ����ڣ�\n");
	return 0;
}

int main(void)
{
	PosType start = {1,1};
	PosType end = {8,8};
	MazePath(start, end);
	PrintStep();
	
	return 0;
}



