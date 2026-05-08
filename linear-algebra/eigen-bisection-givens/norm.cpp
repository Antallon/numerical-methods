#include "norm.h"
#include "Matfill.h"

double vecnorm(const double *const vec, const int n)
{
    double norm = 0.0;
    for (int i = 0; i < n; i++)
    {
        norm += (vec[i] * vec[i]);
    }
    norm = sqrt(norm);
    return norm;
}

double matnorm(const double *const matrix, const int n)
{
    double mem = 0.0;
    double sum;
    int i_n;
    for (int i = 0; i < n; i++)
    {
        sum = 0.0;
        i_n = i*n;
        for (int j = 0; j < n; j++)
        {
            sum += std::fabs(matrix[i_n + j]);
        }
        if (sum > mem)
        {
            mem = sum;
        }
    }
    return mem;
}

//double trace(const double *const A, const int n)
//{
//    double tr = 0.0;
    
//    for (int i = 0; i < n; i++)
//    {
//        tr += A[i * n + i];
//    }
//    return tr;
//}

//double eigensum(const double *const x, const int n, const int deg)
//{
//    double sum = 0.0;

//    if (deg == 1)
//    {
//        for (int i = 0; i < n; i++)
//        {
//            sum += x[i];
//        }
//    }
//    if (deg == 2)
//    {
//        for (int i = 0; i < n; i++)
//        {
//            sum += (x[i] * x[i]);
//        }
//    }
//    return sum;
//}

//void norma1(const double *const A, const double *const x, const int n)
//{
//    cout << "norma 1: ";
//    printf("%.10e\n", fabs(trace(A, n) - eigensum(x, n, 1)));
//}

//void norma2(const double *const A, const double *const x, const int n)
//{
//    cout << "norma 2: ";
//    printf("%.10e\n", fabs(vecnorm(A, n * n) - sqrt(eigensum(x, n, 2))));
//}
