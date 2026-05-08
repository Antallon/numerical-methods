#pragma once
#include <cmath>
#include <vector>
#include <functional>

using namespace std;
double fun(double t, double x,double y);
double u_0(double x,double y);
double u_ans(double t,double x,double y);
double p(double x,double y);
void fourier2d(const int Nx,const int Ny, vector<double>& U,vector<double>& coeff_mn);
void computePoints(int N, vector<double>& vec);
void computeTrig(int N, double x, vector<double>& cx);
void coeff(int N , vector<double>& x, vector<double>::iterator coef, vector<double>::iterator u);
void Cfull(int Nx,int Ny, vector<double>& x,  vector<double>& C, vector<double>& U);
void Dfull(int Nx,int Ny, vector<double>& x,  vector<double>& C, vector<double>& D);
double aprox2 (int Nx,int Ny,double x, double y,vector<double>& coeff_mn);
double compute_eigen_value(const int N,const double h, const int m);
void calculate_dmn(const int Nx,const int Ny,const double hx,const double hy,double time,vector<double>& f,vector<double>& dmn);
void evolution(const int Nx,const int Ny,const double hx,const double hy,const double tau,const vector<double>& dmn,vector<double>& cmn);
void compute_prod(const int Nx,const int Ny,const double hx,const double hy,const double tau,const vector<double>& u,vector<double>& prod);
double calculate_norm(const int Nx,const int Ny,const double hx,const double hy,const double tau,const vector<double>& u,const vector<double>& b,vector<double>& prod);
void BSolver(const int Nx,const int Ny,const int Nt,const double hx,const double hy,const double tau,const double p,const double gamma,vector<double>& u,const vector<double>& b,vector<double>& cmn,vector<double>& dmn,vector<double>& prod,vector<double>& y);



