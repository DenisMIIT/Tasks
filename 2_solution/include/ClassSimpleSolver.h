#pragma once

#include "ClassQuadraticEquationSolver.h"

/**
 * @brief Класс для поиска только действительных корней квадратного уравнения
 */
class SimpleSolver : public QuadraticEquationSolver
{
public:
    /**
     * @brief Базовый конструктор
     */
    SimpleSolver(const double a, const double b, const double c);

    /**
     * @brief Виртуальная функция решения
     * Находит решение, если дискриминант больше нуля, в противном случае выбрасывает исключение.
     */
    void solve() override;
};
