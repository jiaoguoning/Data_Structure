#include <stdio.h>

// 假设有3个分别命名为x、y和z的塔座，在塔座x上插有n个直径大小各不相同、依小到大编号为1,2，...，n
// 的圆盘，现要求将x轴上的n个圆盘移至塔座z上并仍按同样顺序叠排，圆盘移动时，必须遵循下列规则：
// （1） 每次只能移动一个圆盘   
// （2） 圆盘可以插在x、y和z中的任一塔座上
// （3） 任何时刻都不能将一个较大的圆盘压在较小的圆盘之上  

int c;
// 将编号为n的圆盘从x移动到z 
void move(char x, int n, char z)
{
	printf("%d. 移动圆盘%d，从 %c 移到 %c ;\n",++c, n, x, z);
}


// 将x上编号为1~n的圆盘移动至z，y作为辅助塔    
void hanoi(int n, char x, char y, char z)
{
	if(n == 1)
		move(x, 1, z);		//将编号为1的圆盘从x，移动到z
	else{
		hanoi(n-1, x, z, y); //将x上编号为1至n-1的圆盘移到y，z作辅助塔
		move(x, n, z);		 //将编号为n的圆盘从x移动到z
		hanoi(n-1,y,x,z);	 //将y上编号为1至n-1的圆盘移到z，x作辅助塔
	}
}

int main(void)
{
    hanoi(3,'a','b','c');

	return 0;
}