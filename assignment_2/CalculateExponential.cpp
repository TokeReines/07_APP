#include <cmath>
#include "ComplexNumber.hpp"
#include "Helpers.hpp"
#include <iostream>

void SetIdentityMatrix(ComplexNumber **res, int numRows, int numCols)
{

    // Initialize the result matrix with the identity matrix
    for (int i = 0; i < numRows; ++i)
    {
        for (int j = 0; j < numCols; ++j)
        {
            if (i == j)
            {
                res[i][j] = ComplexNumber(1.0, 0.0);
            }
            else
            {
                res[i][j] = ComplexNumber(0.0, 0.0);
            }
        }
    }
}

void CalculateExponential(ComplexNumber **matrix, int nMax, ComplexNumber **result)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            ComplexNumber total;
            ComplexNumber previous = matrix[i][j];
            ComplexNumber sum = ComplexNumber(0.0, 0.0);

            if (i == j)
            {
                total = ComplexNumber(1.0, 0.0) + previous;

                for (int n = 2; n <= nMax; n++)
                {
                    previous = (matrix[i][j] / n) * previous;
                    sum = sum + previous;
                }
                total = total + sum;

                result[i][j] = total;
            }
            else
            {
                result[i][j] = total;
            }
        }
    }
}
// non mandatory
void printMatrix(ComplexNumber **A, int rows, int cols)
{
    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            std::cout << A[i][j];
        }
        printf("\n");
    }
    printf("\n-------------------------\n");
}
