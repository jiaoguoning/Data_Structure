#include <stdio.h>

#define  EQ(a, b)	((a)==(b))	//a,b为数值型
#define  LT(a, b)	((a)< (b))
#define  LQ(a, b)	((a)<=(b))
#define MAXSIZE 20


typedef int KeyType;

typedef struct
{
	KeyType key;
}RedType;

typedef struct 
{
	RedType r[MAXSIZE+1];
	int length;
}SqList;

typedef SqList HeapType;	//堆采用顺序表存储表示

void printData(SqList L,int s,int m);

void HeapAdjust(HeapType &H,int s,int m)
	//已知H.r[s...m]中记录的关键字除H.r[s].key之外均满足堆的定义，本函数调整H.r[s]
	//的关键字，使H.r[s...m]成为一个大顶堆（对其中记录的关键字而言）
	//自下而上依次创建大顶堆，如果只改变最上面的
{
	int j;
	for(j = 2 * s;j <= m; j *= 2)	//沿key较大的孩子结点向下筛选
	{
		if( j < m && LT(H.r[j].key,H.r[j+1].key))
			++j;					//j两个子节点中为key较大记录的下标
		printData(H,s,m);
		if(!LT(H.r[s].key,H.r[j].key))
			break;					//让子结点较大key值和父结点s比较，若小于父节点key，跳出循环
		H.r[0] = H.r[s];			//否则，交换key值较大子结点和父结点
		H.r[s] = H.r[j];
		H.r[j] = H.r[0];			
		printData(H,s,m);
   		s = j;						//交换完成后，继续比较子结点j对应的子结点
		printData(H,-1,m);
	}
}

void HeapSort(HeapType &H)
	//对顺序表H进行堆排序
{
	int i;
	RedType temp;
	for(i = H.length / 2; i > 0; --i)//把H.r[1...H.length]建成大顶堆
	{
		HeapAdjust(H, i, H.length);	 //从最后一个非终端结点开始，依次调整所有的结点，使之成为大顶堆
	}
	for(i = H.length; i > 1; --i)
	{
		H.r[0] = H.r[1];			 //将堆顶记录和当前未经排序子序列H.r[1...i]中
		H.r[1] = H.r[i];			 //最后一个记录相互交换
		H.r[i] = H.r[0];
		printData(H,-1,-1);
		HeapAdjust(H, 1, i-1);	//将H.r[1...i-1]重新调整为大顶堆
								//因为已经成为大顶堆，只是根结点相当于插入一个元素
								//后面只需要调整第1个根结点即可
	}
}


void printData(SqList L,int s,int m)
{
	int i;
	for (i = 1; i <= L.length; ++i)
		printf("%2d  ", L.r[i].key);
	printf("\n");
	for (i = 1; i <= m; ++i)
	{
		if(i == s)
			printf("||  ");
		else if(i == 2 * s)
			printf("|L  ");
		else if(i == 2 * s + 1)
			printf("R|  ");
		else
			printf("    ");
	}
	printf("\n");
}



int main(void)
{
	int arr[8] = {49, 38, 65, 97, 76, 13, 27, 49};
	SqList L;
	L.r[0].key = 0;
	L.length = 0;
	for (int i = 1; i <= 8; i++)
	{
		L.r[i].key = arr[i-1];
		++L.length;
	}
	printData(L,-1,-1);
	HeapSort(L);
	printData(L,-1,-1);

	return 0;
} 