#define _USE_MATH_DEFINES
#include "../include/ClassComplexNumber.h"
#include <cmath>

ComplexNumber::ComplexNumber(const double real, const double imag)
{
    this->real = real;
    this->imag = imag;
}

double ComplexNumber::getReal() const { return real; }
double ComplexNumber::getImag() const { return imag; }

ComplexNumber ComplexNumber::operator + (const ComplexNumber& other) const
{
    return ComplexNumber(real + other.real, imag + other.imag);
}

ComplexNumber ComplexNumber::operator + (const double value) const
{
    return ComplexNumber(real + value, imag);
}

ComplexNumber operator + (const double value, const ComplexNumber& c)
{
    return ComplexNumber(c.getReal() + value, c.getImag());
}

ComplexNumber ComplexNumber::operator - (const ComplexNumber& other) const
{
    return ComplexNumber(real - other.real, imag - other.imag);
}

ComplexNumber ComplexNumber::operator * (const ComplexNumber& other) const
{
    return ComplexNumber(real * other.real - imag * other.imag, real * other.imag + imag * other.real);
}

ComplexNumber ComplexNumber::operator / (const ComplexNumber& other) const
{
    double denominator = other.real * other.real + other.imag * other.imag;
    if (denominator == 0)
    {
        cerr << "Error: деление на ноль" << endl;
        exit(1);
    }
    return ComplexNumber((real * other.real + imag * other.imag) / denominator,
                         (imag * other.real - real * other.imag) / denominator);
}

bool ComplexNumber::operator == (const ComplexNumber& other) const
{
    return (real == other.real) && (imag == other.imag);
}

bool ComplexNumber::operator != (const ComplexNumber& other) const
{
    return !(*this == other);
}

ComplexNumber ComplexNumber::getConjugate() const
{
    return ComplexNumber(real, -imag);
}

string ComplexNumber::toAlgebraicString() const
{
    string sign = (imag >= 0) ? " + " : " - ";
    return to_string(real) + sign + to_string(abs(imag)) + "i";
}

string ComplexNumber::toTrigonometricString() const
{
    double r = sqrt(real * real + imag * imag);
    double phi = atan2(imag, real);
    return to_string(r) + "(cos(" + to_string(phi) + ") + i*sin(" + to_string(phi) + "))";
}

string ComplexNumber::toExponentialString() const
{
    double r = sqrt(real * real + imag * imag);
    double phi = atan2(imag, real);
    return to_string(r) + " * e^(i*" + to_string(phi) + ")";
}

ostream& operator << (ostream& os, const ComplexNumber& c)
{
    os << c.toAlgebraicString();
    return os;
}

istream& operator >> (istream& is, ComplexNumber& c)
{
    is >> c.real >> c.imag;
    return is;
}
