#ifndef COMPLEXNUMBERHEADERDEF
#define COMPLEXNUMBERHEADERDEF

#include <iostream>

class ComplexNumber
{
private:
    double mRealPart;
    double mImaginaryPart;

public:
    ComplexNumber();
    ComplexNumber(double x, double y);

    ComplexNumber(const ComplexNumber &z);
    ComplexNumber(double real);

    double CalculateModulus() const;
    double CalculateArgument() const;

    ComplexNumber CalculatePower(double n) const;
    ComplexNumber CalculateConjugate() const;

    ComplexNumber &operator=(const ComplexNumber &z);
    ComplexNumber operator-() const;
    ComplexNumber operator+(const ComplexNumber &z) const;
    ComplexNumber operator-(const ComplexNumber &z) const;

    friend std::ostream &operator<<(std::ostream &output, const ComplexNumber &z);

    // exercise prototypes
    double GetRealPart() const { return mRealPart; }
    double GetImaginaryPart() const { return mImaginaryPart; }

    friend double RealPart(const ComplexNumber &z);
    friend double ImaginaryPart(const ComplexNumber &z);

    void SetConjugate();

    // not mandatory, but useful for exercise 6.1.7
    ComplexNumber operator*(const ComplexNumber &z) const;
    ComplexNumber operator/(const ComplexNumber &z) const;
    ComplexNumber operator/(int n) const;
};

#endif
