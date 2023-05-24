#include "Student.hpp"
#include "GraduateStudent.hpp"

double GraduateStudent::MoneyOwed() const
{
	return GetLibraryFines();
}

GraduateStudent::GraduateStudent()
{
	fullTime = false;
}

GraduateStudent::GraduateStudent(std::string name, double fines, double fees, bool fullTime) : Student(name, fines, fees)
{
	this->fullTime = fullTime;
}
