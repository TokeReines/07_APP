#include "Matrix2x2.hpp"

Matrix2x2::Matrix2x2()
{
	val00 = 0.0;
	val01 = 0.0;
	val10 = 0.0;
	val11 = 0.0;
}

Matrix2x2::Matrix2x2(const Matrix2x2 &other)
{
	val00 = other.Getval00();
	val01 = other.Getval01();
	val10 = other.Getval10();
	val11 = other.Getval11();
}

Matrix2x2::Matrix2x2(double a, double b, double c, double d)
{
	val00 = a;
	val01 = b;
	val10 = c;
	val11 = d;
}

double Matrix2x2::CalcDeterminant() const
{
	return val00 * val11 - val01 * val10;
}

Matrix2x2 Matrix2x2::CalcInverse() const
{
	double determinant = CalcDeterminant();
	if (determinant == 0)
	{
		std::cout << "Error: Determinant is zero!" << std::endl;
		return Matrix2x2();
	}
	double a = val11 / determinant;
	double b = -val01 / determinant;
	double c = -val10 / determinant;
	double d = val00 / determinant;
	return Matrix2x2(a, b, c, d);
}

Matrix2x2 &Matrix2x2::operator=(const Matrix2x2 &z)
{
	val00 = z.Getval00();
	val01 = z.Getval01();
	val10 = z.Getval10();
	val11 = z.Getval11();
	return *this;
}

Matrix2x2 Matrix2x2::operator-() const
{
	return Matrix2x2(-val00, -val01, -val10, -val11);
}

Matrix2x2 Matrix2x2::operator+(const Matrix2x2 &z) const
{
	return Matrix2x2(val00 + z.Getval00(), val01 + z.Getval01(), val10 + z.Getval10(), val11 + z.Getval11());
}

Matrix2x2 Matrix2x2::operator-(const Matrix2x2 &z) const
{
	return Matrix2x2(val00 - z.Getval00(), val01 - z.Getval01(), val10 - z.Getval10(), val11 - z.Getval11());
}

void Matrix2x2::MultScalar(double scalar)
{
	val00 *= scalar;
	val01 *= scalar;
	val10 *= scalar;
	val11 *= scalar;
}

void Matrix2x2::Print() const
{
	std::cout << "[" << val00 << " " << val01 << "]" << std::endl;
	std::cout << "[" << val10 << " " << val11 << "]" << std::endl;
}
