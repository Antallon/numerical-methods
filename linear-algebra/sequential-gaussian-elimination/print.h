#pragma once
#include <iostream>
#include <iomanip>
#include <sys/time.h>

double min(int a, int b);
//void printMatrix(double *matrix, int l, int n, int m);
void printMatrix(double *matrix,int n, int m,  double *vector_b);


double get_time();