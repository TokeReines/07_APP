#include <iostream>
#include <cmath>

double f(double x)
{
    return std::exp(x) + std::pow(x, 3) - 5.0;
}

double fPrime(double x)
{
    return std::exp(x) + 3.0 * std::pow(x, 2);
}

double newton_Raphson(double initialGuess, double epsilon)
{
    double x0 = initialGuess;
    double x1 = x0 - f(x0) / fPrime(x0);
    while (std::abs(x1 - x0) > epsilon) {
        x0 = x1;
        x1 = x0 - f(x0) / fPrime(x0);
    }
    return x1;
}
