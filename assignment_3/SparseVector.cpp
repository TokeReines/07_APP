#ifndef SPARSE_VECTOR_CPP
#define SPARSE_VECTOR_CPP

#include "SparseVector.hpp"

// Construct SparseVector with given dimension
template <class T>
SparseVector<T>::SparseVector(unsigned int dim)
{
	mSize = dim;
	// init mData with empty vector
	mData = std::vector<std::pair<unsigned int, T>>();
}

template <class T>
SparseVector<T>::SparseVector()
{
	mSize = 0;
	mData = std::vector<std::pair<unsigned int, T>>();
}


template <class T>
inline void SparseVector<T>::setValue(unsigned int index, T value)
{
	// Check if the index is greater than the current size
	if (index >= mSize)
		mSize = index + 1; // Update the size of the vector

	// Find the position to insert or update the value using lower_bound
	auto it = std::lower_bound(mData.begin(), mData.end(), std::make_pair(index, value),
							   [](const std::pair<unsigned int, T> &a, const std::pair<unsigned int, T> &b)
							   {
								   return a.first < b.first;
							   });

	if (it != mData.end() && it->first == index)
	{
		// Index already exists, update the corresponding value
		it->second = value;
	}
	else
	{
		// Index doesn't exist, insert the index-value pair at the found position
		mData.insert(it, std::make_pair(index, value));
	}
}

template <class T>
T SparseVector<T>::getValue(unsigned int index) const
{
	// Check if the index is out of bounds
	if (index >= mSize)
		return T(); // Index is not stored, return default value (0)
		
	// Find the position of the index using lower_bound
	auto it = std::lower_bound(mData.begin(), mData.end(), std::make_pair(index, T()),
							   [](const std::pair<unsigned int, T> &a, const std::pair<unsigned int, T> &b)
							   {
								   return a.first < b.first;
							   });

	if (it != mData.end() && it->first == index)
	{
		// Index exists, return the corresponding value
		return it->second;
	}
	else
	{
		// Index doesn't exist, return default value (0)
		return T();
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

template <class T>
std::vector<T> const &SparseVector<T>::getStorage()
{
	return mData;
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