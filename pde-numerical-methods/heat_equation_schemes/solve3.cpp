#include "solve3.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <functional>
#define EPS 1e-16
#define eps2 1e-30
using namespace std;
 



double f(double t, double x)
{
    // return exp(-t)*cos(M_PI*x)*(M_PI*M_PI - 1);
    return exp(-t)*(cos(M_PI*x)*(M_PI*M_PI-1) - (x*x*x*x-2*x*x*x+13*x*x-12*x+2));
}
double u_0(double x)
{

    // return cos(M_PI*x);
    return x*x-2*x*x*x+x*x*x*x + cos(M_PI*x);
}

double u_ans(double t,double x)
{

    // return exp(-t)*cos(M_PI*x);
    return exp(-t)*(x*x-2*x*x*x+x*x*x*x + cos(M_PI*x));

}


/**
 * @brief Fills the three vectors b, a, c with the coefficients of the
 *        tridiagonal matrix
 * 
 * @param[in] N   - number of time steps
 * @param[in] M   - number of space steps
 * @param[in] h   - space step
 * @param[in] tau - time step
 * @param[out] b  - 1D vector, diagonal elements of the matrix
 * @param[out] a  - 1D vector, subdiagonal elements of the matrix
 * @param[out] c  - 1D vector, superdiagonal elements of the matrix
 * 
 * The function fills the three vectors b, a, c with the coefficients of the
 * tridiagonal matrix. The diagonal elements go in the vector b, the subdiagonal
 * elements go in the vector a, and the superdiagonal elements go in the vector
 * c. The function is used in the implicit finite difference method to solve the
 * heat equation.
 */
void fill_mat
(
    const int N,
    const int M,
    const double h,
    const double tau,
    vector<double>& b,
    vector<double>& a,
    vector<double>& c
)
{
    for(int i=0;i<M;i++)
    {
        if(i==0)
        {
            b[i] = -1.0;
            a[i] = -1.0/(h*h);
            c[i] =  1.0;
        }
        else if(i==M-1)
        {
            b[i] = (2.0/(h*h)) + (1.0/tau);
            a[i] = -1.0;
            c[i] = -1.0/(h*h);
        }
        else
        {
            b[i] = (2.0/(h*h)) + (1.0/tau);
            a[i] = -1.0/(h*h);
            c[i] = -1.0/(h*h);
        }
    }
    b[M]=1.0 + (h*h/(2.0*tau));

}

/**
 * @brief Fills the vector d with the right-hand side of the system of linear
 *        equations
 * 
 * @param[in] N   - number of time steps
 * @param[in] M   - number of space steps
 * @param[in] h   - space step
 * @param[in] tau - time step
 * @param[in] i_0 - current time step
 * @param[in] u   - 2D vector, solution at the previous time step
 * @param[out] d  - 1D vector, right-hand side of the system of linear equations
 * 
 * The function fills the vector d with the right-hand side of the system of linear
 * equations. The right-hand side is constructed from the previous time step's solution
 * and the source term f(t,x).
 */
void fill_d
(
    const int N,
    const int M,
    const double h, 
    const double tau,
    int i_0,
    const vector<double>& u,
    vector<double>& d
)
{
    for(int i=0;i<M+1;i++)
    {
        if(i==0)      d[i] = 0.0;
        else if(i==M) d[i] = (h*h/2.0)*f(i_0*tau, 1.0) + (h*h/(2.0*tau)) * u[(i_0 - 1)*(M+1)+(i)];
        else          d[i] = f(i_0*tau, -h/2.0+i*h) + u[(i_0 - 1)*(M+1)+(i)]    /tau;
    }
}

/**
 * @brief Solve a tridiagonal matrix system using the Thomas algorithm (TDMA)
 * 
 * @param[in]  N    - number of time steps
 * @param[in]  M    - number of space steps
 * @param[in]  h    - space step
 * @param[in]  tau  - time step
 * @param[in]  b    - main diagonal of the tridiagonal matrix
 * @param[in]  a    - subdiagonal of the tridiagonal matrix
 * @param[in]  c    - superdiagonal of the tridiagonal matrix
 * @param[out] x    - solution vector for the current time step
 * @param[in]  d    - right-hand side vector
 * @param[in] alpha - auxiliary vector for the Thomas algorithm
 * @param[in] beta  - auxiliary vector for the Thomas algorithm
 * 
 * The function solves the tridiagonal matrix system associated with the implicit
 * finite difference method for solving the heat equation. It uses the Thomas
 * algorithm to efficiently compute the solution vector `x` for the current time step.
 */

void TDMA
(
    const int N,
    const int M,
    const double h,
    const double tau,
    const vector<double>& b,
    const vector<double>& a,
    const vector<double>& c,
    const vector<double>& d,
    vector<double>& x,
    vector<double>& alpha,
    vector<double>& beta
    
)
{
    alpha[0] = -c[0] / b[0];
    beta[0]  =  d[0] / b[0];
    for(int i=1; i<M;i++) 
    {
        alpha[i] = -c[i] / (a[i-1]*alpha[i-1] + b[i]);
        beta[i]  = (d[i] - a[i-1]*beta[i-1]) / (a[i-1]*alpha[i-1] + b[i]);
    }
    beta[M] = (d[M] - a[M-1]*beta[M-1]) / (a[M-1]*alpha[M-1] + b[M]);
    x[M]    = beta[M];
    for (int i=M-1;i>=0;i--) x[i] = alpha[i]*x[i+1] + beta[i];
}

/**
 * @brief Solves the heat equation using the implicit finite difference method
 * 
 * This function takes in the necessary parameters and uses the implicit finite
 * difference method to solve the heat equation. It uses the Thomas algorithm to
 * solve the tridiagonal matrix system associated with the implicit finite
 * difference method. The function fills the u vector with the solution at each
 * time step.
 * 
 * @param[in]     N     - number of time steps
 * @param[in]     M     - number of space steps
 * @param[in]     h     - space step
 * @param[in]     tau   - time step
 * @param[in]     b     - main diagonal of the tridiagonal matrix
 * @param[in]     a     - subdiagonal of the tridiagonal matrix
 * @param[in]     c     - superdiagonal of the tridiagonal matrix
 * @param[in,out] u     - 2D vector, solution at each time step
 * @param[out]    x     - solution vector for the current time step
 * @param[in]     d     - right-hand side vector
 * @param[in]     alpha - auxiliary vector for the Thomas algorithm
 * @param[in]     beta  - auxiliary vector for the Thomas algorithm
 */
void Implicit_Scheme
(
    const int N,
    const int M,
    const double h,
    const double tau,
    vector<double>& b,
    vector<double>& a,
    vector<double>& c,
    vector<double>& u,
    vector<double>& x,
    vector<double>& d,
    vector<double>& alpha,
    vector<double>& beta
)
{
    for (int i=0;i<M+1;i++) u[0*(M+1)+i] = u_0(-h/2.0 + i*h);
    fill_mat(N,M,h,tau,b,a,c);
    for (int i=1;i<N+1; i++)
    {
        fill_d(N,M,h,tau,i,u,d); 
        TDMA(N,M,h,tau,b,a,c,d,x,alpha,beta);
        for (int j=0;j<M+1;++j) u[i*(M+1)+j] = x[j];
    }
}

/**
 * @brief Solve the heat equation using the explicit finite difference method
 * 
 * @param[in] N        - number of time steps
 * @param[in] M        - number of space steps
 * @param[in] h        - space step
 * @param[in] tau      - time step
 * @param[in,out] u    - 2D vector, where u[i][j] is the solution at time step i and space step j
 * 
 * The function solves the heat equation using the explicit finite difference method.
 * The boundary conditions are of the first kind.
 */
void Explicit_Scheme
(
    const int N,
    const int M,
    const double h,
    const double tau,
    vector<double>& u
) 
    {
        
        for (int i=0;i<M+1;i++) u[0*(M+1)+i] = u_0(-h/2.0 + i*h);
        if (N < 2.*(M-0.5)*(M-0.5)) std::cerr << "(tau / (h * h) = " << tau/(h*h) << " >= 0.5)\n";
        for (int i=0;i<N;i++) 
        {
            for (int j=1;j<M;j++) u[(i+1)*(M+1)+j]=(tau/(h*h))*u[i*(M+1)+(j+1)] - u[i*(M+1)+(j)]*(2.0*tau/(h*h)-1)+u[i*(M+1)+(j-1)]*tau/(h*h)+tau*f(i*tau,-h/2.0 + j*h);

            u[(i+1)*(M+1)+0] = u[(i+1)*(M+1)+1];
            u[(i+1)*(M+1)+M] = (u[(i+1)*(M+1)+(M-1)]+(h*h/(2*tau))*u[(i)*(M+1)+M]+(h*h/2)*f((i+1)*tau,1))/(1+(h*h)/(2*tau));

            // if(i<=200)
            // {
            //     for (int j=0;j<M+1;j++) cout<<u[(i+1)*(M+1)+j]<<" ";
            //     cout<<endl;
            //     for (int j=0;j<M+1;j++) cout<<u_ans((i+1)*tau,-h/2.0+j*h)<<" ";
            //     cout<<endl<<endl;
            // }
        }
    }

double ErNorm
(
    const int N,
    const int M,
    const double h,
    const vector<double>& u
)
{

    double ans = 0.0;
    double tau = 1.0/double(N);
    // for (int i=0;i<M+1;++i) ans+=(u[N*(M+1)+i]-u_ans(1.0,-h/2.0 + i*h))*(u[N*(M+1)+i]-u_ans(1.0,-h/2.0 + i*h))*h;
    for (int i=1;i<M;++i) ans+=(u[N*(M+1)+i]-u_ans(1.0,-h/2.0 + i*h))*(u[N*(M+1)+i]-u_ans(1.0,-h/2.0 + i*h))*h;
    ans+= (u[N*(M+1)+M]-u_ans(1.0,1.0))*(u[N*(M+1)+M]-u_ans(1.0,1.0))*h/2.0;
    return sqrt(ans);
    // for (int i=0;i<N+1;++i)
    // {
    //     for (int j=0;i<M+1;++i)
    //     {
    //         double temp = abs(u[i*(M+1)+j]-u_ans(i*tau,-h/2.0 + j*h));
    //         if(temp>ans) ans = temp;
    //     }
    // }
    // return ans;
}



