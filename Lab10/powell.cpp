#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <functional>

constexpr double xMax = 1.;
constexpr double h = 0.01;
constexpr double eps = 1e-8;
const std::string file_name = "results";

double f1_fun(double x)
{
	return std::log(std::pow(x, 5) + 3. * std::pow(x, 2) + x + 9.);
}
double f2_fun(double x)
{
	return std::pow(x, 6);
}
void f_to_file(double xMin)
{
	std::ofstream file(file_name + "_f.txt");
	for (double i = xMin; i <= xMax; i += h)
	{
		file << i << "   " << std::setw(8) << f1_fun(i) << std::endl;
	}
	file.close();
}
bool is_desc_seq(std::function<double(double)> func, double x1, double x2, double x3)
{
	return (func(x1) > func(x2) && func(x2) > func(x3));
}
double st_order_diff_quotient(std::function<double(double)> func, double x1, double x2)
{
	return (func(x2) - func(x1)) / (x2 - x1);
}
double nd_order_diff_quotient(std::function<double(double)> func, double x1, double x2, double x3)
{
	return (st_order_diff_quotient(func, x2, x3) - st_order_diff_quotient(func, x1, x2)) / (x3 - x1);
}
double approx_min_x(std::function<double(double)> func, double x1, double x2, double x3)
{
	return (x1 + x2) / 2. - (st_order_diff_quotient(func, x1, x2) / (2 * nd_order_diff_quotient(func, x1, x2, x3)));
}
double nearest_to_xm(double x1, double x2, double x3, double x_m)
{
	if (fabs(x_m - x1) < fabs(x_m - x2))
	{
		if (fabs(x_m - x1) < fabs(x_m - x3))
		{
			return x1;
		}
		return x3;
	}
	else if (fabs(x_m - x2) < fabs(x_m - x3))
	{
		return x2;
	}
	return x3;
}
double& farthest_from_xm(double& x1, double& x2, double& x3, double x_m)
{
	if (fabs(x_m - x1) > fabs(x_m - x2))
	{
		if (fabs(x_m - x1) > fabs(x_m - x3))
		{
			return x1;
		}
		return x3;
	}
	else if (fabs(x_m - x2) > fabs(x_m - x3))
	{
		return x2;
	}
	return x3;
}
void save_to_file(std::function<double(double)> func, std::ofstream& file, int it, double x1, double x2, double x3, double x_m)
{
	file << it << "   " << std::setw(12) << x1 << "   " << std::setw(12) << x2 << "   " << std::setw(12) << x3 << "   " << std::setw(12) << x_m << "   ";
	file << std::setw(12) << st_order_diff_quotient(func, x1, x2) << "   ";
	file << std::setw(12) << nd_order_diff_quotient(func, x1, x2, x3) << std::endl;
}
void powell(std::function<double(double)> func, const double x, const int it_num, const std::string full_file_name)
{
	double x1 = x;
	double x2 = x1 + h;
	double x3 = x2 + h;
	double x_m;

	std::ofstream file(full_file_name);

	if (!is_desc_seq(func, x1, x2, x3))
	{
		x2 = x1 - h;
		x3 = x2 - h;
	}
	for (int i = 0; i < it_num; i++)
	{
		x_m = approx_min_x(func, x1, x2, x3);
		save_to_file(func, file, i + 1, x1, x2, x3, x_m);

		if (fabs(nearest_to_xm(x1, x2, x3, x_m) - x_m) < eps)
		{
			file << "\n";
			file.close();
			return;
		}

		std::swap(farthest_from_xm(x1, x2, x3, x_m), x_m);
	}
	file << "\n";
	file.close();
}
void powell_interpolation(std::function<double(double)> func, const double xMin, const int it_num, const char file_num)
{
	const std::string full_file_name = file_name + file_num + ".txt";
	powell(func, xMin, it_num, full_file_name);
}
int main()
{
	std::function<double(double)> func;

	func = f1_fun;
	f_to_file(-1.5);
	powell_interpolation(func , -0.5, 10, '1');

	func = f1_fun;
	powell_interpolation(func , -0.9, 10, '2');

	func = f2_fun;
	powell_interpolation(func , 1.5, 100, '3');

	return 0;
}
