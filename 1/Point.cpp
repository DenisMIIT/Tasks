#include "Point.h"
#include <float.h>

Point::Point(const double x, const double y)
{
    this->x = x;
    this->y = y;
}

double Point::getX(void) const
{
    return x;
}

double Point::getY(void) const
{
    return y;
}

void Point::operator = (const Point other)
{
    this->x = other.x;
    this->y = other.y;
}

bool Point::operator != (const Point other) const
{
    return !(*this == other);
}

bool Point::operator == (const Point other) const
{
    return (fabs(this->x - other.x) <= DBL_EPSILON && fabs(this->y - other.y) <= DBL_EPSILON);
}
