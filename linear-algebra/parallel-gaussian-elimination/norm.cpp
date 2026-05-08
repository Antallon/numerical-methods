#include "norm.h"
#include "Matfill.h"

double vecnorm(double *vec, int n)
{
    double norm = 0.0;
    for (int i = 0; i < n; i++)
    {
        norm += (vec[i]* vec[i]);
    }
    norm = sqrt(norm);
    return norm;
}

double matnorm(double *matrix, int n)
{
    double mem = 0.0;
    double sum;
    for (int i = 0; i < n; i++)
    {   
        sum = 0.0;
        for (int j = 0; j < n; j++)
        {
            sum+= std::fabs(matrix[i * n + j]);
        }
        if(sum>mem){
            mem = sum;
        }
    }
    return mem;
}

void mult(double *A, double *b, double *x, int n, double *res)
{
    for (int i = 0; i < n; i++)
    {   
        res[i]=0.0;
        for (int j = 0; j < n; j++)
        {
            res[i] += A[i * n + j] * x[j];
        }
        res[i] -= b[i];
    }
}

double discrepency(double *A_copy, double *b_copy, double *x, int n, double *res)
{
    
    double kek = 0.0;
    
    mult(A_copy, b_copy, x, n, res);
    kek = vecnorm(res, n) / vecnorm(b_copy, n);
    // std::cout << "Норма Невязки: " << std::scientific << vecnorm(res, n) / vecnorm(b, n) << std::endl;
    std::cout << "norma nevyazki: ";
    printf("%.10e\n", kek);
    return kek;
}

void margin_err(double *x, int n, double *res, double *acc)
{
    for (int i = 0; i < n; i++)
    {
        res[i] = std::fabs(x[i] - acc[i]);
    }
    // std::cout << "Норма погрешности: " << std::scientific << vecnorm(res, n) << std::endl;
    std::cout << "norma pogreshnosti: ";
    printf("%.10e\n", vecnorm(res, n));
}