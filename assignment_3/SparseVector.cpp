#ifndef SPARSE_VECTOR_CPP
#define SPARSE_VECTOR_CPP

#include "SparseVector.hpp"

template <class T>
SparseVector<T>::SparseVector(unsigned int dim) : mSize(dim) {}

// template <class T>
// SparseVector<T>::SparseVector(const SparseVector<T> &other)
// {
//     mSize = other.mSize;
//     mData = other.mData;
// }

template <class T>
inline void SparseVector<T>::setValue(unsigned int index, T value)
{
	// Search for the index in the mData vector
	for (auto &entry : mData)
	{
		if (entry.first == index)
		{
			entry.second = value;
			return;
		}
	}
	// If the index is not found, add a new entry
	mData.push_back(std::make_pair(index, value));
}

template <class T>
T SparseVector<T>::getValue(unsigned int index) const
{
	unsigned int pos = indexNonZero(index);

	if (pos < mData.size() && mData[pos].first == index)
	{
		return mData[pos].second;
	}
	else
	{
		return T(); // Return default value when index is not found
	}
}

template <class T>
unsigned int SparseVector<T>::size() const
{
	return mSize;
}

template <class T>
unsigned int SparseVector<T>::nonZeroes() const
{
	return mData.size();
}

template <class T>
unsigned int SparseVector<T>::indexNonZero(unsigned int i) const
{
	if (i < mData.size())
	{
		return mData[i].first;
	}
	// Handle out-of-range access
	throw std::out_of_range("Index out of range in indexNonZero()");
}

template <class T>
T SparseVector<T>::valueNonZero(unsigned int i) const
{
	if (i < mData.size())
	{
		return mData[i].second;
	}
	// Handle out-of-range access
	throw std::out_of_range("Index out of range in valueNonZero()");
}

template <class T>
SparseVector<T> &SparseVector<T>::operator+=(SparseVector<T> const &x)
{
	if (mSize != x.mSize)
	{
		throw std::invalid_argument("Vector sizes are not equal in operator+=()");
	}

	// Perform element-wise addition
	for (const auto &entry : x.mData)
	{
		unsigned int index = entry.first;
		T value = entry.second;

		// Check if the index exists in the current vector
		auto iter = std::lower_bound(mData.begin(), mData.end(), index,
									 [](const std::pair<unsigned int, T> &p, unsigned int index)
									 {
										 return p.first < index;
									 });

		if (iter != mData.end() && iter->first == index)
		{
			iter->second += value; // Entry already exists, add to its value
		}
		else
		{
			mData.insert(iter, std::make_pair(index, value)); // Insert new entry
		}
	}

	return *this;
}

template <class T>
SparseVector<T> &SparseVector<T>::operator-=(SparseVector<T> const &x)
{
	if (mSize != x.mSize)
	{
		throw std::invalid_argument("Vector sizes are not equal in operator-=()");
	}

	// Perform element-wise subtraction
	for (const auto &entry : x.mData)
	{
		unsigned int index = entry.first;
		T value = entry.second;

		// Check if the index exists in the current vector
		auto iter = std::lower_bound(mData.begin(), mData.end(), index,
									 [](const std::pair<unsigned int, T> &p, unsigned int index)
									 {
										 return p.first < index;
									 });

		if (iter != mData.end() && iter->first == index)
		{
			iter->second -= value; // Entry already exists, subtract its value
		}
		else
		{
			mData.insert(iter, std::make_pair(index, -value)); // Insert new entry with negated value
		}
	}

	return *this;
}

// computes z= x+y, equivalent to z=x, z+=y
template <class T>
SparseVector<T> operator+(SparseVector<T> const &x, SparseVector<T> const &y)
{
	if (x.size() != y.size())
	{
		throw std::invalid_argument("Vector sizes are not equal in operator+()");
	}

	SparseVector<T> z(x);
	z += y;

	return z;
}

// computes z= x-y, equivalent to z=x, z-=y
template <class T>
SparseVector<T> operator-(SparseVector<T> const &x, SparseVector<T> const &y)
{
	if (x.size() != y.size())
	{
		throw std::invalid_argument("Vector sizes are not equal in operator-()");
	}

	SparseVector<T> z(x);
	z -= y;

	return z;
}

// computes the matrix-vector product of a dense matrix and sparse vector z=Ax.
// The result is a dense vector.
template <class T>
Vector<T> operator*(Matrix<T> const &A, SparseVector<T> const &x)
{
	if (A.GetNumberOfColumns() != x.size())
	{
		throw std::invalid_argument("Matrix and vector dimensions are not compatible in operator*()");
	}

	int numRows = A.GetNumberOfRows();
	Vector<T> result(numRows);

	for (int i = 0; i < numRows; i++)
	{
		T sum = 0;

		for (unsigned int j = 0; j < x.nonZeroes(); j++)
		{
			unsigned int columnIndex = x.indexNonZero(j);
			T value = x.valueNonZero(j);

			sum += A(i, columnIndex) * value;
		}

		result[i] = sum;
	}

	return result;
}

// computes the matrix-vector product of a dense matrix and sparse vector z=x^TA.
// The result is a dense vector.
template <class T>
Vector<T> operator*(SparseVector<T> const &x, Matrix<T> const &A)
{
	if (A.GetNumberOfRows() != x.size())
	{
		throw std::invalid_argument("Matrix and vector dimensions are not compatible in operator*()");
	}

	int numCols = A.GetNumberOfColumns();
	Vector<T> result(numCols);

	for (unsigned int i = 0; i < x.nonZeroes(); i++)
	{
		unsigned int rowIndex = x.indexNonZero(i);
		T value = x.valueNonZero(i);

		for (int j = 0; j < numCols; j++)
		{
			result[j] += A(rowIndex, j) * value;
		}
	}

	return result;
}
#endif // SPARSEVECTOR_CPP