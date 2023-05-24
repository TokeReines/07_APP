#include "GraduateStudent.hpp"
#include "PhdStudent.hpp"

double PhdStudent::MoneyOwed() const
{
	return 0.0;
}

PhdStudent::PhdStudent(std::string name, double fines, double fees, bool fullTime) : GraduateStudent(name, fines, fees, fullTime) {};