#include <iostream>
#include <fstream>
#include <iomanip>

#include <gsl\gsl_eigen.h>
#include <gsl\gsl_complex.h>
#include <gsl\gsl_complex_math.h>

double x_i(const int i, double L, const double deltax);
void reset_matrix(gsl_matrix* M, const int n);
void set_matrix(gsl_matrix* M, int alfa, const int n, const double N, const double L, const double deltax);
void eval_to_file(std::ofstream* file_name, gsl_vector_complex* eval, int alfa);
void evec_to_file(std::ofstream* file_name, gsl_matrix_complex* evec, const int n, const double deltax, const double L);

int main()
{
	std::ofstream file; // pierwiastki 6 najmniejszych wartosci wlasnych
	std::ofstream file2; // wektory wlasne dla alfa=0
	std::ofstream file3; // wektory wlasne dla alfa=100

	file.open("results.txt");
	file2.open("results_first_half.txt");
	file3.open("results_second_half.txt");

	const double L = 10.0, N = 1.0;
	const int n = 200;
	const double deltax = L / (n + 1.);

	gsl_matrix* A = gsl_matrix_calloc(n, n);
	gsl_vector_complex* eval = gsl_vector_complex_calloc(n); // wektor wartosci wlasnych
	gsl_matrix_complex* evec = gsl_matrix_complex_calloc(n, n); // macierz prawostronnych wektorow wlasnych
	gsl_eigen_nonsymmv_workspace* w = gsl_eigen_nonsymmv_alloc(n);

	for (int alfa=0; alfa <= 100; alfa += 2)
	{
		reset_matrix(A, n);
		set_matrix(A, alfa, n, N, L, deltax);
		gsl_eigen_nonsymmv(A, eval, evec, w);
		gsl_eigen_nonsymmv_sort(eval, evec, GSL_EIGEN_SORT_ABS_ASC);

		eval_to_file(&file, eval, alfa);

		if (alfa == 0)
		{
			evec_to_file(&file2, evec, n, deltax, L);
		}
		else if (alfa == 100)
		{
			evec_to_file(&file3, evec, n, deltax, L);
		}
	}

	gsl_matrix_free(A);
	gsl_vector_complex_free(eval);
	gsl_matrix_complex_free(evec);
	gsl_eigen_nonsymmv_free(w);

	file.close();
	file2.close();
	file3.close();

	return 0;
}

double x_i(const int i, double L, const double deltax)
{
	return -0.5 * L + (deltax * (i + 1.));
}

void reset_matrix(gsl_matrix* M, const int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			gsl_matrix_set(M, i, j, 0);
		}
	}
}

void set_matrix(gsl_matrix* M, int alfa, const int n, const double N, const double L, const double deltax)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			double xi = x_i(i, L, deltax);
			double p = 1 + (4. * alfa * xi * xi);
			if (i == j)
				gsl_matrix_set(M, i, j, 2. * N / (p * deltax * deltax));
			if (i == j - 1)
				gsl_matrix_set(M, i, j, -1. * N / (p * deltax * deltax));
			if (i == j + 1)
				gsl_matrix_set(M, i, j, -1. * N / (p * deltax * deltax));
		}
	}
}

void eval_to_file(std::ofstream* file_name, gsl_vector_complex* eval, int alfa)
{
	for (int i = 0; i < 6; i++)
	{
		gsl_complex cval = gsl_vector_complex_get(eval, i);
		double val = GSL_REAL(cval);
		*file_name << alfa << "\t" << std::fixed << std::setprecision(6) << sqrt(val);
	}

	*file_name << "\n";
}

void evec_to_file(std::ofstream* file_name, gsl_matrix_complex* evec, const int n, const double deltax, const double L)
{
	for (int i = 0; i < 6; i++)
	{
		*file_name << i << " " << i << "\n";
		*file_name << std::fixed << std::setprecision(6) << -5.0 << " " << 0.0 << "\n";

		for (int j = 0; j < n; j++)
		{
			gsl_complex cv = gsl_matrix_complex_get(evec, j, i);
			*file_name << std::fixed << std::setprecision(6) << x_i(j, L, deltax) << " " << GSL_REAL(cv) << "\n";
		}

		*file_name << std::fixed << std::setprecision(6) << 5.0 << " " << 0.0 << "\n";
	}
}
