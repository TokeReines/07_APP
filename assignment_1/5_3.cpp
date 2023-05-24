#include <cmath>

void swap_pointer(double *a, double *b)
{
    double temp = *a;
    *a = *b;
    *b = temp;
}
void swap_ref(double &a, double &b)
{
    double temp = a;
    a = b;
    b = temp;
}
