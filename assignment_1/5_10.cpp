#include <iostream>
#include <cmath>

using namespace std;

void swap(double *row1, double *row2, int n)
{
    for (int i = 0; i <= n; ++i)
    {
        double temp = row1[i];
        row1[i] = row2[i];
        row2[i] = temp;
    }
}

void display_matrix(double **A, double *b, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%6.2f", A[i][j]);
            if (j == n - 1)
                printf(" |%6.1f", b[i]);
        }
        printf("\n");
    }
    // printf("b: \n");
    // for (int i = n - 1; i >= 0; i--)
    //     printf("%6.1f\n", b[i]);
    printf("\n-------------------------\n");
}

void guassian_elimination(double **A, double *b, double *u, int n)
{
    for (int i = 0; i < n; ++i)
    {
        display_matrix(A, b, n);
        // Pivoting
        int pivot_index = i;
        double max_value = fabs(A[i][i]);
        for (int j = i + 1; j < n; ++j)
        {
            if (fabs(A[j][i]) > max_value)
            {
                pivot_index = j;
                max_value = fabs(A[j][i]);
            }
        }
        if (pivot_index != i)
        {
            // std::swap(A[i], A[pivot_index]);
            //  std::swap(&b[i], &b[pivot_index]);
            swap(A[i], A[pivot_index], n);
            double temp = b[i];
            b[i] = b[pivot_index];
            b[pivot_index] = temp;
            // swap(&b[i], &b[pivot_index], 1);
        }
        printf("Pivoting:\n");
        display_matrix(A, b, n);

        // Elimination
        for (int j = i + 1; j < n; ++j)
        {
            double factor = A[j][i] / A[i][i];
            for (int k = i; k < n; ++k)
            {
                A[j][k] -= factor * A[i][k];
            }
            b[j] -= factor * b[i];
            A[j][i] = 0.0;
            printf("Elimination by factor %f:\n", factor);
            display_matrix(A, b, n);
            printf("\n");
        }
    }

    // Back substitution
    for (int i = n - 1; i >= 0; --i)
    {
        double sum = 0.0;
        for (int j = i + 1; j < n; ++j)
        {
            sum += A[i][j] * u[j];
        }
        u[i] = (b[i] - sum) / A[i][i];
    }
}