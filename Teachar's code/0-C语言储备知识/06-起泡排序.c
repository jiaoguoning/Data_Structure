void bubble_sort(int a[],int n)  
{
	int i = 0,change = 0,j,temp;
	for(i = n-1,change = 1;i >= 1 && change; --i)
	{
		change = 0;
		for(j = 0;j < i; ++j)
			if(a[j] > a[j+1])
			{
				temp = a[j]; a[j] = a[j+1]; a[j+1] = temp;
			}
	}
}

