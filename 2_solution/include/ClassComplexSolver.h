#pragma once

#include "ClassQuadraticEquationSolver.h"
#include "ClassComplexNumber.h"

/**
 * @brief Класс для решения квадратного уравнения в комплексной плоскости
 */
class ComplexSolver : public QuadraticEquationSolver
{
public:
    /**
     * @brief Базовый конструктор
     */
    ComplexSolver(const double a, const double b, const double c);

    /**
     * @brief Виртуальная функция решения
     * Ищет корни в том числе в комплексной плоскости
     */
    void solve() override;
};
