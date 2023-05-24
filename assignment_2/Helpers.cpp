double factorial(double n)
{
    return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}