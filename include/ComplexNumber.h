#ifndef COMPLEXNUMBER_H_
#define COMPLEXNUMBER_H_
#include <opencv2/opencv.hpp>
using namespace std;

class ComplexNumber {
public:
	ComplexNumber(double real = 0.0, double imaginary = 0.0);
	double getReal() const;
	double getImaginary() const;
	void setReal(double real);
	void setImaginary(double imaginary);
	ComplexNumber operator+(const ComplexNumber& other) const;
	ComplexNumber operator-(const ComplexNumber& other) const;
	ComplexNumber operator*(const ComplexNumber& other) const;
	ComplexNumber square() const;
private:
	double real_;
	double imaginary_;
};
#endif /* COMPLEXNUMBER_H_ */