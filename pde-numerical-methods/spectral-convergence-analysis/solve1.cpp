#include "solve1.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <functional>
#define EPS 1e-16
#define eps2 1e-30
using namespace std;

double u(double x)
{
    return 3 * x*x*x*x - 3*x*x -6*x+3.4;
}





void fillf
( 
    const int N, 
    vector<double>& f
)
{
    
    double h = 1.0 / ( (double)(N) - 0.5 );
    double x_k = -h / 2.0;
    
    f[0] = u(x_k);
    for (int k = 1; k < N  ; k++)
    {
        x_k += h;
        f[k] = u(x_k);
    }
    f[N] = u(1.0);
    
}





long double compute_eigen_vector
(
    const int N, 
    const int k, 
    const int m 
)
{
    long double ev = cos(M_PI * m*(2.0*k - 1.0) / (2.0*N - 1.0));
    return ev;
}










long double compute_coeff_d
(
    const int N, 
    const int m, 
    const vector<double>& f
)
{
    long double h = 1.0 / ((double)N - 0.5);
    long double sum = 0.0;
    for (int k = 1; k < N; k++)
    {    
        sum +long double compute_eigen_value
(
    const int N, 
    const int m, 
    const double p
)
{
    long double l = 0.0;
    long double h = 1.0 / (double(N) - 0.5 );
    long double h_sq = h*h;
    l = p - 2.0 /h_sq * (cos(2.0*M_PI * m / (2.0*(double)(N) - 1.0)) - 1.0);
    return l;
}=  2*double(f[k]) * double(compute_eigen_vector(N, k, m)) * double(h);        
    }
    sum +=   2*double(f[N]) * double(compute_eigen_vector(N,N,m)) * double((h/2));
    // cout<<"lol = "<<double(f[0]) * double(compute_eigen_vector(N,0,m))*h/2<<endl;
    // cout<<"kek = "<<double(f[N]) * double(compute_eigen_vector(N,N,m))*h/2<<endl;
    // sum +=   2.0*double(f[0]) * double(compute_eigen_vector(N,0,m)) * double((h / 2.0));
    return sum;
}





void compute_solution_y
(
    const int N, 
    const double p,
    const vector<double>& f,
    vector<double>& y

)
{
    for(int k = 0; k < N + 1 ; k++)
    {
        y[k] = 0.0;
        for(int m = 1; m < N; m++)
        {
            y[k] +=  compute_coeff_d(N, m, f) / compute_eigen_value(N, m, p) * compute_eigen_vector(N, k, m) ;
        }
        y[k] += compute_coeff_d(N, N, f) / compute_eigen_value(N, N, p) * compute_eigen_vector(N, k, N) ;
        // y[k] += compute_coeff_d(N, 0, f) / compute_eigen_value(N, 0, p) * compute_eigen_vector(N, k, 0) ;


    }


}
















/**
 * @brief Print a portion of the matrix and a vector
 * 
 * This function prints the elements of a matrix and a vector up to a certain limit.
 * If the number of columns 'n' is less than or equal to 10, it prints all columns.
 * Otherwise, it prints the first 5 columns. Each row of the matrix is printed
 * alongside the corresponding element from vector_b.
 * 
 * @param matrix - The matrix to be printed.
 * @param n - The number of columns in the matrix.
 * @param m - The number of rows in the matrix.
 * @param vector_b - The vector to be printed alongside the matrix rows.
 */
void printMatrix(vector<double>& matrix,int n, int m,  vector<double>& vector_b){
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


/**
 * @brief Calculate the error norm between the product of matrix A and vector x and the vector b.
 * 
 * This function computes the error norm as the square root of the sum of squared differences 
 * between the elements of vector b and the product of matrix A and vector x. The elements 
 * are weighted by the grid spacing h.
 * 
 * @param A - The matrix with coefficients.
 * @param b - The vector on the right side of the system of equations.
 * @param x - The vector to be multiplied by matrix A.
 * @param N - The size of the matrix A and vector b.
 * @param prod - The resulting vector from multiplying matrix A by vector x.
 * @return The computed error norm as a double.
 */

double ErNorm
(
    const vector<double>& A, 
    const vector<double>& b,  
    const vector<double>& x, 
    int N, 
    vector<double>& prod
)
{
    double ans = 0.0;
    double h = 1.0 / ( double(N) - 0.5 );

    multiply(N, A, x, prod);
    vector<double> res(N-1);
    for(int i=0;i<N-1;i++)
    {
        res[i] = b[i+1];
    }
    for (int i = 0; i < N-1; i++)
    {
        // ans += (b[i] - prod[i]) * (b[i] - prod[i]) * h ;
        // cout<<res[i]<<" "<<prod[i]<<endl;
        ans += (res[i] - prod[i]) * (res[i] - prod[i]) * h ;

    }
    

    

    return sqrt(ans) ;
}












/**
 * @brief Multiply matrix A by vector b
 * 
 * @param[in] N - size of matrix A
 * @param[in] A - matrix A with coefficients for finite difference method
 * @param[in] b - vector b with the right side of the system of equations
 * @param[out] res - vector res with result of multiplication
 */
void multiply
(
    const int N,
    const vector<double>& A, 
    const vector<double>& x, 
    vector<double>& res
) 
{
    for(int i = 0; i < N ; i++)
    {
        res[i] = 0.0;
        for(int j = 0; j < N ; j++)
        {
            res[i] += A[i * (N) + j] * x[j+1];
        }
    } 
}





/**
 * @brief Fill matrix A with coefficients for finite difference method
 * 
 * @param[in] N - size of matrix A
 * @param[in] p - coefficient from equation
 * @param[out] A - matrix A with coefficients for finite difference method
 */
void fillmat
(
    const int N, 
    const double p, 
    vector<double>& A 
)
{
    double h = 1.0 / ( double(N) - 0.5 );
    double h_sq = h*h;
    // double rofl = (2 - p*p*h*h*h*h) / (2 - p*h*h);
    
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            // double p = 1.0 + (double)sin((double)M_PI*(j+1)*h)*(double)sin((double)M_PI*(j+1)*h);
            if     ( i == 0     && j == 0    ) A[i*N + j] = p +( 1.0 / h_sq);
            else if( i == 0     && j == 1    ) A[i*N + j] =    (-1.0 / h_sq);
            else if( i == 1     && j == 0    ) A[i*N + j] =    (-1.0 / h_sq);
            // else if( i == N - 1 && j == N - 1) A[i*N + j] = p -( 2.0 / h_sq);
            // else if( i == N - 1 && j == N - 2) A[i*N + j] =    ( 2.0 / h_sq);
            else if( i == N - 1 && j == N - 1) A[i*N + j] = p +( 2.0 / h_sq);   
            else if( i == N - 1 && j == N - 2) A[i*N + j] =    -( 2.0 / h_sq); //странное место
 
            else if( i == N - 2 && j == N - 1) A[i*N + j] =    (-1.0 / h_sq);
            else if(i == j && i > 0 && i < N - 1 && j > 0 && j < N - 1) A[i*N + j] = p + (2.0 / h_sq);
            else if((std::abs(i - j) == 1) && i > 0 && i < N - 1 && j > 0 && j < N - 1) A[i*N + j] = (-1.0 /h_sq);
            else A[i*N + j] = 0.0;
        }
    }
}
