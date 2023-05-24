#include "Student.hpp"

Student::Student()
{
	name = "";
	tuition_fees = 0.0;
	library_fines = 0.0;
}

Student::Student(std::string name, double fines, double fees)
{
	this->name = name;
	tuition_fees = fees;
	library_fines = fines;
}

double Student::MoneyOwed() const
{
	return tuition_fees + library_fines;
}

void Student::SetLibraryFines(double amount)
{
	library_fines = abs(amount);
}

double Student::GetLibraryFines() const
{
	return library_fines;
}

std::ostream &operator<<(std::ostream &output, const Student &s)
{
	output << "Name: " << s.name << "\n"
		<< "Fees: " << s.tuition_fees << "\n"
		<< "Fines: " << s.GetLibraryFines() << "\n"
		<< "Total: " << s.MoneyOwed() << "\n";
	return output;
}