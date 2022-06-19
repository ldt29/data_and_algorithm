#include<stdio.h>
#include<iostream>
#include<stack>

using namespace std;

int M;
int n;
char S[1010] = { "\0" };
char t[1010] = { "\0" };
int A[1010][1020] = { 0 };
//int T[1000] = { 0 };
int x[1010] = { 0 };

void buildbase()
{
	for (int i = 0; i < n; i++)
	{
		A[i][0] = S[i] ^ 48;
		A[i][n] = t[i] ^ 48;
	}
	for (int i = 1; i < n; i++)
	{
		A[0][i] = A[n - 1][i - 1];
		for (int j = 1; j < n; j++)
		{
			A[j][i] = A[j - 1][i - 1];
		}
	}
}


void swap(int a, int b) {
	int temp;
	for (int i = 0; i <= n; i++)
	{
		temp = A[a][i];
		A[a][i] = A[b][i];
		A[b][i] = temp;
	}
}

void Gauss()
{
	for (int i = 0; i < n - 1; i++)
	{
		if (!A[i][i]) {
			for (int j = i + 1; j < n; j++) {
				if (A[j][i]) {
					swap(i, j);
					break;
				}
			}
		}
		for (int j = i + 1; j < n; j++)
		{
			if (A[j][i]) {
				for (int k = i; k <= n; k++)
				{
					A[j][k] = (A[i][k] - A[j][k] + 2) % 2;
				}
			}
		}
	}
	int cnt = 0;
	for (int i = 0; i < n; i++)
	{
		if (!A[i][i]) {
			if (A[i][n]) {
				printf("N\n");
				A[0][0] = 2;
				return;
			}
			else
				cnt++;
		}
	}
	while (cnt--) {
		A[n - cnt - 1][n - cnt - 1] = 1;
	}
	for (int i = n - 1; i > 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (A[j][i]) {
				//A[j][i] = (A[j][i] - A[i][i] + 2) % 2;
				A[j][n] = (A[j][n] - A[i][n] + 2) % 2;
			}
		}
	}
	return;
}
stack<char> s;
int main()
{
	scanf("%d", &M);
	for (int i = 0; i < M; i++)
	{

		scanf("%d", &n);
		scanf("%s", S);
		scanf("%s", t);
		buildbase();
		Gauss();
		if (A[0][0] == 2)continue;
		int flag = 0;
		for (int j = 0; j < n; j++)
		{
			if (A[j][n])
			{
				for (int k = 0; k < j - flag; k++)
				{
					s.push('A');
				}
				s.push('B');
				flag = j;
			}
		}
		if (s.empty()) {
			printf("A");
		}
		while (s.size()) {
			printf("%c", s.top());
			s.pop();
		}
		printf("\n");
	}
	return 0;
}