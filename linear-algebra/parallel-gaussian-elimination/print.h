#pragma once
#include <iostream>
#include <iomanip>
#include <sys/time.h>
// #include <sys/resource.h>

double min(int a, int b);
//void printMatrix(double *matrix, int l, int n, int m);
void printMatrix(double *matrix,int n, int m,  double *vector_b);
// long int get_time(void)
// {
// 	struct rusage buf;

// 	getrusage(RUSAGE_SELF, &buf);

// 	return buf.ru_utime.tv_sec * 100 + buf.ru_utime.tv_usec/10000;
// };

double get_time(void);