#include "ComplexNumber.h"

ComplexNumber::ComplexNumber(double real, double imaginary)
    : real_(real), imaginary_(imaginary) {}

double ComplexNumber::getReal() const { return real_; }
double ComplexNumber::getImaginary() const { return imaginary_; }
void ComplexNumber::setReal(double real) { real_ = real; }
void ComplexNumber::setImaginary(double imaginary) { imaginary_ = imaginary; }

ComplexNumber ComplexNumber::operator+(const ComplexNumber& other) const {
    return ComplexNumber(real_ + other.real_, imaginary_ + other.imaginary_);
}

ComplexNumber ComplexNumber::operator-(const ComplexNumber& other) const {
    return ComplexNumber(real_ - other.real_, imaginary_ - other.imaginary_);
}

ComplexNumber ComplexNumber::operator*(const ComplexNumber& other) const {
    double real = real_ * other.real_ - imaginary_ * other.imaginary_;
    double imaginary = real_ * other.imaginary_ + imaginary_ * other.real_;
    return ComplexNumber(real, imaginary);
}

ComplexNumber ComplexNumber::square() const {
    return ComplexNumber(real_ * real_ - imaginary_ * imaginary_, 2.0 * real_ * imaginary_);
}