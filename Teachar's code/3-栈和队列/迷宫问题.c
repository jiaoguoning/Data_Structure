#include <stdio.h>
#include <stdlib.h>
#define STACK_INIT_SIZE 20
#define STACKINCREMENT 5
#define MazeType int (*)[10]




typedef struct {
	int X;		//横坐标：所在第几列
	int Y;		//纵坐标：所在第几行
}PosType;

typedef struct
{
    int ord;		//通道块在路径上的“序号”
    PosType seat;	//通道块在迷宫中的“坐标位置”
    int di;			//从此通道块走向下一通道块的“方向”
					//1：东    
}SElemType,ElemType;

typedef struct {
	ElemType *base;
	ElemType *top;
	int stacksize;
}SqStack;

int MazeMap[10][10] =    //迷宫地图为全局变量
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

//因为要修改栈S内存中数据成员的值，因此必须传递S的地址
int InitStack(SqStack *S)
{
	S->base = (ElemType*)malloc(sizeof(ElemType) * STACK_INIT_SIZE);
	if (!S->base)
	{
		printf("初始化失败！\n");
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
			printf("追加失败!\n");
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
		printf("出栈失败，栈为空!\n");
		return 0;
	}
	*e = *--S->top;
	return 1;
}

void printMaze(int map[10][10])
{
	int i,j;
	printf("迷宫如下：\n");

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
		++pos.X;	//东
		break;
	case 2:
		++pos.Y;	//南
		break;
	case 3:
		--pos.X;	//西
		break;
	case 4:
		--pos.Y;	//北
		break;
	default:
		printf("方向有误！\n");
		break;
	}
	return pos;
}

int MarkPrint(PosType seat)
{
	printf("(%d,%d)走不通\n",seat.Y,seat.X);
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
	//若迷宫maze中存在入口start到出口end的通道，则求得一条存放在栈中（从栈底
	//到栈顶），并返回TRUE；否则返回FALSE
{
	SqStack *S = (SqStack*)malloc(sizeof(SqStack));
	ElemType e;
	PosType curpos = start;
	int curstep = 1;
	InitStack(S);
	do{
		if(Pass(curpos))//可以通过
		{
			e.ord = curstep;
			e.seat = curpos;
			e.di = 1;
			FootPrint(curpos,curstep);
			push(S,e);
			if (curpos.X == end.X && curpos.Y == end.Y)
				return 1;
			curpos = NextPos(curpos,1);//下一个位置往东走
			PrintStep();
			curstep++;
		}
		else//不可以通过
		{
			if(S->base != S->top)
			{
				pop(S,&e);
				while (e.di == 4 && S->base != S->top)//所有方向都探索完毕都不行，只能后退
				{
					MarkPrint(e.seat);
					pop(S,&e);
					PrintStep();
					curstep--;
                    printf("倒退到(%3d,%3d)\n",e.seat.Y,e.seat.X);
				}
				if(e.di < 4){
                    ++e.di;  //换下一个方向探索
                    push(S,e);
                    curpos = NextPos(e.seat,e.di); //设定当前位置是该新方向上的相邻块
                }//if
			}//if
		}//else
	}while(S->base != S->top);
	printf("没找到出口！\n");
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



