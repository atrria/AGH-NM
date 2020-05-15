#include <iostream>
#include <cmath>
#include <fstream>

void print(double* t, const int N)
{
	for (int i = 0; i < N; i++)
	{
		std::cout << t[i] << std::endl;
	}
}

int main()
{
    const int N = 10000;
    int iter = 0;
	std::fstream file;
	file.open("out.txt", std::ios::out);
	double h = 0.02;
	double F0 = 0.1;
	double Omega = 0.8;
	double beta = 0.4;
	double a1 = 1;
	double a2 = (h * h) - 2 - beta * h;
	double a3 = 1 + beta * h;

	double xn[N], xs[N];
	double b[N];

	double d0[N];
	double d1[N];
	double d2[N];

	double sumaxs = 10;
	double sumaxn = 1;

	d0[0] = 1;
	d0[1] = 1;
	d1[0] = 0;
	d1[1] = -1;
	d2[0] = 0;
	d2[1] = 0;
	b[0] = 1;
	b[1] = 0;

	for (int i = 2; i < N; i++)
	{
		d0[i] = a3;
		d1[i] = a2;
		d2[i] = a1;
		b[i] = F0*h*h*sin(Omega*h*i);
	}

	for (int i = 0; i < N; i++)
	{
		xn[i] = 0;
		xs[i] = 0;
	}

	while (true)
	{
		if (fabs(sumaxs-sumaxn)<1e-5)
			break;
		xn[0] = b[0] / d0[0];
		xn[1] = (b[1] - d1[1] * xs[0]) / d0[1];
		for (int i = 2; i < N; i++)
		{
			xn[i] = (b[i] - d1[i] * xs[i - 1] - d2[i] * xs[i - 2]) / d0[i];
		}
		sumaxs = 0;
		sumaxn = 0;
		for (int i = 0; i < N; i++)
		{
			sumaxs += xs[i] * xs[i];
			sumaxn += xn[i] * xn[i];
		}
		for (int i = 0; i < N; i++)
		{
			xs[i] = xn[i];
		}
		iter++;
	}

	print(xn, N);
	std::cout << "Po " << iter << " iteracjach\n";
	for (int i = 0; i < N; i++)
	{
		file << xn[i] << std::endl;
	}
	return 0;
}