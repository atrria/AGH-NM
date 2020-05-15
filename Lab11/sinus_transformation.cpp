#include <iostream>
#include <ctime>
#include <cstdlib>
#include <gsl\gsl_linalg.h>
#include <gsl\gsl_fft_real.h>
#include <gsl\gsl_fft.h>
#include <gsl\gsl_fft_halfcomplex.h>
#include <fstream>
#include <algorithm>

/*
    Nie jestem przekonana czy u¿ywam dobrych funkcji FFT.
    Jeœli u¿yjê gsl_fft_real_transform lub gsl_fft_real_radix2_transform to pierwszy wykres wydaje siê byæ dobry (odbity wzglêdem osi X)
    jednak nie istniej¹ analogiczne funkcje obliczaj¹ce transformatê odwrotn¹.
    Funkcja gsl_fft_halfcomplex wydaje siê byæ tym czego szukam, jednak wyniki z niej wygl¹daj¹ ju¿ niepoprawnie.
*/

int signum(double Y)
{
    if (Y > 0.5)
    {
        return 1;
    }
    return -1;
}

double a_rand()
{
    double X = rand() / (RAND_MAX + 1.);
    double Y = rand() / (RAND_MAX + 1.);

    return 2. * signum(Y) * X;
}

void signal(const int n, gsl_vector* y, std::ofstream& file1)
{
    double omega = 4. * M_PI / n;
    for (int i = 0; i < n; i++)
    {
        gsl_vector_set(y, i, std::sin(omega * i) + std::sin(2 * omega * i) + std::sin(3 * omega * i) + a_rand());
        file1 << i << "\t" << std::sin(omega * i) + std::sin(2 * omega * i) + std::sin(3 * omega * i) << "\t" << gsl_vector_get(y, i) << std::endl;
    }
}

double max_in_y(const int n, gsl_vector* y)
{
    double max = gsl_vector_get(y, 0);
    for (int i = 1; i < n; i++)
    {
        if (gsl_vector_get(y, i) > max)
        {
            max = gsl_vector_get(y, i);
        }
    }
    return max;
}

int main()
{
    srand(time(NULL));

    std::ofstream file1("results1.txt");
    std::ofstream file2("results2.txt");
    std::ofstream file3("results3.txt");

    const int k = 10;
    const int n = std::pow(2, k);

    auto y = gsl_vector_calloc(n);

    signal(n, y, file1);

    gsl_fft_halfcomplex_wavetable* wavetable = gsl_fft_halfcomplex_wavetable_alloc(n);
    gsl_fft_real_workspace* workspace = gsl_fft_real_workspace_alloc(n);

    gsl_fft_halfcomplex_wavetable* wavetable2 = gsl_fft_halfcomplex_wavetable_alloc(n);
    gsl_fft_real_workspace* workspace2 = gsl_fft_real_workspace_alloc(n);

    //gsl_fft_real_transform(y->data, y->stride, n, wavetable, workspace);
    //gsl_fft_real_radix2_transform(y->data, y->stride, n);
    gsl_fft_halfcomplex_transform(y->data, y->stride, n, wavetable, workspace);

    for (int i = 0; i < n; i++)
    {
        file2 << gsl_vector_get(y, i) << "\n";
    }

    double max = max_in_y(n, y);

    for (int i = 0; i < n; i++)
    {
        if (std::fabs(gsl_vector_get(y, i)) < (0.25 * max))
        {
            gsl_vector_set(y, i, 0.);
        }
    }

    //gsl_fft_real_transform(y->data, y->stride, n, wavetable, workspace);
    gsl_fft_halfcomplex_inverse(y->data, y->stride, n, wavetable2, workspace2);

    for (int i = 0; i < n; i++)
    {
        gsl_vector_set(y, i, gsl_vector_get(y, i) * (2. / n));
    }

    for (int i = 0; i < n; i++)
    {
        file3 << gsl_vector_get(y, i) << "\n";
    }

    gsl_vector_free(y);
    gsl_fft_halfcomplex_wavetable_free(wavetable);
    gsl_fft_halfcomplex_wavetable_free(wavetable2);
    gsl_fft_real_workspace_free(workspace);
    gsl_fft_real_workspace_free(workspace2);

    file1.close();
    file2.close();
    file3.close();

    system(".\\chart_script.py");
    system(".\\chart_script2.py");
    system(".\\chart_script3.py");

    return 0;
}