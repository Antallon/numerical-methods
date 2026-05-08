#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstdint>

using namespace std;
int main(void)
{
    int n = 0, m = 0, N = 1000000;     
    uint32_t x0, x1, x2;           // (0,....,2**32 - 1) 4 байта
    uint64_t sum;                  // (0,....,2**64 - 1) 8 байт
    uint64_t mask = 0xffffffffUL;   // 32 нуля и 32 единицы вследствие того что у нас 8f каждая f = 1111
                                                                           
    x0 = rand();
    x1 = rand();

    for(int i = 1; i < N; i++)
    {
        sum = (uint64_t)((uint64_t)x0 + (uint64_t)x1); // Здесь мы переходим в 64 бита чтобы не было переполнения так как два uint32 могут максимум быть 2^33 -2 
        x2  = (uint32_t)(mask & sum);                  // побитовое И которое отбрасывает первые 32 бита так как в маске они нули 
                                                       // то же самое что и %2**32

        if((x0 < x1) && (x1 < x2))n++;
        else if((x2 < x1) && (x1 < x0)) m++;
    
        x0 = x1;
        x1 = x2;
        x2 = 0;
    }

    cout << (double)n / N << " " << (double)m / N << endl;

    return 0;
}