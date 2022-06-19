#include<stdio.h>
#include<stdlib.h>

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))

int dp[2][1000010];
int m[1000010];
int cmax[2][1000010];
int n;
int sum=0;
const int INF = 0x3f3f3f3f;
int Max;
int _max[3];

int getmax(int x) 
{
	for (int i = 1; i < 4; i++)
	{
		Max = -INF;
		for (int j = i; j <= n; j++)
		{
			dp[x][j] = max(dp[x][j - 1], cmax[x][j - 1]) + m[j];
			cmax[x][j - 1] = Max;
			Max = max(Max, dp[x][j]);
		}
		_max[i-1] = Max;
	}
	return Max;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		//fscanf(fp, "%d", &m[i]);
		scanf("%d", &m[i]);
		sum += m[i];
	}
	int ans[2];
	ans[1] = getmax(0);
	for (int i = 1; i <= n; i++)
	{
		m[i] = -m[i];
	}
	ans[0] = sum + getmax(1);
	printf("%d", max(ans[1],ans[0]));
	return 0;
}