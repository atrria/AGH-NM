#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <algorithm>
#include <string>

#define _USE_MATH_DEFINES
#include <math.h>

#define NRANSI
extern "C"
{
    #include "nrutil.h"
}
#undef NRANSI

#include "lib/sinft.c"
#include "lib/realft.c"
#include "lib/four1.c"

// signum, zwraca 1 lub -1
int signum(double Y)
{
    return (Y > 0.5f) ? 1 : -1;
}

// wartoœæ sygna³u niezaszumionego
float y0_value(const int n, int i)
{
    float omega = 4.f * (float)(M_PI) / n;
    return std::sin(omega * i) + std::sin(2.f * omega * i) + std::sin(3.f * omega * i);
}

// szum
float a_rand()
{
    float X = rand() / (RAND_MAX + 1.f);
    float Y = rand() / (RAND_MAX + 1.f);
    return 2.f * signum(Y) * X;
}

// wartoœæ sygna³u zaszumionego, zapisywana do pliku
void signal(const int n, float* y, std::ofstream& file)
{
    for (int i = 1; i <= n; i++)
    {
        y[i] = y0_value(n, i) + a_rand();
        file << i << "\t" << y[i] << std::endl;
    }
}

// najwiêksza wartoœæ w wektorze
double max_in_y(const int n, float* y)
{
    double max = y[1];
    for (int i = 2; i <= n; i++)
    {
        if (y[i] > max)
        {
            max = y[i];
        }
    }
    return max;
}

void discrimination_threshold(const int n, float* y)
{
    double max = max_in_y(n, y);

    for (int i = 1; i <= n; i++)
    {
        if (std::fabs(y[i]) <= (0.25f * max)) // niestety nie jestem pewna jaki znak powinien siê tu znajdowaæ - '<' czy '<='
        {
            y[i] = 0.f;
        }
    }
}

void multiply(const int n, float* y)
{
    for (int i = 1; i <= n; i++)
    {
        y[i] *= (2.f / n);
    }
}

// zapis wartoœci zaszumionych/odszumionych do pliku
void y_to_file(const int n, float* y, std::ofstream& file)
{
    for (int i = 1; i <= n; i++)
    {
        file << i << "\t" << y0_value(n, i) << "\t" << y[i] << "\n";
    }
}

void FFT(int k)
{
    std::ofstream file1("results1_" + std::to_string(k) + ".txt");
    std::ofstream file2("results2_" + std::to_string(k) + ".txt");
    std::ofstream file3("results3_" + std::to_string(k) + ".txt");

    const int n = (const int)(std::pow(2, k));
    float* y = new float[n];

    // zapisanie zaszumionego sygna³u do wektora typu float i do pliku
    signal(n, y, file1);

    // transformata sinusowa sygna³u
    sinft(y, n);

    // zapisanie wektora do pliku
    y_to_file(n, y, file2);

    // dyskryminacja na poziomie 25% wartoœci maksymalnej
    discrimination_threshold(n, y);

    // odwrotna transformata sinusowa
    sinft(y, n);

    // przemno¿enie sygna³u
    multiply(n, y);

    // zapisanie wektora do pliku
    y_to_file(n, y, file3);

    file1.close();
    file2.close();
    file3.close();
}

int main()
{
    srand((unsigned int)(time)(NULL));

    FFT(6);
    FFT(8);
    FFT(10);

    system(".\\chart_script.py");

    return 0;
}