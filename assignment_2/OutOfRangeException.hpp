#ifndef SUBMISSION_OUTOFRANGEEXCEPTION_HPP_
#define SUBMISSION_OUTOFRANGEEXCEPTION_HPP_

#include "Exception.hpp"

class OutOfRangeException : public Exception
{
public:
	OutOfRangeException(std::string probString);
};

#endif /* SUBMISSION_OUTOFRANGEEXCEPTION_HPP_ */
