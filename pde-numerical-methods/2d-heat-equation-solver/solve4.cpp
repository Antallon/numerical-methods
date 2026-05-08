#include "solve4.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <functional>
#define EPS 1e-16
#define eps2 1e-30
using namespace std;
 
double fun(double t, double x,double y)
{
    return exp(-t)*cos(M_PI*x)*cos(M_PI*y)*(-1+2*M_PI*M_PI+p(x,y));
    // return exp(-t)*cos(M_PI*x)*cos(M_PI*y)*(-1+2*M_PI*M_PI+p(x,y))+(1-x)*(1-x)*(1-y)*(1-y)*x*x*y*y*(1+exp(-t))-4*exp(-t)*(y*(1-y)*(1-y)+x*(1-x)*(1-x));
}
double u_0(double x,double y)
{

    return cos(M_PI*x)*cos(M_PI*y);
    // return cos(M_PI*x)*cos(M_PI*y)+(1-x)*(1-x)*(1-y)*(1-y)*x*x*y*y;
}

double u_ans(double t,double x,double y)
{

    return exp(-t)*cos(M_PI*x)*cos(M_PI*y);
    // return exp(-t)*(M_PI*x)*cos(M_PI*y)+(1-x)*(1-x)*(1-y)*(1-y)*x*x*y*y;

}

double p
(
    double x,
    double y
)
{
    return 2;
}



void fourier2d
(
    const int Nx,
    const int Ny,
    vector<double>& U,
    vector<double>& coeff_mn
)
{
    vector<double> x(Nx);
    vector<double> y(Ny);
    vector<double> C(Ny*Nx);
    computePoints(Nx, x);
    computePoints(Ny, y);
    Cfull(Nx,Ny, x, C, U);
    Dfull(Nx,Ny, y, C, coeff_mn);
}



/**
 * @brief Compute grid points and points for numerical integration
 * @param[in] N Number of points
 * @param[out] vec Vector of grid points
 * @param[out] p Vector of points for numerical integration
 */
void computePoints(int N, vector<double>& vec)
{
    double h = 1.0 / ( N - 0.5 );
    double x_k = h / 2;
    vec[0] = x_k;
    for(int i=1; i < N; i++)
    {
        x_k += h;
        vec[i] = x_k;
    }

}



/**
 * @brief Compute trigonometric functions for given x and N
 * @param[in] N Number of trigonometric functions
 * @param[in] x Value for which to compute trigonometric functions
 * @param[out] cx Vector of computed trigonometric functions
 */
void computeTrig(int N, double x, vector<double>& cx)
{
    for(int m=0; m < N; m++) cx[m] = cos(M_PI * (m+1) * x);
}





/**
 * @brief Compute coefficients for a given function using trigonometric basis functions.
 * 
 * @param[in] N Number of points for computation.
 * @param[in] x Vector of grid points.
 * @param[out] coef Iterator to the beginning of the output coefficients.
 * @param[in] u Iterator to the input function values.
 * 
 * This function calculates the coefficients of a given function
 * represented by its values at specified grid points using a trigonometric
 * basis. The coefficients are computed by integrating the product of the
 * function values and the cosine of the basis functions over the grid points.
 */
void coeff(int N , vector<double>& x, vector<double>::iterator coef, vector<double>::iterator u)
{
    double h = 1.0 / ( N - 0.5 );
    for(int i=0; i < N; i++)
    {
        *(coef + i) = 0.0;
        for(int j=0; j < N-1; j++) *(coef + i) += *(u+j) * h * cos(M_PI * (i+1) * x[j])*2;
        *(coef + i) += *(u+N-1) * h/2 * cos(M_PI * (i+1)* x[N-1])*2;
        // if(i!=0) *(coef + i) *= 2;
    }
}



/**
 * @brief Compute coefficients for a given 2D array using trigonometric basis functions.
 * 
 * This function calculates the coefficients of a given 2D array represented by
 * its values at specified grid points using a trigonometric basis. The coefficients
 * are computed by integrating the product of the function values and the cosine of
 * the basis functions over the grid points.
 * 
 * @param[in] N Number of points in the array
 * @param[in] x Vector of grid points
 * @param[out] C 2D array to store the computed coefficients
 * @param[in] U 2D array of values to compute coefficients for
 */
void Cfull
(
    int Nx,int Ny,
    vector<double>& x,  
    vector<double>& C, 
    vector<double>& U
)
{
    for(int i = 0; i < Ny; i++) coeff(Nx,x,C.begin()+i*Nx, U.begin()+i*Nx);
}



/**
 * @brief Compute coefficients for a given 2D array transposed using trigonometric basis functions.
 * 
 * This function calculates the coefficients of a given 2D array represented by
 * its values at specified grid points using a trigonometric basis. The coefficients
 * are computed by integrating the product of the function values and the cosine of
 * the basis functions over the grid points. The input array is transposed, so that
 * instead of computing the coefficients for each row, the function computes the
 * coefficients for each column of the input array.
 * 
 * @param[in] N Number of points in the array
 * @param[in] x Vector of grid points
 * @param[in] C 2D array of values to compute coefficients for
 * @param[out] D 2D array to store the computed coefficients
 */
void Dfull
(
    int Nx, int Ny,
    vector<double>& x,
    vector<double>& C, 
    vector<double>& D
)
{
    for(int i = 0; i < Nx; i++)
    {
        vector <double> col(Ny);
        for(int h = 0; h < Ny; h++) col[h] = C[h * Nx + i];
        coeff(Ny, x, D.begin() + i * Nx, col.begin());
    }
}




/**
 * @brief Computes an approximation of a 2D function at a given point (x, y) using Fourier coefficients.
 * 
 * This function calculates an approximation of a 2D function's value at a specified 
 * point (x, y) using precomputed Fourier coefficients stored in the vector `D`. It 
 * utilizes trigonometric basis functions computed by the `computeTrig` function for 
 * both x and y coordinates. The approximation is obtained by summing the product of 
 * the coefficients and the trigonometric values.
 * 
 * @param[in] N Number of terms in the Fourier series.
 * @param[in] x The x-coordinate of the point at which to compute the approximation.
 * @param[in] y The y-coordinate of the point at which to compute the approximation.
 * @param[in] points Vector containing the grid points.
 * @param[in] U Vector containing values used for computing the approximation (not used in this function).
 * @param[in] D Vector containing the precomputed Fourier coefficients.
 * 
 * @return The computed approximation of the 2D function at the point (x, y).
 */
double aprox2 (int Nx,int Ny,double x, double y,vector<double>& coeff_mn)
{
    vector <double> cx(Nx);
    vector <double> cy(Ny);
    // vector <double> x(Nx);
    // vector <double> y(Ny);
    computeTrig(Nx, x, cx);
    computeTrig(Ny, y, cy);
    double z = 0.0;
    for(int j=0;j<Ny;j++) for(int i=0;i<Nx;i++) z += coeff_mn[j*Nx+i]*cx[i]*cy[j];
    return z;
}

double compute_eigen_value(const int N,const double h,const int m)
{
    return 4/(h*h) * sin(M_PI * m / (2.0*(double)(N) - 1.0))*sin(M_PI * m / (2.0*(double)(N) - 1.0));
    // return 4/(h*h) * sin((M_PI/2) * (2*m-1) / (2.0*(double)(N) - 1.0))*sin((M_PI/2) * (2*m-1) / (2.0*(double)(N) - 1.0));

}

void calculate_dmn
(
    const int Nx,const int Ny,const double hx,const double hy,double time,
    vector<double>& f,
    vector<double>& dmn
)
{
    for(int j = 0; j < Ny; j++) for(int i = 0; i < Nx; i++) f[j*Nx+i] = fun(time, hx/2 +i*hx, hy/2 +j*hy);
    fourier2d(Nx,Ny,f,dmn);
}


void evolution
(
    const int Nx,
    const int Ny,
    const double hx,
    const double hy,
    const double tau,
    const vector<double>& dmn,
    vector<double>& cmn
)
{
    double p=2;
    for(int j = 0; j < Ny; j++) for(int i = 0; i < Nx; i++) cmn[j*Nx+i] = (cmn[j*Nx+i]/tau + dmn[j*Nx+i]) / (compute_eigen_value(Nx,hx,i+1) + compute_eigen_value(Ny,hy,j+1) + p + 1.0/tau);
}



void compute_prod
(
    const int Nx,
    const int Ny,
    const double hx,
    const double hy,
    const double tau,
    const vector<double>& u,
    vector<double>& prod
)
{
    for(int j=0;j<Ny;j++)
    {
        for(int i=0; i<Nx;i++)
        {
            if((j==0)&&(i==0))              prod[j*Nx+i] = -((u[j*Nx+(i+1)] - 2*u[j*Nx+i] + u[j*Nx+i])/(hx*hx))-((u[(j+1)*Nx+i]      - 2*u[j*Nx+i]    + u[j*Nx+i])/(hy*hy))         + u[j*Nx+i]/tau + p(hx/2 +i*hx, hy/2 +j*hy)*u[j*Nx+i];
            else if((j==Ny-1)&&(i==Nx-1))   prod[j*Nx+i] = u[j*Nx+i]*(2/(hx*hx) + 2/(hy*hy) + 1/tau + p(hx/2 +i*hx, hy/2 +j*hy))   - u[j*Nx+i-1]*2/(hx*hx)       - u[(j-1)*Nx+i]*2/(hy*hy);
            else if((j==Ny-1)&&(i==0))      prod[j*Nx+i] = u[j*Nx+i]*(2/(hx*hx)+1/(tau) + 2/(hy*hy)+p(hx/2 +i*hx, hy/2 +j*hy)) - u[(j-1)*Nx+i]*2/(hy*hy)     - (u[j*Nx+i+1]   + u[j*Nx+i])*1/(hx*hx);
            else if((j==0)&&(i==Nx-1))      prod[j*Nx+i] = u[j*Nx+i]*(2/(hx*hx)+1/(tau) + 2/(hy*hy)+p(hx/2 +i*hx, hy/2 +j*hy)) - u[j*Nx+i-1]*2/(hx*hx)       - (u[(j+1)*Nx+i] + u[(j)*Nx+i])*1/(hy*hy);
            else if((j==0))                 prod[j*Nx+i] = -((u[j*Nx+(i+1)] - 2*u[j*Nx+i] + u[j*Nx+(i-1)])/(hx*hx))-((u[(j+1)*Nx+i]  - 2*u[j*Nx+i]    + u[j*Nx+i])    /(hy*hy)) + u[j*Nx+i]/tau + p(hx/2 +i*hx, hy/2 +j*hy)*u[j*Nx+i];
            else if((i==0))                 prod[j*Nx+i] = -((u[j*Nx+(i+1)] - 2*u[j*Nx+i] + u[j*Nx+i])    /(hx*hx))-((u[(j+1)*Nx+i]  - 2*u[j*Nx+i]    + u[(j-1)*Nx+i])/(hy*hy)) + u[j*Nx+i]/tau + p(hx/2 +i*hx, hy/2 +j*hy)*u[j*Nx+i];
            else if(i==Nx-1)                prod[j*Nx+i] = u[j*Nx+i]*(2/(hx*hx)+1/(tau) + 2/(hy*hy)+p(hx/2 +i*hx, hy/2 +j*hy)) - u[j*Nx+i-1]*2/(hx*hx)       - (u[(j+1)*Nx+i] + u[(j-1)*Nx+i])*1/(hy*hy);
            else if(j==Ny-1)                prod[j*Nx+i] = u[j*Nx+i]*(2/(hx*hx)+1/(tau) + 2/(hy*hy)+p(hx/2 +i*hx, hy/2 +j*hy)) - u[(j-1)*Nx+i]*2/(hy*hy)     - (u[j*Nx+i+1]   + u[j*Nx+i-1])*1/(hx*hx);
            else                            prod[j*Nx+i] = -((u[j*Nx+(i+1)] - 2*u[j*Nx+i] + u[j*Nx+(i-1)])/(hx*hx))-((u[(j+1)*Nx+i]  - 2*u[j*Nx+i]    + u[(j-1)*Nx+i])/(hy*hy)) + u[j*Nx+i]/tau + p(hx/2 +i*hx, hy/2 +j*hy)*u[j*Nx+i];
        }
    }
    // for(int j=0;j<Ny;j++) for(int i=0;i<Nx;i++) cout<<prod[j*Nx+i]<<" ";
}

double calculate_norm            
(
    const int Nx,
    const int Ny,
    const double hx,    
    const double hy,
    const double tau,
    const vector<double>& u,
    const vector<double>& b,
    vector<double>& prod
)
{
    double error=0;
    compute_prod(Nx,Ny,hx,hy,tau,u,prod);
        for (int j = 0; j < Ny; j++)
        {
            for (int i = 0; i < Nx; i++)
            {
                double temp_error = 0.;
                temp_error = fabs(prod[j*Nx+i] - b[j*Nx+i]);
                if(temp_error > error) error = temp_error;
            }
        }
    return error;
}

void BSolver
(
    const int Nx,
    const int Ny,
    const int Nt,
    const double hx,
    const double hy,
    const double tau,
    const double p,
    const double gamma,
    vector<double>& u,
    const vector<double>& b,
    vector<double>& cmn,
    vector<double>& dmn,
    vector<double>& prod,
    vector<double>& y
)
{
    double err = 100.;
    int iterations = 1;


    while(iterations < 50 && err > 1e-9)
    {
        compute_prod(Nx,Ny,hx,hy,tau,u,prod);
        for(int j = 0; j < Ny; j++) for(int i = 0; i < Nx; i++) prod[j*Nx+i]   = b[j*Nx+i] - prod[j*Nx+i];
        // calculate_dmn(Nx,Ny,Nt,hx,hy,tau,prod,dmn);
        fourier2d(Nx,Ny,prod,dmn);
        for(int j = 0; j < Ny; j++) for(int i = 0; i < Nx; i++) cmn[j*Nx+i] = (dmn[j*Nx+i]) / (compute_eigen_value(Nx,hx,i+1) + compute_eigen_value(Ny,hy,j+1) + p + 1.0/tau);
        for(int j = 0; j < Ny; j++) for(int i = 0; i < Nx; i++) y[j*Nx+i]   = aprox2(Nx,Ny,hx/2 +i*hx, hy/2 +j*hy,cmn);
        for(int j = 0; j < Ny; j++) for(int i = 0; i < Nx; i++) u[j*Nx+i]   = u[j*Nx+i] + gamma * y[j*Nx+i];

        double err = calculate_norm(Nx,Ny,hx,hy,tau,u,b,prod);
        
        cout<<"iteration =  "<<iterations<<", error = "<<err<<endl;
        iterations++;
        if(err < 1e-9) break;
        
        
    }
}