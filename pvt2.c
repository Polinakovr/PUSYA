#define _POSIX_C_SOURCE 1
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>
#define M_PI 3.14159265358979323846
double getrandx(unsigned int *seed)
{
    double result;
    do
    {
        result = 0.0 +(double)rand_r(seed) / RAND_MAX;
    } while (result < 0 || result > 1);

    return result;
}
double getrandy(unsigned int *seed)
{
    double result;
    do
    {
        result = 2.0 + (double)rand_r(seed) / RAND_MAX * 3;
    } while (result < 2 || result > 5);
    return result;
}
double func(double x, double y)
{
    return (x / (pow(y, 2)));
}
int main(int argc, char **argv)
{
    const int n = 10000000;
    printf("Numerical integration by Monte Carlo method: n = %d\n", n);
    int in = 0;
    double s = 0;
    omp_set_num_threads(8);
#pragma omp parallel
    {
        double s_loc = 0;
        int in_loc = 0;
        unsigned int seed = 25234 * omp_get_thread_num() + omp_get_thread_num();
#pragma omp for nowait
        for (int i = 0; i < n; i++)
        {
            double x = getrandx(&seed); /* x in [0, pi] */
            double y = getrandy(&seed);        /* y in [0, sin(x)] */
            if (y <= 5)
            {
                in_loc++;
                s_loc += func(x, y);
            }
        }
#pragma omp atomic
        s += s_loc;
#pragma omp atomic
        in += in_loc;
    }
    double v = M_PI * in / n;
    double res = v * s / in;
    printf("Result: %.12f, n %d\n", res, n);
    return 0;
}