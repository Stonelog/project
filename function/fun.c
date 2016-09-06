#include <stdio.h>
#include <stdlib.h>

int gcb(int num1, int num2)
{
	if(num1 <=0 || num2 <= 0)
	{
		return -1;
	}
	int min = 0;
	if(num1 < num2)
	{
		min = num1;
	}
	else
	{
		min = num2;
	}
	while(min)
	{
		if(num1%min == 0 && num2%min == 0)
		{
			return min;
		}
		--min;
	}
	return -1;
}

int mcb(int num1, int num2)
{
	if(num1 <= 0 || num2 <= 0)
	{
		return -1;
	}
	int max = 0;
	if(num1 > num2)
	{
		max = num1;
	}
	else
	{
		max = num2;
	}

	while(max)
	{
		if(max%num1 == 0 && max%num2 == 0)
		{
			return max;
		}
		++max;
	}
	return -1;
}

#include <assert.h>
#define MAX 20

void perm(int *a, int size, int s,int *r, int m)
{
    assert(a&&r);
	int iBegin = 0;
	int jBegin = 0;
	int index = 0;
	int flag = 0;
	int *temp = (int *)malloc(sizeof(int)*m);

	for (iBegin = 0 ; iBegin < size; ++iBegin)
	{
		flag = 1;
		r[s] = a[iBegin];
		index = 0;
		for (jBegin = 0; jBegin < size; ++jBegin)
		{
			if(jBegin != iBegin)
			{
				temp[index++] = a[jBegin];
			}
		}
		perm(temp,size-1,s+1,r,m);
	}
	if(flag == 0)
	{
		for (iBegin = 0; iBegin < m; ++iBegin)
		{
			printf("%d ",r[iBegin]);
		}
		printf("\n");
	}
	free(temp);
	temp = NULL;
}

void FindK(int *num , int size, int k)
{
	assert(num);
	int *temp = (int *)malloc(sizeof(int)*k);

	int iBegin = 0;
	int jBegin = 0;
	int max = 0;
	int maxIndex = 0;

	for (iBegin = 0; iBegin < k; ++iBegin)
	{
		maxIndex = iBegin;
		max = num[iBegin];
		for (jBegin = iBegin+1; jBegin < size; ++jBegin)
		{
			if(max < num[jBegin])
			{
				max = num[jBegin];
				maxIndex = jBegin;
			}
		}

		int tem = num[maxIndex];
		num[maxIndex] = num[iBegin];
		num[iBegin] = tem;
		temp[iBegin] = tem;
	}
	for (iBegin = 0; iBegin < k; ++iBegin)
	{
		printf("%d ",temp[iBegin]);
	}
	printf("\n");

	free(temp);
	temp = NULL;
}

void seqSum(int *a, int size)
{
	assert(a);

	int iBegin  = 0;
	int sum = 0;
	int MaxSum = *a;

	for(iBegin = 0; iBegin < size; ++iBegin)
	{
		if(sum > 0)
		{
			sum += a[iBegin];
		}
		else
		{
			sum = a[iBegin];
		}
		if(MaxSum < sum)
		{
			MaxSum  = sum;
		}
	}
	printf("MaxSum = %d \n",MaxSum);
}

int factorSum(int a)
{
	int i = 0;
	int sum = 0;
	for (i = 1; i < a; ++i)
	{
		if(a % i == 0)
		{
			sum += i;
		}
	}
	return sum;
}

void friendly()
{
	int x[3001];
	int i = 0;
	int j = 0;

	for (i = 1 ; i < 3001; ++i)
	{
		x[i] = factorSum(i);
	}

	for (i = 1 ; i < 3001; ++i)
	{
		if(x[i] != -11)
		{
			for (j = i+1; j < 3001; ++j)
			{
				if(x[i] == j && x[j] == i)
				{
					printf(" <%d,%d> ",i, j);
					x[i] = -11;
				}
			}
		}
	}
	printf("\n");
}

#include <string.h>

int IsCircleString(const char *str)
{
	assert(str);
	const char *left = str;
	const char *right = str + strlen(str) - 1;

	while(left <= right)
	{
		if(*left != *right)
		{
			return 0;
		}
		++left;
		--right;
	}
	return 1;
}

int main()
{
	int a[] = {1,3,5,-1};
	int r[MAX];

    perm(a,sizeof(a)/sizeof(int),0,r, sizeof(a)/sizeof(int));

	friendly();

	printf("4 and  6 gcb : %d \n",gcb(4,6));
	printf("4 and  3 mcb : %d \n",mcb(4,3));

	char *str = "abba";
	printf("%s IsCicleString ? %d \n",str, IsCircleString(str));

	int num[] = { -1, 7, 3 ,1, 99, -2, 100, 66};
    FindK(num , sizeof(num)/sizeof(num[0]), 3);

    seqSum(a, sizeof(a)/sizeof(a[0]));
	return 0;
}



