#include <iostream>
#include <chrono>
#include "Matfill.h"
#include "Matin.h"
#include "bvec.h"
#include "gauss.h"
#include "norm.h"
#include "print.h"
#include <math.h>
#include <sys/time.h>
using namespace std;


int main(int argc, char **argv)
{   
    
    int n, m, k;
    int na;
    printf("Process start \n");




    try
    {
        n = std::stoi(argv[1]); // string to int
        m = std::stoi(argv[2]);
        k = std::stoi(argv[3]);
        cout << n << endl;
        cout << m << endl;
        cout << k << endl;
        if(k==0 && argc<5){
            cerr << "Error: The command line parameters must be at least 4" << endl;
            return -1;
        }

        if(k!=0 && argc<4){
            cerr << "Error: The command line parameters must be at least 4" << endl;
            return -1;
        }

    }

    catch (const std::invalid_argument &e)
    {
        cerr << "Error: Invalid argument. Need enter integers for n, m and k" << endl;

        return -1;
    }
    catch(const std::out_of_range&e){
        cerr <<"Error: meaning out of int range"<< endl;
        return -1;
    }
    catch(const std::exception&e){
        cout<<"Error inputXXXXXXXXX"<<e.what()<<endl;
        return -1;
    }

//    if(argc<4){
//        cerr<<"Error: count of param must be>=4"<<endl;
//        return -1;
//    }

    if (n <2  || m < 0 || k<0||k>4)
    {
        cerr << "Error: parametres must be positive" << endl;
        return -1;
    }


    if (n < m)
    {
        cerr << "Error: n must be >= m" << endl;
        return -1;
    }



    try{
        double *A = new double[n * n];
        double *A_copy = new double[n * n];
        double *b = new double[n];
        double *x = new double[n];
        double *res = new double[n];
        double *acc = new double[n];
        double *b_copy = new double[n];

        cout << "lets go" << endl;
        for (int u = 0; u < n; ++u)
        {
            acc[u] = (u+1) % 2;
        }

        








        if (k == 0)
        {
            string filename = argv[4];
            int err = fromfile(A,n,filename);
            if (err == -1)
            {
                delete[] A;
                delete[] b;
                delete[] x;
                delete[] res;
                delete[] acc;
                delete[] A_copy;
                delete[] b_copy;
                return -1;
            }
            
            bvec(A, b, n);
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    A_copy[i*n + j] = A[i*n+j];
                }
                b_copy[i] = b[i];
            }
            printMatrix(A, n, m, b);
            // timeval tv1;
            // gettimeofday(&tv1, 0);
            double time = get_time();
            na = solve(n, A, b, x,A_copy,acc);
            // timeval tv2;
            // gettimeofday(&tv2, 0);
            // double Time = (double(tv2.tv_sec) * 1000000.0 + double(tv2.tv_usec) -
            // double(tv1.tv_sec) * 1000000.0 + double(tv1.tv_usec)) /1000000.0;
            time = get_time() - time;
            time /=100;
            cout<<"Time: "<<time<<"seconds"<<endl;

            // printf("Time: %f\n", Time);
            if (na == -1)
            {
                cerr << "Determinate of matrix is zero" << endl;
                delete[] A;
                delete[] b;
                delete[] x;
                delete[] res;
                delete[] acc;
                delete[] A_copy;
                delete[] b_copy;
                return -1;
            }
            discrepency(A_copy, b_copy, x, n, res);
            margin_err(x, n, res, acc);
        }








        else if (k == 1 || k == 2 || k == 3 || k == 4)
        {
            
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    A[i * n + j] = fMat(n, k, i, j);
                }
            }
            bvec(A, b, n);
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    A_copy[i*n + j] = A[i*n+j];
                }
                b_copy[i] = b[i];
            }

            printMatrix(A, n, m, b);
            // timeval tv1;
            // gettimeofday(&tv1, 0);
            double time = get_time();
            na = solve(n, A, b, x,A_copy,acc);
            time = get_time() - time;
            time /=100;
            cout<<"Time: "<<time<<"seconds"<<endl;
            // timeval tv2;
            // gettimeofday(&tv2, 0);
            // double Time = (double(tv2.tv_sec) * 1000000.0 + double(tv2.tv_usec) -
            // double(tv1.tv_sec) * 1000000.0 + double(tv1.tv_usec)) /1000000.0;
            // printf("Time: %f\n", Time);
            if (na == -1)
            {
                cerr << "Determinate of matrix is zero" << endl;
                delete[] A;
                delete[] b;
                delete[] x;
                delete[] res;
                delete[] acc;
                delete[] A_copy;
                delete[] b_copy;
                return -1;
            }
            
            discrepency(A_copy, b_copy, x, n, res);
            
            margin_err(x, n, res, acc);
        
            
        }

        else
        {
            cerr << "Error: k has wrong value" << endl;
        }
        
        printMatrix(A, n, m, x);

        delete[] A;
        delete[] b;
        delete[] x;
        delete[] res;
        delete[] acc;
        delete[] A_copy;
        delete[] b_copy;
        return 0;
    }
    catch(std::bad_alloc&){
        std::cerr<<"memory error" <<endl;
    }
}
