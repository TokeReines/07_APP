#include <cmath>

double calc_mean(double a[], int length)
{
    double sum = 0;
    for (int i = 0; i < length; i++)
    {
        sum += a[i];
    }
    return sum / length;
}


double calc_std(double a[], int length)
{
    double mean = calc_mean(a, length);
    double sum = 0;
    for (int i = 0; i < length; i++)
    {
        sum += std::pow(a[i] - mean, 2);
    }
    /* Make sure not to divide by 0 when lenght is 1 */
    if (length == 1)
    {
        return 0;
    }
    return std::sqrt(sum / (length - 1));
}
