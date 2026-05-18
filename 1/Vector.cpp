#include "Vector.h"
#include <float.h>
#include <iostream>

Vector::Vector(const Point A, const Point B)
{
    this->x = B.getX() - A.getX();
    this->y = B.getY() - A.getY();
}

Vector::Vector(const double x, const double y)
{
    this->x = x;
    this->y = y;
}

double Vector::getX(void) const
{
    return x;
}

double Vector::getY(void) const
{
    return y;
}

double Vector::getLen() const
{
    return sqrt(pow(x, 2) + pow(y, 2));
}

bool Vector::getAngle(const Vector second) const
{
    Vector first(x, y);
    return (fabs(first * second) <= DBL_EPSILON);
}

double Vector::operator * (const Vector other) const
{
    return (x * other.x + y * other.y);
}
