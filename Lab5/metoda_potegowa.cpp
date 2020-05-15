#include <iostream>
#include <iomanip>
#include <cmath>
#include <gsl/gsl_matrix.h>

const int n = 7, K = 7, IT_MAX = 12;

void set_matrix(gsl_matrix* M);
void set_matrix_with_matrix(gsl_matrix* M, gsl_matrix* M2);
double vector_vector(gsl_vector* V1, gsl_vector* V2);
void matrix_vector(gsl_vector* result, gsl_vector* V, gsl_matrix* M);
void matrix_matrix(gsl_matrix* result, gsl_matrix* M, gsl_matrix* M2);
void tensor(gsl_matrix* M, gsl_vector* lambda, gsl_vector* x, int k);
void show_matrix(gsl_matrix* M);
void show_eigen_values(gsl_matrix* approximations);

int main()
{
	gsl_matrix* A = gsl_matrix_calloc(n, n);
	gsl_matrix* W = gsl_matrix_calloc(n, n);
	gsl_matrix* X = gsl_matrix_calloc(n, n);
	gsl_matrix* approximations = gsl_matrix_calloc(IT_MAX, IT_MAX);
	gsl_matrix* D = gsl_matrix_calloc(n, n);
	gsl_matrix* X_transposed = gsl_matrix_calloc(n, n);
	gsl_matrix* AX = gsl_matrix_calloc(n, n);

	gsl_vector* lambda = gsl_vector_calloc(n);
	gsl_vector* x_v = gsl_vector_calloc(n);
	gsl_vector* x_v_next = gsl_vector_calloc(n);

	set_matrix(A);
	set_matrix_with_matrix(W, A);

	for (int k = 0; k < n; k++)
	{
		gsl_vector_set_all(x_v, 1.0);
		for (int i = 0; i < IT_MAX; i++)
		{
			matrix_vector(x_v_next, x_v, W);
			gsl_vector_set(lambda, k, vector_vector(x_v_next, x_v) / vector_vector(x_v, x_v));
			gsl_matrix_set(approximations, i, k, gsl_vector_get(lambda, k));
			for (int j = 0; j < n; j++)
			{
				gsl_vector_set(x_v, j, gsl_vector_get(x_v_next, j) / sqrt(vector_vector(x_v_next, x_v_next)));
			}
		}
		tensor(W, lambda, x_v, k);
		for (int i = 0; i < n; i++)
		{
			gsl_matrix_set(X, i, k, gsl_vector_get(x_v, i));
		}
	}
	set_matrix_with_matrix(X_transposed, X);
	gsl_matrix_transpose(X_transposed);
	matrix_matrix(AX, A, X);
	matrix_matrix(D, X_transposed, AX);

	show_matrix(D);
	show_eigen_values(approximations);

	gsl_vector_free(x_v);
	gsl_vector_free(x_v_next);
	gsl_vector_free(lambda);

	gsl_matrix_free(A);
	gsl_matrix_free(W);
	gsl_matrix_free(X);
	gsl_matrix_free(approximations);
	gsl_matrix_free(D);
	gsl_matrix_free(AX);
	gsl_matrix_free(X_transposed);
}

void set_matrix(gsl_matrix* M)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			gsl_matrix_set(M, i, j, 1. / (sqrt(2.0 + abs(i - j))));
		}
	}
}

void set_matrix_with_matrix(gsl_matrix* M, gsl_matrix* M2)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			gsl_matrix_set(M, i, j, gsl_matrix_get(M2, i, j));
		}
	}
}

double vector_vector(gsl_vector* V1, gsl_vector* V2)
{
	double result = 0.0;
	for (int i = 0; i < n; i++)
	{
		result += gsl_vector_get(V1, i) * gsl_vector_get(V2, i);
	}
	return result;
}

void matrix_vector(gsl_vector* result, gsl_vector* V, gsl_matrix* M)
{
	gsl_vector_set_all(result, 0.0);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			gsl_vector_set(result, i, (gsl_vector_get(result, i) + (gsl_matrix_get(M, i, j) * gsl_vector_get(V, j))));
		}
	}
}

void matrix_matrix(gsl_matrix* result, gsl_matrix* M, gsl_matrix* M2)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < n; k++)
			{
				gsl_matrix_set(result, i, j, gsl_matrix_get(result, i, j) + (gsl_matrix_get(M, i, k) * gsl_matrix_get(M2, k, j)));
			}
		}
	}
}

void tensor(gsl_matrix* M, gsl_vector* lambda, gsl_vector* x, int k)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			gsl_matrix_set(M, i, j, gsl_matrix_get(M, i, j) - gsl_vector_get(lambda, k) * gsl_vector_get(x, i) * gsl_vector_get(x, j));
		}
	}
}

void show_matrix(gsl_matrix* M)
{
	for (int i = 0; i < n; i++)
	{
		std::cout << i << "   ";
		for (int j = 0; j < n; j++)
		{
			std::cout << std::scientific << std::setprecision(5) << gsl_matrix_get(M, i, j) << "   ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

void show_eigen_values(gsl_matrix* approximations)
{
	for (int i = 0; i < IT_MAX; i++)
	{
		std::cout << i << "   ";
		for (int j = 0; j < n; j++)
		{
			std::cout << std::scientific << std::setprecision(10) << gsl_matrix_get(approximations, i, j) << "   ";
		}
		std::cout << "\n";
	}
}