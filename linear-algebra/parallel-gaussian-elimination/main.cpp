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
#include <pthread.h>
using namespace std;

struct ThreadData
{
    // std::thread id;
    int n;
    double *A;
    double *b;
    double *x;
    double *copy;
    double *acc;
    double norma;
    int thread_num;
    int p;
    int lol;
    double time;
} ;

void *gaussElim(void *data)
{
	ThreadData *threaddata = static_cast<ThreadData*>(data);
        synchronize(threddata->p);
        double timee = get_time();
//        co/*ut<<"kek"<<endl;
//        cout<<threaddata->norma<<endl;*/
	int lol = solve(threaddata->n, threaddata->A, threaddata->b, threaddata->x, threaddata->copy, threaddata->acc, threaddata->thread_num, threaddata->p, threaddata->norma);
//        synchronize(threddata->p);
        synchronize(threddata->p);
        timee = get_time() - timee;

        timee /=100;
//        cout<<"Time: "<<timee<<"seconds"<<endl;
        threaddata->time = timee;
        threaddata->lol = lol;
        return NULL;
}


int main(int argc, char **argv)
{
    
    int n, p, r, s;

    printf("Process start \n");

    try
    {
        n = std::stoi(argv[1]);
        p = std::stoi(argv[2]);
        r = std::stoi(argv[3]);
        s = std::stoi(argv[4]);
        cout << n << endl; // Размерность
        cout << p << endl; // Количество потоков
        cout << r << endl; // То что раньше m
        cout << s << endl; // Формула
        if (s == 0 && argc < 6)
        {
            cerr << "Error: The command line parameters must be at least 4" << endl;
            return -1;
        }

        if (s != 0 && argc < 5)
        {
            cerr << "Error: The command line parameters must be at least 4" << endl;
            return -1;
        }
        if (p > 4 || p>n-1)
        {
            // cerr << "Error: Our EVM has only 4 kernels :(" << endl;
            cerr<<"Error: too much threads"<< endl;
            return -1;
        }
    }
    catch (const std::invalid_argument &e)
    {
        cerr << "Error: Invalid argument. Need enter integers for n,p, r, and s" << endl;
        return -1;
    }
    catch (const std::out_of_range &e)
    {
        cerr << "Error: Value out of int range" << endl;
        return -1;
    }
    catch(const std::exception&e){
        cout<<"Error inputXXXXXXXXX"<<e.what()<<endl;
        return -1;
    }

    if (n < 2 || r < 0 || s < 0 || p < 1|| s>4)
    {
        cerr << "Error: Parameters must be positive" << endl;
        return -1;
    }

    if (n < r)
    {
        cerr << "Error: n must be >= r" << endl;
        return -1;
    }

    try
    {
        double *A = new double[n * n];
        double *A_copy = new double[n * n];
        double *b = new double[n];
        double *x = new double[n];
        double *res = new double[n];
        double *acc = new double[n];
        double *b_copy = new double[n];
        ThreadData *threadData = new ThreadData[p];
        pthread_t* threads = new pthread_t[p];
        double residual;
        double timee = -1;

        

    

        for (int u = 0; u < n; ++u)
        {
            acc[u] = (u + 1) % 2;
        }

        if (s == 0)
        {
            string filename = argv[5];
            int err = fromfile(A, n, filename);
            if (err == -1)
            {
                delete[] A;
                delete[] b;
                delete[] x;
                delete[] res;
                delete[] acc;
                delete[] A_copy;
                delete[] b_copy;
                delete[] threadData;
                delete[] threads;
                return -1;
            }

            bvec(A, b, n);

            for (int i = 0; i < n; i++)
            {

                for (int j = 0; j < n; j++)
                {
                    A_copy[i * n + j] = A[i * n + j];
                }
                b_copy[i] = b[i];
            }
//            for(int i = 0;i<n;i++){
//                x[i] = 0;
//            }
            double norm = matnorm(A, n);
            for (int i = 0; i < p; i++)
            {
                threadData[i].n = n;
                threadData[i].A = A;
                threadData[i].b = b;
                threadData[i].x = x;
                threadData[i].copy = A_copy;
                threadData[i].acc = acc;
                threadData[i].norma = norm;
                threadData[i].thread_num = i;
                threadData[i].p = p;
            }

            printMatrix(A, n, r, b);
//            timee = get_time();
            // na = solve(n, A, b, x, A_copy, acc, p,threadData);



            for (int i = 0; i < p; i++)
            {
                pthread_create(&threads[i], 0, gaussElim, &threadData[i]);
            }
            for (int i = 0; i < p; i++)
            {
                pthread_join(threads[i], 0);
            }
            for (int i = 0; i < p; i++)
            {
                if(threadData[i].time>timee)
                {
                    timee = threadData[i].time;
                }
            }



//            timee = get_time() - timee;
//            timee /=100;
//            cout<<"Time: "<<timee<<"seconds"<<endl;

            if (threadData[0].lol == -1)
            {
                cerr << "Determinate of matrix is zero" << endl;
                delete[] A;
                delete[] b;
                delete[] x;
                delete[] res;
                delete[] acc;
                delete[] A_copy;
                delete[] b_copy;
                delete[] threadData;
                delete[] threads;
                return -1;
            }
            double timee2 = get_time();
            residual = discrepency(A_copy, b_copy, x, n, res);
            timee2 = get_time() - timee2;
            timee2 /=100;
            cout<<"Time discrepancy: "<<timee2<<"seconds"<<endl;
            margin_err(x, n, res, acc);
        }
        else if (s == 1 || s == 2 || s == 3 || s == 4)
        {

            for (int i = 0; i < n; i++)
            {

                for (int j = 0; j < n; j++)
                {
                    A[i * n + j] = fMat(n, s, i, j);
                }
            }
            bvec(A, b, n);

            for (int i = 0; i < n; i++)
            {

                for (int j = 0; j < n; j++)
                {
                    A_copy[i * n + j] = A[i * n + j];
                }
                b_copy[i] = b[i];
            }
            double norm = matnorm(A, n);
            for (int i = 0; i < p; i++)
            {
                threadData[i].n = n;
                threadData[i].A = A;
                threadData[i].b = b;
                threadData[i].x = x;
                threadData[i].copy = A_copy;
                threadData[i].acc = acc;
                threadData[i].norma = norm;
                threadData[i].thread_num = i;
                threadData[i].p = p;
            }

            printMatrix(A, n, r, b);
//            timee = get_time();
//            cout<<"time1 "<<timee/100<<endl;
            // na = solve(n, A, b, x, A_copy, acc, p,threadData);



            for (int i = 0; i < p; i++)
            {
                pthread_create(&threads[i], 0, gaussElim, &threadData[i]);
            }
            for (int i = 0; i < p; i++)
            {
                pthread_join(threads[i], 0);
            }

            for (int i = 0; i < p; i++)
            {
                if(threadData[i].time>timee)
                {
                    timee = threadData[i].time;
                }
            }



//            timee = get_time() - timee;
//            timee /=100;
//            cout<<"Time: "<<timee<<"seconds"<<endl;
           

            if (threadData[0].lol == -1)
            {
                cerr << "Determinate of matrix is zero" << endl;
                delete[] A;
                delete[] b;
                delete[] x;
                delete[] res;
                delete[] acc;
                delete[] A_copy;
                delete[] b_copy;
                delete[] threadData;
                delete[] threads;
                return -1;
            }
            double timee2 = get_time();
            residual = discrepency(A_copy, b_copy, x, n, res);
            timee2 = get_time() - timee2;
            timee2 /=100;
            cout<<"Time discrepancy: "<<timee2<<"seconds"<<endl;
            margin_err(x, n, res, acc);
        }
        else
        {
            cerr << "Error: s has wrong value" << endl;
        }
        cout<<endl;
        printMatrix(A, n, r, x);
        printf("%s : residual = %e time = %.2f n = %d p = %d r = %d s = %d\n", argv[0],residual,timee,n,p,r,s);
//        printf("%s : residual = %e n = %d p = %d r = %d s = %d\n", argv[0],residual,n,p,r,s);



        delete[] A;
        delete[] b;
        delete[] x;
        delete[] res;
        delete[] acc;
        delete[] A_copy;
        delete[] b_copy;
        delete[] threadData;
        delete[] threads;
        return 0;
    }
    catch (std::bad_alloc &)
    {
        std::cerr << "Memory error" << endl;
    }
}
