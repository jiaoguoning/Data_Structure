//��һ������main�������������5��Ԫ�ص��������飬Ȼ�����һ���������ݹ������ЩԪ�صĺ͡���15�֣�

#include<stdio.h>

int fun(int *a,int n)
{
    if(n == 0)
        return a[0];
    else
        return fun(a ,n - 1) + a[n];
}
int main(void)
{
    int a[5] = {1, 2, 3, 4, 5},i;
    
    printf("%d",fun(a, 4));
    return 0;
}
