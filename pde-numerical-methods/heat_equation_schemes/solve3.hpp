#pragma once
#include <cmath>
#include <vector>
#include <functional>

using namespace std;
double f(double t, double x);
double u_0(double x);
double u_ans(double t,double x);
void fill_mat(const int N,const int M,const double h,const double tau,vector<double>& b,vector<double>& a,vector<double>& c);
void fill_d(const int N,const int M,const double h, const double tau,int i_0,const vector<double>& u,vector<double>& d);
void TDMA(const int N,const int M,const double h,const double tau,const vector<double>& b,const vector<double>& a,const vector<double>& c,const vector<double>& d,vector<double>& x,vector<double>& alpha,vector<double>& beta);
void Implicit_Scheme(const int N,const int M,const double h,const double tau,vector<double>& b,vector<double>& a,vector<double>& c,vector<double>& u,vector<double>& x,vector<double>& d,vector<double>& alpha,vector<double>& beta);
void Explicit_Scheme(const int N,const int M,const double h,const double tau,vector<double>& u); 
double ErNorm(const int N,const int M,const double h,const vector<double>& u);

