#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <fstream>

void show_matrix(std::vector< std::vector<double > > vec, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			std::cout << std::setw(10) << vec[i][j] << " ";
		}
		std::cout << "\n\n";
	}
}
void fill_vector_x(std::vector<double>& x, double xMin, double xMax, int n)
{
	x[0] = xMin;
	for (int i = 1; i <= n; i++)
	{
		//x[i] = x[i - 1] + ((xMax - xMin) / n); // rownoodlegle
		x[i] = ((xMin - xMax) * cos(M_PI * (2.0 * i + 1.0) / (2.0 * n + 2.0)) + (xMin + xMax)) / 2.0; // optymalizacja zerami wielomianow Czebyszewa
	}
}
void fill_vector_y(std::vector< std::vector<double>>& y, std::vector<double> x, int n, std::ofstream& file2)
{
	for (int i = 0; i <= n; i++)
	{
		y[i][0] = 1. / (1. + x[i] * x[i]);
		file2 << x[i] << " " << y[i][0] << "\n";
	}
}
void calculate_differential_quotient(std::vector< std::vector<double>>& m, std::vector<double> x, int n)
{
	for (int j = 1; j <= n; j++)
	{
		for (int i = j; i <= n; i++)
		{
			m[i][j] = (m[i][j - 1] - m[i - 1][j - 1]) / (x[i] - x[i - j]);
		}
	}
}
double calculate_Wn(std::vector < std::vector < double > > y, std::vector <double> x, int n, double k)
{
	double result = 0., product = 0.;
	for (int j = 0; j <= n; j++)
	{
		product = 1.;
		for (int i = 0; i < j; i++)
		{
			product *= (k - x[i]);
		}
		result += ( y[j][j] * product );
	}
	return result;
}
void save_Wn_to_file(std::vector < std::vector < double > > y, std::vector <double> x, int n, double xMin, double xMax, std::ofstream& file)
{
	for (double k = xMin; k <= xMax; k += 0.01)
	{
		std::cout << std::setw(10) << k << " " << calculate_Wn(y, x, n, k) << " " << 1. / (1. + k * k) << "\n";
		file << std::setw(10) << k << " " << calculate_Wn(y, x, n, k) << " " << 1. / (1. + k * k) << "\n";
	}
	std::cout << std::endl;
	file << "\n";
}

int main()
{
	double xMin = -5, xMax = 5;
	std::ofstream file;
	file.open("results3.txt");
	std::ofstream file2;
	file2.open("results2.txt");

	for (int n = 5; n <= 20; n += 5)
	{
		std::vector < std::vector < double > > inter (n+1, std::vector < double > (n+1));
		std::vector <double> x(n + 1);
		std::vector < std::vector <double> > W(n, std::vector < double >(n));
		fill_vector_x(x, xMin, xMax, n);
		fill_vector_y(inter, x, n, file2);
		calculate_differential_quotient(inter, x, n);
		save_Wn_to_file(inter, x, n, xMin, xMax, file);
	}

	file.close();
	file2.close();

	return 0;
}