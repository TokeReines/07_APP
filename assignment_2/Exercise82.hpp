#ifndef SUBMISSION_EXERCISE82_HPP_
#define SUBMISSION_EXERCISE82_HPP_

template<typename T>
T CalcAbs(T val) {
	// Use templates to write a single function that may be used to calculate the absolute value of an integer or a double precision floating point number
	if (val < 0) {
		return -val;
	}
	else {
		return val;
	}
}


#endif /* SUBMISSION_EXERCISE82_HPP_ */
