#include <iostream>
#include <iomanip>
#include <complex>
#include <vector>
#include <fstream>

std::complex<double> jremainder(std::vector<std::complex<double>> a, std::vector<std::complex<double>>& b, int l, std::complex<double> zj, const int n)
{
	std::complex<double> Rj;
	b[n] = 0.;
	for (int i = n - 1; i >= 0; i--)
	{
		b[i] = a[i + 1] + (zj * b[i + 1]);
	}
	Rj = a[0] + zj * b[0];
	return Rj;
}
std::ostream& operator<<(std::ostream& os, std::complex<double>& z)
{
	return os << z.real() << "    " << z.imag();
}
void calculate(const int n, const int IT_MAX, std::complex<double> z0, std::complex<double> Rj, std::complex<double> Rj_prim,
			std::vector<std::complex<double>> a, std::vector<std::complex<double>> b, std::vector<std::complex<double>> c, std::ofstream& file)
{
	std::complex<double> zj;
	for (int l = n; l >= 1; l--)
	{
		zj = z0;
		std::cout << std::fixed << std::setprecision(5) << std::setw(8) << z0 << std::endl;
		file << std::fixed << std::setprecision(5) << std::setw(8) << z0 << std::endl;
		for (int j = 1; j <= IT_MAX; j++)
		{
			Rj = jremainder(a, b, l, zj, n);
			Rj_prim = jremainder(b, c, l - 1, zj, n - 1);
			zj -= Rj / Rj_prim;
			std::cout << std::fixed << std::setprecision(5) << std::setw(8) << zj << std::endl;
			file << std::fixed << std::setprecision(5) << std::setw(8) << zj << std::endl;
		}
		std::cout << "\n";
		for (int i = 0; i < n + 1; i++)
		{
			a[i] = b[i];
		}
	}
}

int main()
{
	using namespace std::complex_literals;
	const int n = 4, IT_MAX = 20;

	std::ofstream file;
	std::ofstream file2;
	file.open("results_z1.txt");
	file2.open("results_z2.txt");

	std::complex<double> z0 = 0.;
	std::complex<double> zj = 0.;
	std::complex<double> Rj = 0.;
	std::complex<double> Rj_prim = 0.;

	std::vector<std::complex<double>> a = { 16.+8.i, -20.+14.i, 4.-8.i, -4.+1.i, 1. };
	std::vector<std::complex<double>> b = { 0., 0., 0., 0., 0. };
	std::vector<std::complex<double>> c = { 0., 0., 0., 0. };

	calculate(n, IT_MAX, z0, Rj, Rj_prim, a, b, c, file);
	z0 = -10. - 10.i;
	calculate(n, IT_MAX, z0, Rj, Rj_prim, a, b, c, file2);

	file.close();
	file2.close();
	return 0;
}
