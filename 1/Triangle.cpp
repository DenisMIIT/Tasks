#include "Triangle.h"
#include <float.h>
#include <cmath>

void Triangle::checkTriangle(const Point A, const Point B, const Point C)
{
    if (A == B || B == C || C == A)
    {
        cerr << "Точки совпадают => не образуют треугольник!";
        exit(1);
    }

    Vector AB(A, B);
    Vector AC(A, C);

    // Проверка на то, лежат ли точки на одной прямой.
    // Если площадь параллелограмма, натянутого на векторы AB и AC, равна 0, то точки коллинеарны.
    // Псевдоскалярное произведение: |AB_x * AC_y - AB_y * AC_x|
    double cross_product = fabs(AB.getX() * AC.getY() - AB.getY() * AC.getX());

    if (cross_product <= DBL_EPSILON)
    {
        cerr << "Точки лежат на одной прямой => не образуют треугольник!";
        exit(1);
    }
}

Triangle::Triangle() : A(0, 10), B(0, 0), C(10, 0)
{
}

Triangle::Triangle(const Point A, const Point B, const Point C)
{
    this->A = A;
    this->B = B;
    this->C = C;

    checkTriangle(A, B, C);
}

Point Triangle::getAltitudePointH() const
{
    // Находим векторы, задающие прямую BC и вектор из B в A
    Vector BC(B, C);
    Vector BA(B, A);

    // Находим проекцию вектора BA на вектор BC.
    // Скалярное произведение BA * BC и скалярный квадрат вектора BC
    double dot_BA_BC = BA * BC;
    double dot_BC_BC = BC * BC;

    // Коэффициент проекции
    double coeff = dot_BA_BC / dot_BC_BC;

    // Координаты точки H получаем прибавлением к точке B масштабированного вектора BC
    double h_x = B.getX() + BC.getX() * coeff;
    double h_y = B.getY() + BC.getY() * coeff;

    return Point(h_x, h_y);
}

double Triangle::getArea() const
{
    // Площадь треугольника S = 1/2 * a * h
    Point H = getAltitudePointH();
    Vector AH(A, H); // Высота
    Vector BC(B, C); // Основание

    return 0.5 * BC.getLen() * AH.getLen();
}
