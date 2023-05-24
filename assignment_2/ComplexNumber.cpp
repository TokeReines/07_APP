#include "ComplexNumber.hpp"
#include "math.h"

ComplexNumber ComplexNumber::operator*(const ComplexNumber &z) const
{
    double real = mRealPart * z.mRealPart - mImaginaryPart * z.mImaginaryPart;
    double imag = mRealPart * z.mImaginaryPart + mImaginaryPart * z.mRealPart;
    return ComplexNumber(real, imag);
}

ComplexNumber ComplexNumber::operator/(const ComplexNumber &z) const
{
    double denominator = z.mRealPart * z.mRealPart + z.mImaginaryPart * z.mImaginaryPart;
    double real = (mRealPart * z.mRealPart + mImaginaryPart * z.mImaginaryPart) / denominator;
    double imag = (mImaginaryPart * z.mRealPart - mRealPart * z.mImaginaryPart) / denominator;
    return ComplexNumber(real, imag);
}

ComplexNumber ComplexNumber::operator/(int n) const
{
    return ComplexNumber(mRealPart / n, mImaginaryPart / n);
}

ComplexNumber::ComplexNumber()
{
    mRealPart = 0.0;
    mImaginaryPart = 0.0;
}

ComplexNumber::ComplexNumber(double x, double y)
{
    mRealPart = x;
    mImaginaryPart = y;
}

ComplexNumber::ComplexNumber(const ComplexNumber &z)
{
    mRealPart = z.GetRealPart();
    mImaginaryPart = z.GetImaginaryPart();
}

ComplexNumber::ComplexNumber(double real)
{
    mRealPart = real;
    mImaginaryPart = 0.0;
}

double ComplexNumber::CalculateModulus() const
{
    return sqrt(mRealPart * mRealPart + mImaginaryPart * mImaginaryPart);
}

double ComplexNumber::CalculateArgument() const
{
    return atan2(mImaginaryPart, mRealPart);
}

ComplexNumber ComplexNumber::CalculatePower(double n) const
{
    double modulus = CalculateModulus();
    double argument = CalculateArgument();
    double mod_of_result = pow(modulus, n);
    double arg_of_result = n * argument;
    double real = mod_of_result * cos(arg_of_result);
    double imag = mod_of_result * sin(arg_of_result);
    return ComplexNumber(real, imag);
}

ComplexNumber ComplexNumber::CalculateConjugate() const
{
    return ComplexNumber(mRealPart, -mImaginaryPart);
}

ComplexNumber &ComplexNumber::operator=(const ComplexNumber &z)
{
    mRealPart = z.GetRealPart();
    mImaginaryPart = z.GetImaginaryPart();
    return *this;
}

ComplexNumber ComplexNumber::operator-() const
{
    return ComplexNumber(-mRealPart, -mImaginaryPart);
}

ComplexNumber ComplexNumber::operator+(const ComplexNumber &z) const
{
    return ComplexNumber(mRealPart + z.GetRealPart(), mImaginaryPart + z.GetImaginaryPart());
}

ComplexNumber ComplexNumber::operator-(const ComplexNumber &z) const
{
    return ComplexNumber(mRealPart - z.GetRealPart(), mImaginaryPart - z.GetImaginaryPart());
}

std::ostream &operator<<(std::ostream &output, const ComplexNumber &z)
{
    output << "(" << z.GetRealPart() << "," << z.GetImaginaryPart() << ")";
    return output;
}

double RealPart(const ComplexNumber &z)
{
    return z.GetRealPart();
}

double ImaginaryPart(const ComplexNumber &z)
{
    return z.GetImaginaryPart();
}

void ComplexNumber::SetConjugate()
{
    mImaginaryPart = -mImaginaryPart;
}
