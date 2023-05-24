#ifndef MATRIX_CPP
#define MATRIX_CPP

#include <vector>
#include <stdexcept>
#include "Vector.hpp"
#include "Matrix.hpp"


template <class T>
Matrix<T>::Matrix(int numRows, int numCols)
    : mData(numRows * numCols), mNumRows(numRows), mNumCols(numCols) {}

template <class T>
Matrix<T>::Matrix(const Matrix &other)
    : mData(other.mData), mNumRows(other.mNumRows), mNumCols(other.mNumCols) {}

template <class T>
T &Matrix<T>::operator()(int row, int col) { return mData[row * mNumCols + col]; }

template <class T>
const T &Matrix<T>::operator()(int row, int col) const { return mData[row * mNumCols + col]; }

template <class T>
int Matrix<T>::GetNumberOfRows() const { return mNumRows; }

template <class T>
int Matrix<T>::GetNumberOfColumns() const { return mNumCols; }
template <class T>
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &otherMatrix) {
    if (this != &otherMatrix) {
        mData = otherMatrix.mData;
        mNumRows = otherMatrix.mNumRows;
        mNumCols = otherMatrix.mNumCols;
    }
    return *this;
}

template <class T>
Matrix<T> Matrix<T>::operator-() const {
    Matrix<T> result(mNumRows, mNumCols);
    for (int i = 0; i < mData.size(); i++) {
        result.mData[i] = -mData[i];
    }
    return result;
}

template <class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &m1) const {
    Matrix<T> result(mNumRows, mNumCols);
    for (int i = 0; i < mData.size(); i++) {
        result.mData[i] = mData[i] + m1.mData[i];
    }
    return result;
}

template <class T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &m1) const {
    Matrix<T> result(mNumRows, mNumCols);
    for (int i = 0; i < mData.size(); i++) {
        result.mData[i] = mData[i] - m1.mData[i];
    }
    return result;
}

// scalar multiplication
template <class T>
Matrix<T> Matrix<T>::operator*(double a) const
{
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows * mNumCols; i++)
    {
        result.mData[i] = mData[i] * a;
    }

    return result;
}

// matrix-vector multiplications
template <class T>
Vector<T> operator*(const Matrix<T> &m, const Vector<T> &v)
{
    int numRows = m.GetNumberOfRows();
    int numCols = m.GetNumberOfColumns();
    int vectorSize = v.getSize();

    assert(numCols == vectorSize);

    Vector<T> result(numRows);

    for (int i = 0; i < numRows; i++)
    {
        T sum = 0;
        for (int j = 0; j < numCols; j++)
        {
            sum += m(i, j) * v[j];
        }
        result[i] = sum;
    }

    return result;
}

template <class T>
Vector<T> operator*(const Vector<T> &v, const Matrix<T> &m)
{
    int numRows = m.GetNumberOfRows();
    int numCols = m.GetNumberOfColumns();
    int vectorSize = v.getSize();

    assert(vectorSize == numRows);

    Vector<T> result(numCols);

    for (int i = 0; i < numCols; i++)
    {
        T sum = 0;
        for (int j = 0; j < vectorSize; j++)
        {
            sum += v[j] * m(j, i);
        }
        result[i] = sum;
    }

    return result;
}

#endif
