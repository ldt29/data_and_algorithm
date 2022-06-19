#include<stdio.h>
#include<math.h>
#include<algorithm>

using namespace std;

int flag;
int N;
double A[1001][1001];
double B[1001][1001];
double x[1000] = { 1 };
double l_x;
double _x[1000] = { 1 };
double y[1000] = { 1 };
double _y[1000] = { 1 };

double modulus(double* x)
{
	double l = 0;
	for (int i = 0; i < N ; i++)
	{
		l += x[i] * x[i];
	}
	return pow(l, 0.5);
}

void A_x()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			x[i] += A[i][j] * _x[j];
		}
	}
}

void B_y()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			y[i] += B[i][j] * _y[j];
		}
	}
}

void power_method() 
{
	int cnt = 0;
	while (1)
	{
		A_x();
		if (cnt == flag)break;
		l_x = modulus(x);
		for (int i = 0; i < N; i++)
		{
			_x[i] = x[i] / l_x;
			x[i] = 0;
		}
		cnt++;
	}
	printf("%.4g ", l_x);
}

void gauss()
{
	for (int i = 0; i < N; i++)
	{
		B[i][i] = 1;
	}
	double k_1 = 0;
	for (int i = 0; i < N; i++) 
	{
		for (int j = i + 1; j < N; j++)
		{
			k_1 = A[j][i] / A[i][i];
			for (int k = i; k < N; k++) 
			{
				A[j][k] = A[j][k] - k_1 * A[i][k];
			}
			for (int k = 0; k < j; k++) 
			{
				B[j][k] = B[j][k] - k_1 * B[i][k];
			}
		}
	}
	for (int i = N - 1; i >= 0; i--)
	{
		if (A[i][i] != 1.0)
		{
			k_1 = A[i][i];
			for (int j = i; j < N; j++)
			{
				A[i][j] = A[i][j] / k_1;
			}
			for (int j = 0; j < N; j++) 
			{
				B[i][j] = B[i][j] / k_1;
			}
		}
		for (int j = i - 1; j >= 0; j--)
		{
			k_1 = A[j][i];
			for (int k = i; k < N; k++)
			{
				A[j][k] = A[j][k] - k_1 * A[i][k];
			}
			for (int k = 0; k < N; k++)
			{
				B[j][k] = B[j][k] - k_1 * B[i][k];
			}
		}
	}
}

void anti_power_method()
{
	gauss();
	int cnt = 0;
	while (1)
	{
		B_y();
		if (cnt == flag)break;
		l_x = modulus(y);
		for (int i = 0; i < N; i++)
		{
			_y[i] = y[i] / l_x;
			y[i] = 0;
		}
		cnt++;
	}
	printf("%.4g", 1/l_x);
}

int main()
{
	scanf("%d", &N);
	for (int i = 0; i < N; i++) 
	{
		for (int j = 0; j < N; j++) 
		{
			scanf("%lf", &A[i][j]);
		}
	}
	if (N < 800)flag = 3000;
	else flag = 1000;
	power_method();
	anti_power_method();
	return 0;
}