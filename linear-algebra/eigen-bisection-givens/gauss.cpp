#include "gauss.h"
#include "norm.h"
#include <iostream>
#include "print.h"
#include <cmath>
#include <vector>

#define EPS 1e-16
using namespace std;

double mach_()
{
    double epss = 1;
    while (1 + epss / 2.0 > 1)
    {
        epss = epss / 2.0;
    }
    return epss;
}

// Проверка матрицы на симметричность
int checking(const int n, const double *const A)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // if (fabs(A[i * n + j] - A[j * n + i]) > EPS)
            // {
            //     return -1;
            // }
            if (fabs(A[i * n + j] - A[j * n + i]) > EPS)
            {
                return -1;
            }
        }
    }
    return 0;
}




void third_diag(const int n, double *A)
{
    for (int row = 1; row < n - 1; row++)
    {
        double *rowPtr = A + row * n;
        for (int down_row = row + 1; down_row < n; down_row++)
        {
            double *row_rowm1Ptr = rowPtr + row - 1;
            double *downRowPtr = A + down_row * n;
            double *downRow_rowm1Ptr = downRowPtr + row -1;
            double *endPtr = downRowPtr + n;

            // double tmp1 = rowPtr[row - 1];
            // double tmp2 = downRowPtr[row - 1];
            double tmp1 = *row_rowm1Ptr;
            double tmp2 = *downRow_rowm1Ptr;
            if(tmp2<EPS)
            {
                continue;
            }
            double r = sqrt(tmp1 * tmp1 + tmp2 * tmp2);
            if (r < EPS)
            {
                continue;
            }

            double cos_phi = tmp1 / r;
            double sin_phi = -tmp2 / r;

            // Домножение на матрицу элементарного вращения слева
            for (;downRow_rowm1Ptr< endPtr;)
            {
                double a = *row_rowm1Ptr;
                double b = *downRow_rowm1Ptr;
                *row_rowm1Ptr = cos_phi * a - sin_phi * b;
                *downRow_rowm1Ptr = sin_phi * a + cos_phi * b;
                row_rowm1Ptr++;
                downRow_rowm1Ptr++;
            }

            // Домножение на транспонированную матрицу элементарного вращения справа
            for (int new_row = row - 1; new_row < n; new_row++)
            {
                double *newRowPtr = A + new_row * n;
                double a = newRowPtr[row];
                double b = newRowPtr[down_row];
                newRowPtr[row] = cos_phi * a - sin_phi * b;
                newRowPtr[down_row] = sin_phi * a + cos_phi * b;
            }
        }
    }
//    printMatrix(A,n,10);
}













double coeff(const int n, const double *const A, const double L)
{
    double maxEl = 0.0;
    double element;
    for (int i = 1; i < n; i++)
    {
        element = A[i * n + i - 1];
        if (fabs(element) > fabs(maxEl))
        {
            maxEl = fabs(element);
        }
    }

    for (int i = 0; i < n; i++)
    {
        element = A[i * n + i] - L;
        if (fabs(element) > fabs(maxEl))
        {
            maxEl = fabs(element);
        }
    }
    if (maxEl < EPS)
    {
        return 1.0;
    }
    return 0.25 / maxEl;
}

// Реккурентный метод
int n_(const int n, const double *const A, const double L)
{
    double x_;
    double y = 1.0;
    double u, v, ak, bk, g, temp;
    int m;
    const double mach = mach_();
    const double al = coeff(n, A, L);

    x_ = al * (A[0] - L);
    if (x_ < 0.0)
    {
        m = 1;
    }
    else
    {
        m = 0;
    }
    for (int i = 1; i < n; i++)
    {
        ak = al * (A[i * n + i] - L);
        bk = al * A[i * n + i - 1];
        // cout << "bk " << bk<< "y "<< y<<endl;
        //  if (bk < EPS || y < EPS)
        //  {
        //      temp = 0;
        //  }
        //  else
        //  {
        temp = fabs(bk * bk * y);
        // }
        if (fabs(x_) > temp)
        {
            temp = fabs(x_);
        }
        if (temp < mach)
        {
            temp = 1;
        }

        g = 1.0 / (mach * temp);
        u = g * (ak * x_ - bk * bk * y);
        // cout <<"u " << u<<endl;
        v = g * x_;
        //cout << "i=" << i << ", x_=" << x_ << ", y=" << y << ", ak=" << ak << ", bk=" << bk << ", u=" << u << ", v=" << v << ", temp=" << temp << ", m= " << m << endl;
        if (u * x_ <= 0.0)
        {
            m++;
        }
        x_ = u;
        y = v;
    }
    //cout << "-----------------------------" << endl;
    return m;
}

// Функция для нахождения k-го собственного значения методом бисекции
double findKthEigenvalue(const double *const A, const int n, int k, const double eps,const double norma)
{
    double norm = norma + eps;
    double a0 = -norm;
    double b0 = norm;

    double ai = a0;
    double bi = b0;
    double ci;
    int cou = 0;
    // double memor;
    // memor = 2*b0;
    // cout<<"lol"<<endl;
    while (bi - ai > eps)
    {
        cou++;
        ci = 0.5 * (ai + bi);
        // if(cou==stop)
        // {
        //     break;
        // }
        // cout << "ai "<<ai<<" bi "<<bi<< " ci "<<ci<<endl;
        if (n_(n, A, ci) < k + 1)
        {
            ai = ci;
        }

        else
        {
            bi = ci;
        }
        // memor = ci;
         if (cou == 100)
         {
            
             break;
         }
    }
    // cout << "//////////////////////////" << endl;
    return 0.5 * (ai + bi);
}

double solve(const int n, double *A, const double eps,int number)
{
    third_diag(n, A);
    const double norma = matnorm(A, n);
//    for (int k = 0; k < n; k++)
//    {
//        x[k] = findKthEigenvalue(A, n, k, eps,norma);
//        if(k<5)
//        {
//            cout<< x[k]<<endl;
//        }
//    }
    // cout<<"kek"<<endl;
    number -= 1;
    double lol = findKthEigenvalue(A,n,number,eps,norma);
    // cout<<lol<<endl;

//    cout<<number+1 <<" eigenvalue = "<< lol<<endl;
    return lol;
}
