#include <stdio.h>

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

void perm(int *a, int n, int s,int *r, int m)
{
    assert(a&&r);
	int i = 0;
	int j = 0;
	int k = 0;
	int flag = 0;
	int b[3] ;

	for (i = 0 ; i < n; ++i)
	{
		flag = 1;
		r[s] = a[i];
		j = 0;
		for (k = 0; k < n; ++k)
		{
			if(k != i)
			{
				b[j++] = a[k];
			}
		}
		perm(b,n-1,s+1,r,m);
	}
	if(flag == 0)
	{
		for (k = 0; k < m; ++k)
		{
			printf("%d ",r[k]);
		}
		printf("\n");
	}
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
	int a[3] = {1,3,5};
	int r[MAX];

    perm(a,3,0,r, 3);

	friendly();

	printf("4 and  6 gcb : %d \n",gcb(4,6));
	printf("4 and  3 mcb : %d \n",mcb(4,3));

	char *str = "abba";
	printf("%s IsCicleString ? %d \n",str, IsCircleString(str));

	return 0;
}



