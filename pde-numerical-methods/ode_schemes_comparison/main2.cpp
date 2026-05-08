#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>                                               //Для setw
#include "solve2.hpp"
#include <cmath>

#include <math.h>
#include <cmath>
using namespace std;
#define pi 3.14159265358979323846



int main()
{   
    int N       = 1000;
    int N_step  = 10;
    int N_num   = 11;
    double A    = 1000.0;
    double y0   = 1.0;
    double err1;
    double err2;
    double err3;
    double err4; 

    ofstream File("result.txt");
    cout<<"Process start "<<endl<<endl;
    vector<double> N_arr(N_num);

    for(int i=0;i<N_num;i++)
    {
        // cout<<i<<" "<<N<<endl;
        err1 = aprox(N,A,y0,1,1.0);
        err2 = aprox(N,A,y0,2,1.0);
        err3 = aprox(N,A,y0,3,1.0);
        err4 = aprox(N,A,y0,4,0.01);
        
        File <<N<<" "<<err1<<" "<<err2<<" "<<err3<<" "<<err4<<endl;
        // N+=N_step;
        N*=2;
        
    } 


    
    
    return 0;
    
}
