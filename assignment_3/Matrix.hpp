#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <stdexcept>
#include "Vector.hpp"

template <class T>
class Matrix
{
private:
    std::vector<T> mData;   // entries of matrix
    int mNumRows, mNumCols; // dimensions

public:
    Matrix(int numRows, int numCols);
    Matrix(const Matrix &other);

    T &operator()(int row, int col);
    const T &operator()(int row, int col) const;

    int GetNumberOfRows() const;
    int GetNumberOfColumns() const;

    Matrix<T> &operator=(const Matrix<T> &otherMatrix);
    Matrix<T> operator-() const;
    Matrix<T> operator+(const Matrix<T> &m1) const;
    Matrix<T> operator*(double a) const;
    Matrix<T> operator-(const Matrix<T> &m1) const;
}; // class Matrix

// matrix-vector multiplications
template <class T>
Vector<T> operator*(const Matrix<T> &m, const Vector<T> &v);

template <class T>
Vector<T> operator*(const Vector<T> &v, const Matrix<T> &m);

#include "Matrix.cpp"

#endif
