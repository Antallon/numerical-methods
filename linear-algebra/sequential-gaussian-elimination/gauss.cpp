#include "gauss.h"
#include "norm.h"
#include <iostream>
#include <math.h>
#include "print.h"
#define EPS 1e-16

void swapCol(int n, double *A, int col1, int col2,double *A_copy, double*acc)
{
    for (int i = 0; i < n; i++)
    {   
        int i_n = i * n;
        std::swap(A[i_n + col1], A[i_n + col2]);
        std::swap(A_copy[i_n + col1], A_copy[i_n + col2]);
    }
    std::swap(acc[col1],acc[col2]);
}

int findMax(int n, double *A, int row)
{
    int maxCol = row;
    for (int i = row + 1; i < n; i++)
    { // идем вправо по колонкам и ищем максимальный элемент в строке
        int row_n = row * n;
        if (fabs(A[row_n + i]) > fabs(A[row_n + maxCol]))
        {
            maxCol = i;
        }
    }
    return maxCol;
}

// int triangle(int n, double *A, double *b,double *A_copy, double *acc)
// {
//     double norma = matnorm(A, n);

//     for (int row = 0; row < n - 1; row++)
//     {
//         int nrow= row*n;
//         int maxCol = findMax(n, A, row);
//         if (maxCol != row)
//         {
//             swapCol(n, A, maxCol, row,A_copy,acc);
//         }
//         for (int down_row = row + 1; down_row < n; down_row++)
//         {
//             int ndown_row =down_row * n;
//             if (std::fabs(A[nrow + row]) <= norma * EPS)
//             {
//                 return -1;
//             }                                                        // идем по строкам,ниже текущей
//             double ratio = -A[ndown_row + row] / A[nrow + row]; // Находим коэфф
//             for (int i = row; i < n; i++)
//             {
//                 A[ndown_row + i] += ratio * A[nrow + i]; // Вычитаем из нижних строк текущую
//             }
//             b[down_row] += ratio * b[row];
//         }


//     }
//     return 1;
// }

// int triangle(int n, double *A, double *b, double *A_copy, double *acc,double norma)
// {
//    norma = matnorm(A, n);

//     for (int row = 0; row < n - 1; row++)
//     {
//         double *rowPtr = A + row * n;
//         int maxCol = findMax(n, A, row);
//         if (maxCol != row)
//         {
//             swapCol(n, A, maxCol, row, A_copy, acc);
//         }

//         for (int down_row = row + 1; down_row < n; down_row++)
//         {
//             double *downRowPtr = A + down_row * n;
//             if (std::fabs(rowPtr[row]) <= norma * EPS)
//             {
//                 return -1;
//             }

//             double ratio = -downRowPtr[row] / rowPtr[row];
//             for (int i = row; i < n; i++)
//             {
//                 downRowPtr[i] += ratio * rowPtr[i];
//             }
//             b[down_row] += ratio * b[row];
//         }
//     }
//     return 1;
// }


int triangle(int n, double *A, double *b, double *A_copy, double *acc, double norma)
{

    for (int row = 0; row < n - 1; ++row)
    {
        
        double *b_row = b + row;
        
        double *row_rowPtr = A + row * n + row;

        int maxCol = findMax(n, A, row);
        if (maxCol != row)
        {
            swapCol(n, A, maxCol, row, A_copy, acc);
//            printMatrix(A,n,3,b);
        }
//        cout<<"norma"<<norma<<endl;
//        cout<<"row_rowPtr"<<*row_rowPtr<<endl;
        if (fabs(*row_rowPtr) <= norma * EPS)
        {
            return -1;
        }

        for (int down_row = row + 1; down_row < n; ++down_row)
        {
            double *rowPtr = row_rowPtr;
            double *downRowPtr = A + down_row * n;
            double *downRow_rowPtr = downRowPtr + row;
            double *end_drPtr = downRowPtr+n;
            
            // double ratio = -downRowPtr[row] / *row_rowPtr;
            if (fabs(*row_rowPtr) <= norma * EPS)
            {
                return -1;
            }
//            cout<< " *downRow_rowPtr "<<*downRow_rowPtr<<endl;
            double ratio = -(*downRow_rowPtr) / (*row_rowPtr);
//            cout<<"lol"<<endl;
            for (;downRow_rowPtr< end_drPtr;)
            {
//                cout<<"lol2"<<endl;
//                cout<<"*downRow_rowPtr "<< *downRow_rowPtr<<"ratio "<< ratio
//                 cout<< " *downRow_rowPtr " << *downRow_rowPtr << " rowPtr "<< *rowPtr << " ratio " << ratio<<endl;
                *downRow_rowPtr += ratio * (*rowPtr);
                // cout<< " *downRow_rowPtr " << *downRow_rowPtr << " rowPtr "<< *rowPtr << " ratio " << ratio<<endl;
//                printMatrix(A,n,3,b);
                downRow_rowPtr++;
                rowPtr++;
                // cout<<"////////////"<<endl;
            }
            // cout<<"######################"<<endl;
            // b[down_row] += ratio * b[row];
            b[down_row] += ratio * (*b_row);
            
        }
//         cout<<"$$$$$$$$$$$$$$$$$$$$"<<endl;
    }
    return 1;
}



int reverse(int n, double *A, double *b, double *x,double norma)
{ // Обратный ход
    
    for (int i = n - 1; i >= 0; i--)
    {
        int i_n = i * n;
        double *rowPtr = A + i_n;
        double *row_rowPtr = A + i_n + i;
        // double *row_row_divPtr = &(1.0/(*row_rowPtr));
        if (fabs(*row_rowPtr) <= norma * EPS)
        {
            return -1;
        }
        double row_row_div = 1.0/(*row_rowPtr);
        double *xiPtr = x + i;
        // int i_n = i*n;
        // x[i] = b[i];
        *xiPtr = b[i];
        double *row_jPtr = rowPtr + i + 1;
//        double *endPtr = rowPtr + n;
        double * x_j = x + i + 1;
        double *endPtr = x + n;
//        for (int j = i + 1; j < n; j++)
//        {
//            double Aijminus = -(rowPtr[j]);
//            // x[i] -= A[i_n + j] * x[j]; // из b_i вычитаем те что нашли и делим на элемент
//            // xiPtr -= A[i_n + j] * x[j];
//            *xiPtr += Aijminus * x[j];

//        }
        for (; x_j< endPtr;)
        {
            double Aijminus = -(*row_jPtr);
            // x[i] -= A[i_n + j] * x[j]; // из b_i вычитаем те что нашли и делим на элемент
            // xiPtr -= A[i_n + j] * x[j];
            *xiPtr += Aijminus * (*x_j);
            x_j++;
            row_jPtr++;


        }
        // if (fabs(A[i_n + i]) <= norma * EPS)
        // {
        //     return -1;
        // }
//        if (fabs(*row_rowPtr) <= norma * EPS)
//        {
//            return -1;
//        }
        // x[i] /= A[i_n + i];
        *xiPtr*=row_row_div;
        
    }
    
    return 1;
}




int solve(int n, double *A, double *b, double *x,double *A_copy, double * acc)
{
    int a, c;
    double norma = matnorm(A, n);
    a = triangle(n, A, b, A_copy, acc,norma);
    c = reverse(n, A, b, x,norma);
   
    if (a == -1 || c == -1)
    {
        return -1;
    }
    return 0;
}
