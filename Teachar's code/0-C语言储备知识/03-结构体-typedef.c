#include <stdio.h>

//----------------     ½á¹¹Ìå     ----------------//

typedef struct Date
{
	int Year;
	int Month;
	int Day;
	struct Date *pDate;
}Date, *pDate;

typedef int INTARR[3];

int main(void)
{
	Date d1 = {2018,9,11};
	pDate pd = &d1;
	Date* pd1 = &d1;
    INTARR arr1;
	arr1[0] = 1;	arr1[1] = 2;   arr1[2] = 3;
	pd->pDate = &d1;
	printf("%d-%d-%d\n",pd->Year,pd->Month,pd->Day);
	printf("%d-%d-%d\n",pd1->Year,pd1->Month,pd1->Day);
	printf("%d-%d-%d\n",pd->pDate->Year,pd->pDate->Month,pd->pDate->Day);

	return 0;
}

