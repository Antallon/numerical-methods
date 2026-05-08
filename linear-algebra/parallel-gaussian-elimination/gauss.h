#pragma once
#include <iostream>



void swapCol(int n, double *A, int col1, int col2, double *A_copy, double *acc);
int findMax(int n, double *A, int row);
int triangle(int n, double *A, double *b, double *A_copy, double *acc);
int reverse(int n, double *A, double *b, double *x,double norma);
int solve(int n, double *A, double *b, double *x, double *A_copy, double *acc,int num_thread, int p,double norma);
void gaussianElimination(int n,double *A,double *b,int row,int start_row,int end_row);
void synchronize(int total_threads);
