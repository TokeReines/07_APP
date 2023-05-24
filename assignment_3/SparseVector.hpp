#ifndef SPARSE_VECTOR_HPP
#define SPARSE_VECTOR_HPP

#include <vector>
#include <algorithm>

#include "Vector.hpp"
#include "Matrix.hpp"

template <class T>
class SparseVector
{
private:
	// Add your data members here!
	std::vector<std::pair<int, T>> mData; // data stored in vector as (index, value) pairs
	int mSize;							  // size of vector
public:
	// Creates a vector of dimensionality dim. It starts with 0 nonzero elements
	// which need to be set using setValue
	SparseVector(unsigned int dim);
    // SparseVector(const SparseVector<T> &other);

	// assignment operators and copy constructor should be automatically
	// generated by the compiler when using a std::vector for internal storing.
	// However, test that assignment works!

	// sets the value v_i of the vector. if it does not exist it is added
	void setValue(unsigned int index, T value);

	// returns the value v_i of the vector. Returns 0 if the value is not stored
	T getValue(unsigned int index) const;

	// returns the dimensionality of the vector
	unsigned int size() const;

	// returns the number stored elements
	unsigned int nonZeroes() const;

	// returns the index of the ith stored nonzero entry (in increasing order)
	unsigned int indexNonZero(unsigned int i) const;

	// returns the value of the ith stored nonzero entry (in increasing order)
	T valueNonZero(unsigned int i) const;

	// adds x too the current vector
	SparseVector<T> &operator+=(SparseVector<T> const &x);
	// subtracts x from the current vector
	SparseVector<T> &operator-=(SparseVector<T> const &x);
};

// computes z= x+y, equivalent to z=x, z+=y
template <class T>
SparseVector<T> operator+(SparseVector<T> const &x, SparseVector<T> const &y);

// computes z= x-y, equivalent to z=x, z-=y
template <class T>
SparseVector<T> operator-(SparseVector<T> const &x, SparseVector<T> const &y);

// computes the matrix-vector product of a dense matrix and sparse vector z=Ax.
// The result is a dense vector.
template <class T>
Vector<T> operator*(Matrix<T> const &A, SparseVector<T> const &x);

// computes the matrix-vector product of a dense matrix and sparse vector z=x^TA.
// The result is a dense vector.
template <class T>
Vector<T> operator*(SparseVector<T> const &x, Matrix<T> const &A);

#include "SparseVector.cpp"

#endif
