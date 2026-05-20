#pragma once
#include <iostream>

using namespace std;

/**
 * @brief Абстрактный базовый класс "Решение квадратного уравнения"
 */
class QuadraticEquationSolver
{
protected:
    /**
     * @param a - коэффициент a
     */
    double a;

    /**
     * @param b - коэффициент b
     */
    double b;

    /**
     * @param c - свободный коэффициент c
     */
    double c;

public:
    /**
     * @brief Базовый конструктор
     * @param a - коэффициент a
     * @param b - коэффициент b
     * @param c - коэффициент c
     */
    QuadraticEquationSolver(const double a, const double b, const double c);

    /**
     * @brief Виртуальная функция решения уравнения
     */
    virtual void solve() = 0;

    /**
     * @brief Виртуальный деструктор по-умолчанию
     */
    virtual ~QuadraticEquationSolver() = default;
};
