#include <cmath>
#include <cassert>

void solve3by3(double **A, double *b, double *u) {
    // Compute the determinant of the 3x3 matrix A
    double det = 0;
    for(int i = 0; i < 3; i++) {
        det = det + (A[0][i] * (A[1][(i+1)%3] * A[2][(i+2)%3] - A[1][(i+2)%3] * A[2][(i+1)%3]));
    }

    // Check that the determinant is nonzero, for singular matrices
    assert(det != 0.0);

    // Compute the inverse of A
    double Ainv[3][3];
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++) {
            Ainv[i][j]=((A[(j+1)%3][(i+1)%3] * A[(j+2)%3][(i+2)%3]) - (A[(j+1)%3][(i+2)%3] * A[(j+2)%3][(i+1)%3]))/ det;
        }
    }

    // Compute the solution u = A^(-1) * b
    for (int i = 0; i < 3; i++) {
        u[i] = 0.0;
        for (int j = 0; j < 3; j++) {
            u[i] += Ainv[i][j] * b[j];
        }
    }
}
