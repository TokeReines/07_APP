#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cassert>
#include <stdexcept>
#include <cmath>
#include <vector>

template <class T>
class Vector
{
private:
    std::vector<T> mData; // data stored in vector
    int mSize; // size of vector

public:
    Vector(int size);
    Vector(const Vector& other);

    T& operator[](int index);
    const T& operator[](int index) const;

    int getSize() const;
    
	// assignment operator
	Vector& operator=(const Vector& otherVector);

    // overloading the unary - operator
	Vector operator-() const;

    // overloading the binary + operator
	Vector operator+(const Vector& v1) const;

    // overloading the binary - operator
	Vector operator-(const Vector& v1) const;

	// scalar multiplication
	Vector operator*(double a) const;

	// p-norm method
	double CalculateNorm(int p = 2) const;
};

#include "Vector.cpp"

#endif
