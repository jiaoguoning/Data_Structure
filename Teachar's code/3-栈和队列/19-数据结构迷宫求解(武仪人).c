#include <stdio.h>
#include <stdlib.h>

#define Status          int
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define OK              1
#define ERROR           0
#define OVERFLOW        -2

const int dx[] = {1 , 0 , -1 , 0} , dy[] = {0 , 1 , 0 , -1};


typedef struct node
{
    int X;
    int Y;
}PosType;

typedef struct
{
    PosType * base;
    PosType * top;
    int stacksize;
}SqStack;

int flag[10][10];
int Map[][10] = 
{
    {1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1} ,
    {1 , 0 , 0 , 1 , 0 , 0 , 0 , 1 , 0 , 1} ,
    {1 , 0 , 0 , 1 , 0 , 0 , 0 , 1 , 0 , 1} ,
    {1 , 0 , 0 , 0 , 0 , 1 , 1 , 0 , 0 , 1} ,
    {1 , 0 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 1} ,
    {1 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 1} ,
    {1 , 0 , 1 , 0 , 0 , 0 , 1 , 0 , 0 , 1} ,
    {1 , 0 , 1 , 1 , 1 , 0 , 1 , 1 , 0 , 1} ,
    {1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1} ,
    {1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1} 
};

Status InitStack(SqStack * st)
{//初始化栈

    st -> base = (PosType *) calloc(STACK_INIT_SIZE , sizeof(PosType));
    if(!(st -> base)) exit(OVERFLOW);

    st -> top = st -> base;
    st -> stacksize = STACK_INIT_SIZE;
    return OK;
}
Status Push(SqStack * st , PosType e)
{
    if(st -> top - st -> base >= st -> stacksize)
    {
        st -> base = (PosType *) realloc(st -> base , (st -> stacksize + STACKINCREMENT) * sizeof(PosType));
        if(!(st -> base)) exit(OVERFLOW);
        st -> top = st -> base + st -> stacksize;
        st -> stacksize += STACKINCREMENT;
    }
    *(st -> top ++) = e;
    return OK;
}
Status Pop(SqStack * st , PosType * e)
{
    if(st -> top - st -> base <= 0) return ERROR;
    *e = *(-- st -> top);
    return OK;
}
Status MazePath(SqStack * st , PosType start , PosType end)
{
    
    PosType e , NextPost;
    InitStack(st);
    Push(st , start);
    flag[start.X][start.Y] = 1;
    
    while(st -> top - st -> base > 0)//只要栈非空
    {
        
        Pop(st , &e);//弹出栈顶
        
        if(e.X == end.X && e.Y == end.Y)//找到终点
        {
            printf("找到了终点\n");
            return OK;
        }

        for(int i = 0 ; i < 4 ; ++ i)//遍历上下左右四个方向
        {
            //下一个点的坐标
            int x = e.X + dx[i];
            int y = e.Y + dy[i];
            //如果下一个点可走
            if(x > 0 && x < 10 && y > 0 && y < 10 && !Map[x][y] && !flag[x][y])
            {
                NextPost.X = x;
                NextPost.Y = y;
                flag[x][y] = 1;
                Push(st , NextPost);
            }
            
        }
    }
    return ERROR;
}
int main(void)
{
    SqStack st;
    InitStack(&st);
    PosType start , end;
    start.X = 1;
    start.Y = 1;
    end.X = 8;
    end.Y = 8;

    MazePath(&st , start , end);
}