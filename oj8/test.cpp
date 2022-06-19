#include<iostream>
#include<complex>
#include<cmath>
#include<iomanip>
#define PI 3.14159265358979323846

using namespace std;

typedef complex<double> complexf;
double a[101];//多项式实系数
complexf z[101];//根
complexf _z[101];//迭代根
int N;//幂次
int _count[101] = { 0 };//重根判断

//求值
complexf fun(double* a, complexf x)
{
	complexf f = a[0];
	for (int i = 1; i <= N; i++)
	{
		f = a[i] + f * x;
	}
	return f;
}

double fun(double* a, double x)
{
	double f = a[0];
	for (int i = 1; i <= N; i++)
	{
		f = a[i] + f * x;
	}
	return f;
}

//求导
complexf dfun(double* a, complexf x, int c)
{
	int m = 1;
	complexf df;
	for (int j = 0; j < c; j++)
	{
		m = m * (N - j);
	}
	df = a[0] * m;
	for (int i = 1; i < N - c + 1; i++)
	{
		m = 1;
		for (int j = 0; j < c; j++)
		{
			m = m * (N - i - j);
		}
		df = a[i] * m + df * x;
	}
	return df;
}

double dfun(double* a, double x)
{
	double df = a[0] * N;
	for (int i = 1; i < N; i++)
	{
		df = a[i] * ((double)N - (double)i) + df * x;
	}
	return df;
}

complexf dfun(double* a, complexf x)
{
	complexf df = a[0] * N;
	for (int i = 1; i < N; i++)
	{
		df = a[i] * ((complexf)N - (complexf)i) + df * x;
	}
	return df;
}

//霍纳系数
void honor(double* c, double z_p) {
	for (int i = 0; i < N; i++)
	{
		for (int j = 1; j <= N; j++) {
			c[j] += c[j - 1] * z_p;
		}
	}
	c[0] = fabs(c[0]);
	for (int i = 1; i <= N; i++)
	{
		c[i] = -fabs(c[i]);
	}
}

//牛顿法
double newton(double* c, double r, int iter, double eps)
{
	double df, f;
	for (int i = 0; i < iter; i++)
	{
		f = fun(c, r);
		df = dfun(c, r);
		r = r - f / df;
		if (fabs(f / df) < eps)
			return r;
	}
	return r;
}

//aberth初值
void aberth(int iter, double eps)
{
	double z_p = -a[1] / a[0] / (double)N;
	double c[101];
	for (int i = 0; i <= N; i++)
	{
		c[i] = a[i];
	}
	honor(c, z_p);
	double r = 99.0;
	r = newton(c, r, iter, eps);
	double theta;
	for (int i = 0; i < N; i++)
	{
		theta = (2 * PI / (double)N) * i + PI / (2.0 * N);
		z[i] = (complexf)z_p + r * complexf(cos(theta), sin(theta));
		//cout << z[i] << endl;
	}
}


bool operator < (complexf a, complexf b) {
	return (a.real() < b.real()) || (a.real() == b.real() && abs(a.imag()) < abs(b.imag()));
}

void weierstrass(int iter, double eps)
{
	complexf f, df;
	double e;
	complexf w,z_c;
	for (int i = 0; i < iter; i++)
	{
		e = 0;
		for (int j = 0; j < N; j++)
		{
			z_c = 0;
			_count[j] = 0;
			for (int k = 0; k < N; k++)
			{
				if (abs(z[j] - z[k]) < 0.01) {
					_count[j]++;
					continue;
				}
				z_c += 1.0 / (z[j] - z[k]);
			}
			//f = fun(a, z[j]);
			//df = dfun(a, z[j]);
			f = dfun(a, z[j],_count[j]-1);
			df = dfun(a, z[j], _count[j]);
			w = f / df / (1.0 - f / df * z_c);
			z[j] = z[j] - w;
			if (e < abs(f/df))e = abs(f/df);
		}
		if (e < eps)return;
	}
}

void out() {
	complexf temp;
	int tem;
	for (int i = 0; i < N; i++)
	{
		for (int j = N - 1; j > i; j--) {
			if (z[j - 1] < z[j]) {
				temp = z[j];
				z[j] = z[j - 1];
				z[j - 1] = temp;
			}
		}
	}
	for (int i = 0; i < N; i++)
	{
		if (z[i].imag()<-0.00005)continue;
		//int j = 1;
		//while (abs(dfun(a, z[i], j)) < 0.1) {
			//j++;
		//}
		//for (int k = 0; k < j; k++)
		//{
		cout << setiosflags(ios::fixed) << setprecision(4) << z[i].real() << "      " << abs(z[i].imag())<< endl;
		if (abs(z[i].imag()) > 0.00005)
			cout << setiosflags(ios::fixed) << setprecision(4) << z[i].real() << "      " << -abs(z[i].imag()) << endl;
	//	}
	}
}

int main()
{
	cin >> N;
	for (int i = 0; i <= N; i++)
	{
		cin >> a[i];
	}
	aberth(100, 0.001);
	//cout << "\n" << newton(a, 5, 100, 0.0001)<<endl;
	weierstrass(1000, 0.00001);
	out();
	return 0;
}