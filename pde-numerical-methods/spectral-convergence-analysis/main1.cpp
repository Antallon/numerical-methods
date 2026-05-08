#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>                                               //Для setw
#include "solve1.hpp"
#include <cmath>

#include <math.h>
#include <cmath>
using namespace std;



int main()
{   
    double p    = 0.;
    double mult = 1.0;
    int N       = 4;
    int N_step  = 10;
    int N_num   = 6;
    ofstream File("result.txt");
    ofstream Fil("re.txt");
    cout<<"Process start "<<endl<<endl;
    vector<double> errors(N_num);
    vector<double> N_arr(N_num);
   
    if (!File)
    {
        cerr << "Error: Unable to open file" << endl;
        return -1;
    }
    
    for(int i=0;i<N_num;i++)
    {
        cout<<i<<" "<<N<<endl;
        vector<double> A((N)*(N));
        vector<double> y(N+1);
        vector<double> f(N+1);
        vector<double> prod(N);
        vector<double> res(N+1);
        // fillmat(N, p, A);
        fillf(N, f);
        compute_solution_y(N, p, f, y);
        for(int k = 0; k < N+1 ; k++)
        {
            res[k] = 0.0;
            for(int j = 1; j < N ; j++)
            {
                res[k] += compute_coeff_d(N, j, f)*compute_eigen_vector(N,k,j);
            }
            res[k] += compute_coeff_d(N, N, f)*compute_eigen_vector(N,k,N);
        }
        for(int i = 0; i < N+1 ; i++) File<< res[i]<<" ";
        File<<endl;
        for(int i = 0; i < N+1 ; i++) File<< f[i]<<" ";
        File<<endl<<endl<<endl;
        double ans=0.0;
        double h = 1.0 / ( double(N) - 0.5 );
        for (int i = 1; i < N; i++)
        {
            // ans += (res[i] - f[i]) * (res[i] - f[i]) * h ;
            if( abs(res[i] - f[i]) > ans ) ans = abs(res[i] - f[i]) ;
        }
        // ans += (res[N] - f[N]) * (res[N] - f[N]) * h/2 ;
        // ans = sqrt(ans);
        errors[i] = ans;
        N_arr[i] = N;
        N*=3;
        // N+=30;
        Fil<<N<<" "<<ans<<endl;
    }
    for(int i=0;i<N_num;i++) cout<<setprecision(10)<<N_arr[i]<<" "<<errors[i]<<endl;


    cout<<endl;
    N=10;

    vector<double> A((N)*(N));
    vector<double> y(N+1);
    vector<double> f(N+1);
    vector<double> prod(N);
    vector<double> res(N+1);
    // fillmat(N, p, A);
    fillf(N, f);
    compute_solution_y(N, p, f, y);
    // multiply(N, A, y, prod);
    // ErNorm(A,f,y,N,prod);

    for(int i = 0; i < N ; i++)
    {
        res[i] = 0.0;
        for(int j = 1; j < N ; j++)
        {
            res[i] += compute_coeff_d(N, j, f)*compute_eigen_vector(N,i,j);
        }
        // res[i] += compute_coeff_d(N, N, f)*compute_eigen_vector(N,i,N);
    }
   
    // cout<<"The result for method Fourier is: "<<endl;
    // cout<<"|||||||  ";
   
    for(int i = 0; i < N ; i++)
    {
        cout<< res[i]<<" ";
    }
    cout<<endl<<endl;
    File<<endl<<endl;

    cout<<"The real answer for method Fourier is: "<<endl;
    // for(int i = 0; i < N+1 ; i++)
    for(int i = 0; i < N ; i++)

    {
        cout<< f[i]<<" ";
    }
    cout<<endl<<endl;
    File<<endl<<endl;
    // for(int i = 0; i < N ; i++) kek2(A, N, p, i);
    
    return 0;
    
}
