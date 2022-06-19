#include<stdio.h> 

#define maxn 30000
int a[maxn];
int Dp[maxn];

int max(int i, int j)
{
	if (i > j) return i;
	else return j;
}

int main()
{
	int N, maxtotal = 0;
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &a[i]);
	}
	for (int k = 0; k < N - 1; k++)
	{
		Dp[k] = max(a[k], a[k + 1]);
	}
	for (int t = 4; t < N + 1; t += 2) {
		for (int k = 0; k < N - t + 1; k++)
		{
			Dp[k] = max(max(Dp[k] + a[k + t - 1], Dp[k + 1] + max(a[k], a[k + t - 1])), Dp[k + 2] + a[k]);
		}
	}
	printf("%d", Dp[0]);
}