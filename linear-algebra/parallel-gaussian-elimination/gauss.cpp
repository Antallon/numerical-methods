#include <iostream>
#include <cmath>
#include "gauss.h"
#include "norm.h"
#include "print.h"

#define EPS 1e-16
using namespace std;



void swapCol(int n, double *A, int col1, int col2, double *A_copy, double *acc)
{
    for (int i = 0; i < n; i++)
    {
        int i_n = i * n;
        std::swap(A[i_n + col1], A[i_n + col2]);
        std::swap(A_copy[i_n + col1], A_copy[i_n + col2]);
    }
    std::swap(acc[col1], acc[col2]);
}

int findMax(int n, double *A, int row)
{
    int maxCol = row;
    for (int i = row + 1; i < n; i++)
    {
        int row_n = row * n;
        if (fabs(A[row_n + i]) > fabs(A[row_n + maxCol]))
        {
            maxCol = i;
        }
    }
    return maxCol;
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









void synchronize(int total_threads)
{
	static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	static pthread_cond_t condvar_in = PTHREAD_COND_INITIALIZER;
	static pthread_cond_t condvar_out = PTHREAD_COND_INITIALIZER;
	static int threads_in = 0;
	static int threads_out = 0;

	pthread_mutex_lock(&mutex);
	threads_in++;
	if (threads_in >= total_threads)
	{
		threads_out = 0;
		pthread_cond_broadcast(&condvar_in);
	} 
    else
    {
		while (threads_in < total_threads)
        {
			pthread_cond_wait(&condvar_in,&mutex);
        }
    }

	threads_out++;
	if (threads_out >= total_threads)
	{
		threads_in = 0;
		pthread_cond_broadcast(&condvar_out);
	} 
    else
    {
		while (threads_out < total_threads)
        {
			pthread_cond_wait(&condvar_out,&mutex);
        } 
    }
	pthread_mutex_unlock(&mutex);

}




void gaussianElimination(int n,double *A,double *b,int row,int start_row,int end_row)
{
    // double *AData = data->A;
    // int rowData = data->row;
    // int nData = data->n;
    // double *bData = data->b;
    
    double *row_rowPtr = A + row * n + row;
    double *b_row = b + row;

    for (int down_row = start_row; down_row < end_row; down_row++)
    {
        double *rowPtr = row_rowPtr;
        double *downRowPtr = A + down_row * n;
        double *downRow_rowPtr = downRowPtr + row;
        double *end_drPtr = downRowPtr+n;
        double ratio = -(*downRow_rowPtr) / *row_rowPtr;
            
            for (;downRow_rowPtr< end_drPtr;)
            {
                *downRow_rowPtr += ratio * (*rowPtr); 
                downRow_rowPtr++;
                rowPtr++;
            }  
        // b[down_row] += ratio * b[row];
        b[down_row] += ratio * (*b_row);
    }
}




int solve(int n, double *A, double *b, double *x, double *A_copy, double *acc,int num_thread, int p,double norma)
{
//    cout<<"lol"<<endl;
    int result = 0;
    for (int row = 0; row < n; row++)
    {
        if(num_thread == 0){

            int maxCol = findMax(n, A, row);
            if (maxCol != row)
            {
                swapCol(n, A, maxCol, row, A_copy, acc);
            }
//            cout<<A[row*n+row]<<endl;
            if(fabs(A[row*n+row])<EPS * norma) return -1;
        }
//        cout<<"lol"<<endl;
        synchronize(p);
        int Rows = n - (row + 1);      // Сколько строк нужно обработать на каждом шаге
        int Rest = Rows % p;           // остаток при делении
        int RowsPerThread = Rows/p;

        
        if (Rest == 0)
        {

            int start_row = row + 1 + num_thread * RowsPerThread;
            int end_row = row + 1 + (num_thread + 1) * RowsPerThread;
            gaussianElimination(n,A,b,row,start_row,end_row);
//            cout<< "row: " << row<<" | "<< num_thread<<" start row: "<<start_row<< " end row: "<<end_row<<endl;
            
        }
        else
        {

            if(num_thread != p-1) 
            {
                int start_row = row + 1 + num_thread * RowsPerThread;
                int end_row = row + 1 + (num_thread + 1) * RowsPerThread;
                gaussianElimination(n,A,b,row,start_row,end_row);

//                cout<< "row: " << row<<" | "<< num_thread<<" start row: "<<start_row<< " end row: "<<end_row<<endl;
            }

            else
            {
                int start_row = row + 1 + num_thread * RowsPerThread;
                int end_row = n;
                gaussianElimination(n,A,b,row,start_row,end_row);

//                cout<<" REST "<< "row: " << row<<" | "<< num_thread<<" start row: "<<start_row<< " end row: "<<end_row<<endl;
            }

        }
//        cout<<"?";
        synchronize(p);

        
//        cout<<"|||||||||||||||||||||||||||"<<endl;
    }

    if(num_thread == 0){
    result = reverse(n, A, b, x,norma);

    }

    return result;
}
