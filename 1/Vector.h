#pragma once
#include "Point.h"

/**
 * @brief Класс вектора
 */
class Vector
{
private:
    /**
     * @param x - координата вектора по оси x
     */
    double x;

    /**
     * @param y - координата вектора по оси y
     */
    double y;

public:
    /**
     * @brief Конструктор, задающий вектор по двум координатам
     */
    Vector(const double x, const double y);

    /**
     * @brief Конструктор, задающий вектор по двум точкам (вектор переносится в начало координат)
     */
    Vector(const Point A, const Point B);

    /**
     * @brief Выводит значение вектора по оси x
     * @return Значение вектора по оси x
     */
    double getX(void) const;

    /**
     * @brief Выводит значение вектора по оси y
     * @return Значение вектора по оси y
     */
    double getY(void) const;

    /**
     * @brief Рассчитывает длину вектора
     * @return Длину вектора
     */
    double getLen() const;

    /**
     * @brief Рассматривает угол между двумя векторами
     * @return Если угол равен 90-градусам, возвращает единицу, иначе - ноль
     */
    bool getAngle(const Vector second) const;

    /**
     * @brief Оператор скалярного произведения векторов
     * @return Число, результат произведения
     */
    double operator * (const Vector other) const;
};
