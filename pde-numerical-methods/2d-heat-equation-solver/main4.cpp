#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>                                               //Для setw
#include "solve4.hpp"
#include <cmath>

#include <math.h>
#include <cmath>
using namespace std;



int main()
{   
    // int Nx=20,Ny=20,Nt=200;
    int Nx=10,Ny=10,Nt=100;
    double hx = 1/double(Nx-0.5), hy = 1/double(Ny-0.5), tau = 1/double(Nt);
    cout<<"Process start "<<endl<<endl;
    // double gamma = 0.01;
    double gamma = 1;
    double p=2;
    



    vector<double> time_layer(Nx*Ny);
    vector<double> f(Nx*Ny);
    vector<double> b(Nx*Ny);
    vector<double> cmn(Nx*Ny);
    vector<double> dmn(Nx*Ny);
    vector<double> prod(Nx*Ny);
    vector<double> y(Nx*Ny);



    for(int j=0;j<Ny;j++) for(int i=0;i<Nx;i++) time_layer[j*Nx+i] = u_0(hx/2 +i*hx,hy/2 +j*hy);
    
    fourier2d(Nx,Ny,time_layer,cmn);
    
    ofstream File("result.txt");
    File<<"Слой 0"<<endl;
    File<<"Численное решение"<<endl;
    for(int j = 0; j < Ny; j++) for(int i = 0; i < Nx; i++) File<<aprox2(Nx,Ny,hx/2 +i*hx, hy/2 +j*hy,cmn)<<" ";
    File<<endl;
    File<<"Точное решение"<<endl;
    for(int j = 0; j < Ny; j++) for(int i = 0; i < Nx; i++) File<<u_0(hx/2 +i*hx,hy/2 +j*hy)<<" ";
    File<<endl<<endl;


    for(int t=1;t<Nt;t++)
    {

        calculate_dmn(Nx,Ny,hx,hy,tau*t,f,dmn);
        // if(t==3)
        // {
        //     ofstream File("result.txt");
        //     for(int j = 0; j < Ny; j++) for(int i = 0; i < Nx; i++) File<<aprox2(Nx,Ny,hx/2 +i*hx, hy/2 +j*hy,dmn)<<" ";
        //     File<<endl;
        //     for(int j = 0; j < Ny; j++) for(int i = 0; i < Nx; i++) File<<fun(tau*t,hx/2 +i*hx,hy/2 +j*hy)<<" ";
        // }
        evolution(Nx,Ny,hx,hy,tau,dmn,cmn);
        for(int j = 0; j < Ny; j++)
        {
            for(int i = 0; i < Nx; i++) b[j*Ny+i] = time_layer[j*Ny+i]/tau + fun(t*tau, hx/2 +i*hx, hy/2 +j*hy);
            for(int i = 0; i < Nx; i++) time_layer[j*Ny+i] = aprox2(Nx,Ny,hx/2 +i*hx, hy/2 +j*hy,cmn);
        } 
        BSolver(Nx,Ny,Nt,hx,hy,tau,p,gamma,time_layer,b,cmn,dmn,prod,y);
        fourier2d(Nx,Ny,time_layer,cmn);
        File<<"Слой "<<t<<endl;
        File<<"Численное решение"<<endl;
        for(int j = 0; j < Ny; j++) for(int i = 0; i < Nx; i++) File<<aprox2(Nx,Ny,hx/2 +i*hx, hy/2 +j*hy,cmn)<<" ";
        File<<endl;
        File<<"Точное решение"<<endl;
        for(int j = 0; j < Ny; j++) for(int i = 0; i < Nx; i++) File<<u_ans(t*tau,hx/2 +i*hx,hy/2 +j*hy)<<" ";
        File<<endl<<endl;
        // break;
    }
    
    return 0;
    
}
