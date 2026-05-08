#include "solve2.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <functional>
#define EPS 1e-16
#define eps2 1e-30
using namespace std;

/**
 * @brief Compute the approximate solution of the Cauchy problem
 * 
 * @param[in] N - number of steps
 * @param[in] A - coefficient of the equation
 * @param[in] y0 - initial value of y
 * @param[in] aprox_tip - type of approximation: 1 - Euler, 2 - implicit Euler, 3 - trapezoidal, 4 - Adams
 * @param[in] len - length of the interval
 * 
 * @return the root mean square error of the approximate solution
 */
double aprox
(
    const int N,
    const int A, 
    const int y0,
    const int aprox_tip,
    const double len
) 
{
    double y      = y0;
    double h      = len / double(N);
    double y_0    = y0;  
    double y_1    = y0*(1.0 - A*h);
    double y_real = 0.0;
    double ans    = 0.0;


    for(int i=1;i<N;i++)
    {
        if(aprox_tip==1)
        {
            y = y*(1.0 - A*h);
        }

        if(aprox_tip==2)
        {
            y = y/(1.0 + A*h);
        }

        if(aprox_tip==3)
        {
            y = (2.0 - A*h)/(2.0 + A*h)*y;
        }

        if(aprox_tip==4)
        {
            if(i==1) continue;   
            y  = y_0 - 2.0*A*h*y_1;
            y_0 = y_1;
            y_1 = y;
        }
        y_real = y0*exp(-A*y0*i*h);
        ans +=(y_real-y)*(y_real-y)*h;
    }

    return sqrt(ans);
}