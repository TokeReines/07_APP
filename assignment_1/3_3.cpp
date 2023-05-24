#include <fstream>
#include <cmath>
#include <cassert>
#include <iostream>

using namespace std;

// Define the differential equation y' = f(x,y) = -y
double f(double x, double y)
{
    return -y;
}

// Define the backward Euler method for solving ODEs
double backward_euler(double x, double y, double h)
{
    return (y) / (1 + h);
}

void implicit_Euler(int n)
{
    assert (n > 1);
    // Check if the number of grid points is greater than 1
    if (n < 1)
    {
        cout << "Error: n must be greater than 1" << endl;
        return;
    }

    // Set the interval and step size
    double x0 = 0.0;
    double xn = 1.0;
    double h = (xn - x0) / (n - 1);

    // Set the initial condition
    double y0 = 1.0;

    // Open the file for output
    ofstream outfile("xy.dat");
    outfile.precision(10);

    // Implement the backward Euler method
    double x = x0;
    double y = y0;
    outfile << x << "," << y;
    for (int i = 1; i < n; i++)
    {
        y = backward_euler(x + h, y, h);
        x = x + h;
        outfile << "\n" << x << "," << y;
    }

    // Close the file
    outfile.close();
}