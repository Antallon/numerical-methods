#include "Matfill.h"

double fMat(int n, int k, int i, int j)
{

    if (k == 1)
    {
        return (n - max(i + 1, j + 1) + 1);
    }
    else if (k == 2)
    {
        return (max(i + 1, j + 1));
    }
    else if (k == 3)
    {
        return (abs(i - j));
    }
    else if (k == 4)
    {
        return (1.0 / (i + j + 1));
    }
    else
    {
        return 0;
    }
}

int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}



