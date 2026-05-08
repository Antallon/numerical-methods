#include <iostream>
#include <chrono>
#include "Matfill.h"
#include "Matin.h"
#include "gauss.h"
#include "norm.h"
#include "print.h"
#include <math.h>
using namespace std;

int main(int argc, char **argv)
{

    int n, m, k, number;
    double eps;
    // int na;
    // printf("Process start \n");

    try
    {
        n = std::stoi(argv[1]); // string to int
        m = std::stoi(argv[2]);
        eps = std::stod(argv[3]);
        number = std::stoi(argv[4]);
        k = std::stoi(argv[5]);
        // cout << n << endl;
        // cout << m << endl;
        // cout << eps << endl;
        // cout << k << endl;
        if (k == 0 && argc < 7)
        {
            cerr << "Error: The command line parameters must be at least 6" << endl;
            return -1;
        }

        if (k != 0 && argc < 6)
        {
            cerr << "Error: The command line parameters must be at least 5" << endl;
            return -1;
        }
    }

    catch (const std::invalid_argument &e)
    {
        cerr << "Error: Invalid argument. Need enter integers for n, m and k" << endl;

        return -1;
    }

    catch (const std::out_of_range &e)
    {
        cerr << "Error: meaning out of int range" << endl;
        return -1;
    }
    catch(const std::exception&e){
        cout<<"Error inputXXXXXXXXX"<<e.what()<<endl;
        return -1;
    }
    if(number>n)
    {
        cout<<"Error: number of eigenvalue must be <= n "<<endl;
        return -1;
    }



    if (n < 2 || m <= 0 || k < 0 || eps <= 0||k>4 || number<=0)
    {
        cerr << "Error: parametres must be positive" << endl;
        return -1;
    }

    if (n < m)
    {
        cerr << "Error: n must be >= m" << endl;
        return -1;
    }

    try
    {
        double *A = new double[n * n];
        double *A_copy = new double[n * n];
//        double *x = new double[n];

        cout << "lets go" << endl;

        if (k == 0)
        {
            string filename = argv[6];
            const int err = fromfile(A, n, filename);
            if (err == -1)
            {
                delete[] A;
//                delete[] x;
                delete[] A_copy;
                return -1;
            }
            const int err2 = checking(n, A);
            if (err2 == -1)
            {
                cerr << "Error: Matrix must be symmetric" << endl;
                delete[] A;
//                delete[] x;
                delete[] A_copy;
                return -1;
            }

            for (int i = 0; i < n; i++)
            {
                int i_n = i*n;
                for (int j = 0; j < n; j++)
                {
                    A_copy[i_n + j] = A[i_n + j];
                }
            }

            printMatrix(A, n, m);
            clock_t start_time = clock();
            double eigen = solve(n, A, eps,number);
            print_eigen(eigen);
            clock_t end_time = clock();
            const double sec = (double)(end_time - start_time) / CLOCKS_PER_SEC;
            printf("Time: %f\n", sec);
//            norma1(A_copy, x, n);
//            norma2(A_copy, x, n);
        }

        else if (k == 1 || k == 2 || k == 3 || k == 4)
        {

            for (int i = 0; i < n; i++)
            {
                int i_n = i*n;
                for (int j = 0; j < n; j++)
                {
                    A[i_n + j] = fMat(n, k, i, j);
                }
            }

            for (int i = 0; i < n; i++)
            {
                int i_n = i*n;
                for (int j = 0; j < n; j++)
                {
                    A_copy[i_n + j] = A[i_n + j];
                }
            }

            printMatrix(A, n, m);
            clock_t start_time = clock();
            double eigen = solve(n, A,eps,number);
            print_eigen(eigen);
            clock_t end_time = clock();
            double sec = (double)(end_time - start_time) / CLOCKS_PER_SEC;
            printf("Time: %f\n", sec);
//            norma1(A_copy, x, n);
//            norma2(A_copy, x, n);
        }

        else
        {
            cerr << "Error: k has wrong value" << endl;
        }

        // printMatrix(A, n, m);
        // cout << " Eigenvalues: " << endl;
        // for (int i = 0; i < n; i++)
        // {
        //     cout << x[i]<< "  ";
        // }

        delete[] A;
//        delete[] x;
        delete[] A_copy;
        return 0;
    }

    catch (std::bad_alloc &)
    {
        std::cerr << "memory error" << endl;
    }

}
