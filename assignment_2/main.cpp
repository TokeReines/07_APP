#include "ComplexNumber.hpp"
#include "CalculateExponential.hpp"
#include "Matrix2x2.hpp"
#include "GraduateStudent.hpp"
#include "PhdStudent.hpp"
#include "Exception.hpp"
#include "FileNotOpenException.hpp"
#include "OutOfRangeException.hpp"

using namespace std;

void testComplexNumber()
{
    // Create a 3x3 diagonal matrix with complex numbers on the diagonal
    ComplexNumber **A = new ComplexNumber *[3];
    for (int i = 0; i < 3; ++i)
    {
        A[i] = new ComplexNumber[3];
        for (int j = 0; j < 3; ++j)
        {
            if (i == j)
            {
                if (i == 0)
                    A[i][j] = ComplexNumber(2, 3); // (2+3i)
                else if (i == 1)
                    A[i][j] = ComplexNumber(4, 5); // (4+5i)
                else
                    A[i][j] = ComplexNumber(6, 7); // (6+7i)
            }
            else
            {
                A[i][j] = ComplexNumber(0); // Fill other elements with 0
            }
        }
    }

    // Create a 3x3 matrix to store the result
    ComplexNumber **res = new ComplexNumber *[3];
    for (int i = 0; i < 3; ++i)
    {
        res[i] = new ComplexNumber[3];
    }

    // Call the CalculateExponential function
    CalculateExponential(A, 50, res);

    // Display the result
    printMatrix(res, 3, 3);

    // Clean up memory
    for (int i = 0; i < 3; ++i)
    {
        delete[] A[i];
        delete[] res[i];
    }
    delete[] A;
    delete[] res;
}

void testStudent()
{
    GraduateStudent s1("John Smith", 25, 3, true);
    PhdStudent s2("Jane Doe", 25, 3, true);
    std::cout << "GraduateStudent money owed " << s1.MoneyOwed() << std::endl;
    std::cout << "PhdStudent money owed " << s2.MoneyOwed() << std::endl;
}

void testException()
{
    // Test FileNotOpenException
    try
    {
        throw FileNotOpenException("Test message");
    }
    catch (FileNotOpenException &e)
    {
        e.PrintDebug();
    }

    // Test OutOfRangeException
    try
    {
        throw OutOfRangeException("Test message");
    }
    catch (OutOfRangeException &e)
    {
        e.PrintDebug();
    }
}

int main()
{
    testComplexNumber();
    testStudent();
    testException();
    return 0;
}