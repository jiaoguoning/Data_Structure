#include <stdio.h>

int c;
void move(char x, int n, char z)
{
	printf("%d. 移动圆盘%d，从 %c 移到 %c ;\n",++c, n, x, z);
}


void hanoi(int n, char x, char y, char z)
{
	if(n == 1)
		move(x, 1, z);		//将编号为1的圆盘从x，移动到z
	else{
		hanoi(n-1, x, z, y);//将x上编号为1至n-1的圆盘移到y，z作辅助塔
		move(x, n, z);		 //将编号为n的圆盘从x移动到z
		hanoi(n-1,y,x,z);	//将y上编号为1至n-1的圆盘移到z，x作辅助塔
	}
}

int main(void)
{
    hanoi(3,'a','b','c');

	return 0;
}