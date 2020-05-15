#include <iostream>
#include <functional>
#include <iomanip>
#include <fstream>
#include "gsl/gsl_linalg.h"

//------------------------------------------
//                 print Matrix
//------------------------------------------
void printMatrix(gsl_matrix* a, const int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			std::cout << std::setw(10) << gsl_matrix_get(a, i, j) << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

//------------------------------------------
//                 print Vector
//------------------------------------------
void printVector(gsl_vector* y, const int n)
{
	for (int i = 0; i < n; i++)
	{
		std::cout << std::setw(10) << gsl_vector_get(y, i) << " ";
	}
	std::cout << "\n\n";
}

//------------------------------------------
//                 fill Matrix
//------------------------------------------
void fillMatrix(gsl_matrix* a, const int n)
{
	for (int i = 0; i < n; i++)
	{
		gsl_matrix_set(a, i, i, 4);
		if (i != n - 1)
		{
			gsl_matrix_set(a, i, i + 1, 1);
			gsl_matrix_set(a, i + 1, i, 1);
		}
	}
	gsl_matrix_set(a, 0, 1, 2);
	gsl_matrix_set(a, n - 1, n - 2, 2);
}

//------------------------------------------
//                 function 1
//------------------------------------------
double firstFunction(const double x)
{
	return 1. / (1. + x * x);
}

//------------------------------------------
//                 function 2
//------------------------------------------
double secondFunction(const double x)
{
	return std::cos(2. * x);
}

//------------------------------------------
//                 fill Vector
//------------------------------------------
void fillVector(gsl_vector* y, std::function<double(const double)> const func, const double h, const double xMin, const double deltaX, const int n)
{
	gsl_vector_set(y, 0, func(xMin) + (h / 3.) * (func(xMin + deltaX) - func(xMin - deltaX)) / (2. * deltaX));
	for (int i = 1; i < n - 1; i++)
	{
		gsl_vector_set(y, i, func(xMin + i * h));
	}
	gsl_vector_set(y, n - 1, func(xMin + (n - 1.) * h) - (h / 3) * (func(xMin + (n - 1.) * h + deltaX) - func(xMin + (n - 1.) * h - deltaX)) / (2 * deltaX));
}

//------------------------------------------
//                 copy Vector
//------------------------------------------
void copyVector(gsl_vector* y, gsl_vector* c, const int n, const double h, std::function<double(const double)> const func, const double xMin, const double deltaX)
{
	for (int i = 0; i < n; i++)
	{
		gsl_vector_set(c, i + 1, gsl_vector_get(y, i));
	}
	gsl_vector_set(c, 0, gsl_vector_get(c, 2) - (h / 3.) * (func(xMin + deltaX) - func(xMin - deltaX)) / (2. * deltaX));
	gsl_vector_set(c, n + 1, gsl_vector_get(c, n - 1) + (h / 3.) * (func(xMin + (n - 1.) * h + deltaX) - func(xMin + (n - 1.) * h - deltaX)) / (2 * deltaX));
}

//------------------------------------------
//                 phi
//------------------------------------------


double xind(int i, const int xMin, const double h)
{
	return xMin + (i - 1) * h;
}

double phi(double x, unsigned int i, const int xMin, const double h)
{
	if (x >= xind(i - 2,xMin,h) && x < xind(i - 1, xMin, h))
		return (pow(x - xind(i - 2, xMin, h), 3)) / (pow(h, 3));

	if (x >= xind(i - 1, xMin, h) && x < (xind(i, xMin, h)))
		return (pow(h, 3) + 3 * pow(h, 2) * (x - xind(i - 1, xMin, h)) + 3 * h*pow((x - xind(i - 1, xMin, h)), 2) - 3 * pow((x - xind(i - 1, xMin, h)), 3)) / pow(h, 3);

	if (x >= xind(i, xMin, h) && x < (xind(i + 1, xMin, h)))
		return (pow(h, 3) + 3 * pow(h, 2) * (xind(i + 1, xMin, h) - x) + 3 * h*pow((xind(i + 1, xMin, h) - x), 2) - 3 * pow((xind(i + 1, xMin, h) - x), 3)) / pow(h, 3);

	if (x >= xind(i + 1, xMin, h) && x < (xind(i + 2, xMin, h)))
		return (pow(xind(i + 2, xMin, h) - x, 3)) / (pow(h, 3));

	return 0;
}

//------------------------------------------
//                 interpolation
//------------------------------------------
void interpolate(gsl_vector* c, const double h, const int n, const double xMin, std::ofstream& output, std::function<double(const double)> const func)
{
	double sx = 0.;
	for (double x = -5; x <= 5; x += 0.01)
	{
		sx = 0.;
		for (int i = 0; i < n + 2; i++)
		{
			sx += gsl_vector_get(c, i) * phi(x, i,xMin,h);
		}
		output << x << "\t" << sx << "\t" << func(x) << "\n";
	}
}

//------------------------------------------
//------------------------------------------
//                 calculate
//------------------------------------------
//------------------------------------------
void calculate(gsl_matrix* aMatrix,
	gsl_vector* yVector,
	gsl_vector* cVector,
	std::function<double(double)> const functionPointer,
	std::ofstream& output,
	const int n,
	const double xMin,
	const double h,
	const double deltaX)
{
	// fill matrix a
	fillMatrix(aMatrix, n);
	printMatrix(aMatrix, n);
	// fill vector y
	fillVector(yVector, functionPointer, h, xMin, deltaX, n);
	printVector(yVector, n);
	// solve linear equations
	gsl_linalg_HH_svx(aMatrix, yVector);
	printVector(yVector, n);
	// copy vector y to larger vector c & set first and last element of vector c
	copyVector(yVector, cVector, n, h, functionPointer, xMin, deltaX);
	printVector(cVector, n + 2);
	// save interpolation function values to file
	interpolate(cVector, h, n, xMin, output, functionPointer);
}

//------------------------------------------
//                 MAIN
//------------------------------------------
int main()
{
	const int n = 14;
	const double xMin = -5;
	const double xMax = 5;
	const double h = (xMax - xMin) / static_cast<double>(n - 1);
	const double deltaX = 0.01;


	std::function<double(const double)> functionPointer;
	gsl_matrix* aMatrix = gsl_matrix_calloc(n, n);
	gsl_vector* yVector = gsl_vector_calloc(n);
	gsl_vector* cVector = gsl_vector_calloc(n + 2);
	std::ofstream output;
	std::ofstream output2;
	output.open("results_2_14.txt");
	output2.open("results_nods_2_14.txt");

	functionPointer = secondFunction;
	calculate(aMatrix, yVector, cVector, functionPointer, output, n, xMin, h, deltaX);

	for (double i = xMin; i <= xMax; i += h)
	{
		output2 << i << "  " << functionPointer(i) << std::endl;
	}

	output.close();
	output2.close();
	gsl_matrix_free(aMatrix);
	gsl_vector_free(yVector);
	gsl_vector_free(cVector);

	return 0;
}