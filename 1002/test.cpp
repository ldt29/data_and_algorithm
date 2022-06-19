#include<iostream>
#include<string>
using namespace std;
const int Inf = 2147483647;
const int Num = 2;
const int Mod = 9973;
 
struct Matrix {//the class of 2*2 Matrix
	int M[Num][Num];
	void iniMatrix() {
		M[1][0] = 0;
		M[0][1] = 0;
		for (int i = 0; i < Num; i++)
		{
			M[i][i] = 1;
		}
	};
};

Matrix Multiply(Matrix a, Matrix b) {// the multplication of 2*2 Matrix
	Matrix answer;
	for (int i = 0; i < Num; i++)
	{
		for (int j = 0; j < Num; j++)
		{
			answer.M[i][j] = 0;
			for (int k = 0; k < Num; k++)
			{
				answer.M[i][j] += (a.M[i][k] * b.M[k][j]) ;
				answer.M[i][j] %= Mod;
			}
		}
	}
	return answer;
}

Matrix QuicklyMutiply(Matrix a, int num) {// the quick multplication of 2 * 2 Matrix
	Matrix answer;
	answer.iniMatrix();
	while (num) {
		if (num & 1) {
			answer = Multiply(answer, a);
		}
		a = Multiply(a, a);
		num >>= 1;
	}
	return answer;
}

int main() {
	Matrix a;
	a.M[0][0] = 1;
	a.M[1][1] = 0;
	a.M[0][1] = 1;
	a.M[1][0] = 1;
	int n,i=0;
	cin >> n;
	int Fibonacci[20] = {0};
	while (n--)
	{
		cin >> Fibonacci[i];
		i++;
	}
	n++;
	while(n<i)
	{
		cout << QuicklyMutiply(a, Fibonacci[n]).M[0][1]<< endl;
		n++;
	}
	return 0;
}