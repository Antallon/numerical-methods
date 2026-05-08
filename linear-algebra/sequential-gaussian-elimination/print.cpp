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

/*void printMatrix(double *matrix, int l, int n, int m) {
    std::cout << "tut" << std::endl;
    // Выводим не более m строк и столбцов матрицы
    for (int i = 0; i < std::min(l, m); i++) {
        std::cout << "tut" << std::endl;
        for (int j = 0; j < std::min(n, m); j++) {
            printf("%10.3e ", matrix[i*n + j]);
        }
        std::cout << std::endl;
    }
}*/


void printMatrix(double *matrix,int n, int m,  double *vector_b){
        int l;
        if (n <= 10)
                l = n;
        else
                l = 5;
        for (int i = 0; i < m; i++){
                for (int j = 0; j < l; j++){
                        if ((i*n + j) <= (n*m - 1))
                                printf("%10.3e ", matrix[i*n + j]);
                }
                printf("  |    %10.3e\n", vector_b[i]);
        }
        printf("\n");
}



double get_time()
{
	timeval tim;

	gettimeofday(&tim, 0);

	return tim.tv_sec * 100 + tim.tv_usec/10000;
}