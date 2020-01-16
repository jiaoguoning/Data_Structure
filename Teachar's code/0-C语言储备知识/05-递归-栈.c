//编一个程序，main函数中输入具有5个元素的整型数组，然后调用一个函数，递归计算这些元素的和。（15分）

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
