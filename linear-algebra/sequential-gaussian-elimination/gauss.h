#pragma once
#include <chrono>
void swapCol(int n, double *A, int col1, int col2,double *A_copy, double *acc);
int findMax(int n, double *A, int row);
int triangle(int n, double *A, double *b,double *A_copy, double *acc, double norma);
int reverse(int n, double *A, double *b, double *x, double norma);
int solve(int n, double *A, double *b, double *x,double *A_copy, double *acc);