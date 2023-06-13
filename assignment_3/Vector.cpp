#ifndef VECTOR_CPP
#define VECTOR_CPP

#include "Vector.hpp"

template <class T>
Vector<T>::Vector(int size) : mData(size), mSize(size) {}

template <class T>
Vector<T>::Vector(const Vector &other) : mData(other.mData), mSize(other.mSize) {}

template <class T>
T &Vector<T>::operator[](int index)
{
    return mData[index];
}

template <class T>
const T &Vector<T>::operator[](int index) const
{
    return mData[index];
}

template <class T>
int Vector<T>::size() const
{
    return mSize;
}

// assignment operator
template <class T>
Vector<T> &Vector<T>::operator=(const Vector &otherVector)
{
    assert(mSize == otherVector.mSize);

    for (unsigned int i = 0; i < mSize; i++)
    {
        mData[i] = otherVector.mData[i];
    }
    return *this;
}

// overloading the unary - operator
template <class T>
Vector<T> Vector<T>::operator-() const
{
    Vector v(mSize);
    for (unsigned int i = 0; i < mSize; i++)
    {
        v[i] = -mData[i];
    }
    return v;
}

// overloading the binary + operator
template <class T>
Vector<T> Vector<T>::operator+(const Vector &v1) const
{
    assert(mSize == v1.mSize);

    Vector v(mSize);
    for (unsigned int i = 0; i < mSize; i++)
    {
        v[i] = mData[i] + v1.mData[i];
    }
    return v;
}

// overloading the binary - operator
template <class T>
Vector<T> Vector<T>::operator-(const Vector &v1) const
{
    assert(mSize == v1.mSize);

    Vector v(mSize);
    for (int i = 0; i < mSize; i++)
    {
        v[i] = mData[i] - v1.mData[i];
    }
    return v;
}

// scalar multiplication
template <class T>
Vector<T> Vector<T>::operator*(double a) const
{
    Vector v(mSize);
    for (int i = 0; i < mSize; i++)
    {
        v[i] = a * mData[i];
    }
    return v;
}

// p-norm method
template <class T>
double Vector<T>::CalculateNorm(int p) const
{
    double sum = 0.0;
    for (int i = 0; i < mSize; i++)
    {
        sum += std::pow(std::abs(mData[i]), p);
    }
    return std::pow(sum, 1.0 / ((double)(p)));
};

template <class T>
inline std::vector<T> const &Vector<T>::getStorage()
{
    return mData;
}

#endif
