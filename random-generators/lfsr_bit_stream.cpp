#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdint>

using namespace std;

int popcount(uint32_t x) 
{
// Подсчитывает количество единичных битов в числе x
    int c = 0;
    while (x) 
    { 
        c += x & 1; 
        x >>= 1;
    }
    return c;
}

int main() 
{
    uint32_t a = (1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<5)|(1<<7);
    uint32_t b = std::rand();
    uint32_t freq[256] = {0};

    for (int n = 0; n < 1000000; n++) 
    {
        uint32_t out = 0;
        for (int i = 0; i < 8; i++) 
        {
            uint32_t c = popcount(a & b) & 1;// посчитали количество единиц и взяли последний бит\\\\ если колиечство единиц четное-0, нечётное 1
            uint32_t last = (b >> 31) & 1;
            out = (out << 1) | last;
            b = (b << 1) | c;
        }
        freq[out]++;
    }

    for (int i = 0; i < 256; i++)
        cout << i << " : " << freq[i] << endl;

    return 0;
}
