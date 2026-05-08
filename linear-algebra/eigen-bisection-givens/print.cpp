#include "print.h"
double min(int a, int b)
{
    if (a > b)
    {
        return b;
    }
    else
    {
        return a;
    }
}



void printMatrix(const double *const matrix, const int n, const int m)
{
    int l;
    if (n <= 10)
    {
        l = n;
    }

    else
    {
        l = 5;
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < l; j++)
        {
            if ((i * n + j) <= (n * m - 1))
            {
                printf("%10.3e ", matrix[i * n + j]);
            }
        }
        std::cout << std::endl;
        // printf("  |    %10.3e\n", vector_b[i]);
    }

    printf("\n");
}

void print_eigen(double eigen){
    std::cout<< "EigenValue: "<<eigen<<std::endl;
}
