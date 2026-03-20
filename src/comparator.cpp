#include "comparator.h"

int cmp_with_number(double n1, double n2)
{
    const double eps = 1e-5;
    return n2 - eps <= n1 && n1 <= n2 + eps;
}

