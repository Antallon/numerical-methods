#pragma once
#include <chrono>
#include <math.h>
void third_diag(const int n, double *A);
double findKthEigenvalue(const double *const A, const int n, int k, const double eps,const double norma);
double solve(const int n, double *A, const double eps,int number);
double mach_();
// void G_create(int n, double *G, int k, int l, double cos_phi, double sin_phi);
// void G_T(double *G, int n, int k, int l);
// void mult(int n, double *mat1, double *mat2, int flag);
int checking(const int n, const double *const A);
double coeff(const int n, const double *const A, const double L);
int n_(const int n, const double *const A, const double L);
