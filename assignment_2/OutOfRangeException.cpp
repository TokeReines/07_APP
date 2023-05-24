#include "OutOfRangeException.hpp"

OutOfRangeException::OutOfRangeException(std::string probString) : Exception("Out of range", probString)
{
}