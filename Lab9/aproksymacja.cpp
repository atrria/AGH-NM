#include <iostream>
#include <fstream>
#include <iomanip>
#include <gsl/gsl_linalg.h>

constexpr int sigma = 4, x0 = 2;
constexpr double xMin = -3. * sigma + double(x0);
constexpr double xMax = 3. * sigma + double(x0);
constexpr double a0 = -1.*(x0 * x0) / 2. / (sigma * sigma);
constexpr double a1 = double(x0) / (sigma * sigma);
constexpr double a2 = -1. / 2. / (sigma * sigma);

double f_function(int value_number, const double h)
{
    int number = 0;
    for (double x = xMin; x <= xMax + h; x += h)
    {
        number++;
        if (number == value_number)
        {
            return a0 + (a1 * x) + (a2 * x * x);
        }
    }
}

double x_value(int value_number, const double h)
{
    int number = 0;
    for (double x = xMin; x <= xMax + h; x += h)
    {
        number++;
        if (number == value_number)
        {
            return x;
        }
    }
}

void show_matrix(gsl_matrix* m)
{
    for (int i = 0; i < sigma; i++)
    {
        for (int j = 0; j < sigma; j++)
        {
            std::cout << std::setw(8) << gsl_matrix_get(m, i, j) << "  ";
        }
        std::cout << "\n";
    }
}

void show_vector(gsl_vector* v)
{
    for (int i = 0; i < sigma; i++)
    {
        std::cout << std::setw(8) << gsl_vector_get(v, i) << "\n";
    }
}

void set_matrix(gsl_matrix* m, const int n, const double h)
{
    for (int i = 1; i <= sigma; i++)
    {
        for (int k = 1; k <= sigma; k++)
        {
            double value = 0.;
            for (int j = 1; j <= n; j++)
            {
                value += std::pow(x_value(j, h), i + k - 2);
            }
            gsl_matrix_set(m, i - 1, k - 1, value);
        }
    }
}

void set_vector(gsl_vector* v, const int n, const double h)
{
    for (int k = 1; k <= sigma; k++)
    {
        double value = 0.;
        for (int j = 1; j <= n; j++)
        {
            value += f_function(j, h) * std::pow(x_value(j, h), k - 1);
        }
        gsl_vector_set(v, k - 1, value);
    }
}

void input_results_to_files(std::ofstream& file, std::ofstream& file2, gsl_vector* r, const int n, const double h)
{
    for (int i = 1; i <= n; i++)
    {
        file << x_value(i, h) << "   " << std::exp(gsl_vector_get(r, 0) + gsl_vector_get(r, 1) * x_value(i, h) + gsl_vector_get(r, 2) * std::pow(x_value(i, h), 2) + gsl_vector_get(r, 3) * std::pow(x_value(i, h), 3))<<"\n";
        file2 << x_value(i, h) << "   " << std::exp(f_function(i, h)) << "\n";
    }
}

int main()
{
    int n = 11;
    double h = (xMax - xMin) / (n - 1.);

    gsl_matrix* G = gsl_matrix_calloc(sigma, sigma);
    gsl_vector* r = gsl_vector_calloc(sigma);

    std::ofstream file("results.txt");
    std::ofstream file2("results2.txt"); 

    set_matrix(G, n, h);
    set_vector(r, n, h);

    show_matrix(G);
    std::cout << "--------------------------------------------------------\n";
    show_vector(r);

    gsl_linalg_HH_svx(G, r);
    std::cout << "--------------------------------------------------------\n";
    show_vector(r);
    
    input_results_to_files(file, file2, r, n, h);

    gsl_matrix_free(G);
    gsl_vector_free(r);

    file.close();
    file2.close();

    return 0;
} 