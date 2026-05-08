#include "bvec.h"



void bvec(double *A, double *vec, int n)
{   
    for (int i = 0; i < n; ++i) {
        vec[i] = 0.0;
        for (int j = 0; j < n; j += 2) {
            vec[i] += A[i * n + j];
        }
    }
}
