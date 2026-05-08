#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>                                               //Для setw
#include "solve3.hpp"
#include <cmath>

#include <math.h>
#include <cmath>
using namespace std;



int main()
{   
    int N      = 200;
    int M      = 10;
    int steps = 6;
    ofstream File_exp("result_explicit.txt");
    ofstream File_imp("result_implicit.txt");

    cout<<"Process start "<<endl<<endl;
   
    for(int step=0;step<steps;step++)
    {
        double h   = 1.0/double(M - 0.5);
        double tau = 1.0/double(N);
        vector<double> u((N+1)*(M+1));
        Explicit_Scheme(N,M,h,tau,u);
        double error = ErNorm(N,M,h,u);
        cout<<"Ошибка в явной схеме для (N,M)=("<<N<<","<<M<<") равна "<<error<<endl;
        File_exp<<N<<" "<<M<<" "<<error<<endl;
        M*=2;
        N*=4;    
    }



    cout<<endl;
    N = 200;
    M = 10;
    for(int step=0;step<steps;step++)
    {

        double h   = 1.0/double(M - 0.5);
        double tau = 1.0/double(N);
        vector<double> u((N+1)*(M+1));
        vector<double> b(M+1);
        vector<double> a(M);
        vector<double> c(M);
        vector<double> d(M+1);
        vector<double> x(M+1);
        vector<double> alpha(M);
        vector<double> beta(M+1);
        Implicit_Scheme(N,M,h,tau,b,a,c,u,x,d,alpha,beta);

        double error = ErNorm(N,M,h,u);
        cout<<"Ошибка в неявной схеме для (N,M)=("<<N<<","<<M<<") равна "<<error<<endl;
        File_imp<<N<<" "<<M<<" "<<error<<endl;
        double ans_0 = 0.0;
        double ans_N = 0.0;
        double max_f = -1.0;
        for (int i=1;i<M;++i) ans_0+=(u[0*(M+1)+i]-u_ans(0.0,-h/2.0 + i*h))*h;
        ans_0+= (u[0*(M+1)+M]-u_ans(0.0,1.0))*h/2.0;
        ans_0 = sqrt(ans_0);

        for (int i=1;i<M;++i) ans_N+=(u[N*(M+1)+i]-u_ans(1.0,-h/2.0 + i*h))*h;
        // ans_N+= (u[N*(M+1)+M]-u_ans(1.0,1.0))*h/2.0;
        ans_N = sqrt(ans_N);
        for (int i=0;i<M+1;++i)
        {
            if(d[i]>max_f) max_f = d[i];
        }
        M*=2;
        N*=4;     
    }
    











    // for(int i=0;i<steps-1;i++)
    // {
    //     double h_0 = (M_arr[i] - 0.5);
    //     double h_1 = (M_arr[i+1] - 0.5);
    //     double tau_0 = N_arr[i];
    //     double tau_1 = N_arr[i+1];
    //     // cout<<"Порядок сходимости = "<<log(errors[i]/errors[i+1])/log(N_arr[i]/N_arr[i+1])<<endl;
    //     // cout<<"Порядок сходимости для (M1,M2)=("<<M_arr[i]<<" "<<M_arr[i+1]<<") есть "<<log(errors[i+1]/errors[i])/log(M_arr[i]/M_arr[i+1])<<endl;
    //     // cout<<"Порядок сходимости для (M1,M2)=("<<M_arr[i]<<" "<<M_arr[i+1]<<") есть "<<log(errors[i+1]/errors[i])/log((tau_0+h_0*h_0)/(tau_1+h_1*h_1))<<endl;
    //     cout<<"Порядок сходимости для (M1,M2)=("<<M_arr[i]<<" "<<M_arr[i+1]<<") есть "<<log(errors[i+1]/errors[i])/log((h_0)/(h_1))<<endl;
    //     // cout<<"Порядок сходимости для (M1,M2)=("<<M_arr[i]<<" "<<M_arr[i+1]<<") есть "<<log(errors[i+1]/errors[i])/log((M_arr[i+1])/(M_arr[i]))<<endl;



    //     // File<<"Порядок сходимости для (M1,M2)=("<<M_arr[i]<<" "<<M_arr[i+1]<<") есть "<<log(errors[i+1]/errors[i])/log(h_1/h_0)<<endl;
    // }
   
           // if(step == steps-1)
        // {
        //     for (int i = 0; i < N+1; ++i) 
        //     {
        //         for (int j = 0; j < M+1; ++j)
        //         {
        //             File_u<<u[(M+1)*i+j]<<" ";
        //         }
        //         File_u<<endl;  
        //     }
        // }

    
    
    return 0;
    
}
