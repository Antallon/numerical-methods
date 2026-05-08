#include <iostream>
#include <cmath>
#include <thread>

double vecnorm(double *vec, int n);
void mult(double *A, double *b, double *x, int n, double *res);
double discrepency(double *A, double *b, double *x, int n,double *res);
void margin_err(double *x, int n,double *res, double *acc);
double matnorm(double *matrix, int n);

