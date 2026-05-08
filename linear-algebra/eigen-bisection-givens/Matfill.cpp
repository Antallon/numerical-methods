#include "Matfill.h"

double fMat(const int n, const int k, const int i, const int j)
{

    if (k == 1)
    {
        return (n - max(i + 1, j + 1) + 1);
    }

    else if (k == 2)
    {
        if (i == j)
        {
            return 2.0;
        }
        if (abs(i - j) == 1)
        {
            return -1.0;
        }
        else
        {
            return 0.0;
        }
    }

    else if (k == 3)
    {
        if (i == j && j + 1 < n)
        {
            return 1.0;
        }
        if (j + 1 == n)
        {
            return i + 1;
        }
        if (i + 1 == n)
        {
            return j + 1;
        }
        else
        {
            return 0.0;
        }
    }

    else if (k == 4)
    {
        return (1.0 / (i + j + 1));
    }

    else{
        return -1;
    }


}

int max(const int a, const int b)
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
