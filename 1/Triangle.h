#pragma once
#include <iostream>
#include "Vector.h"

using namespace std;

/**
 * @brief Класс треугольника
 */
class Triangle
{
private:
    /**
     * @param A - первая точка (вершина, из которой опускается высота AH)
     */
    Point A;

    /**
     * @param B - вторая точка
     */
    Point B;

    /**
     * @param C - третья точка
     */
    Point C;

    /**
     * @brief Функция проверки, образуют ли точки треугольник (точки не должны лежать на одной прямой)
     * @param A - первая точка
     * @param B - вторая точка
     * @param C - третья точка
     */
    void checkTriangle(const Point A, const Point B, const Point C);

public:
    /**
     * @brief Конструктор по-умолчанию, задаёт точки как: A(0,10), B(0,0), C(10,0)
     */
    Triangle();

    /**
     * @brief Конструктор, задающий координаты точек как переданные значения
     * @param A - значение первой точки
     * @param B - значение второй точки
     * @param C - значение третьей точки
     */
    Triangle(const Point A, const Point B, const Point C);

    /**
     * @brief Рассчитывает координаты точки H (основания высоты AH, опущенной на сторону BC)
     * @return Точку H
     */
    Point getAltitudePointH() const;

    /**
     * @brief Рассчитывает площадь треугольника
     * @return Рассчитанное значение площади
     */
    double getArea() const;
};
