#include <stdio.h>

int c;
void move(char x, int n, char z)
{
	printf("%d. �ƶ�Բ��%d���� %c �Ƶ� %c ;\n",++c, n, x, z);
}


void hanoi(int n, char x, char y, char z)
{
	if(n == 1)
		move(x, 1, z);		//�����Ϊ1��Բ�̴�x���ƶ���z
	else{
		hanoi(n-1, x, z, y);//��x�ϱ��Ϊ1��n-1��Բ���Ƶ�y��z��������
		move(x, n, z);		 //�����Ϊn��Բ�̴�x�ƶ���z
		hanoi(n-1,y,x,z);	//��y�ϱ��Ϊ1��n-1��Բ���Ƶ�z��x��������
	}
}

int main(void)
{
    hanoi(3,'a','b','c');

	return 0;
}