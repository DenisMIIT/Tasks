#include "../include/ClassSimpleSolver.h"
#include <cmath>
#include <stdexcept>

SimpleSolver::SimpleSolver(const double a, const double b, const double c)
: QuadraticEquationSolver(a, b, c) {}

void SimpleSolver::solve()
{
    if (a == 0)
    {
        throw invalid_argument("Ошибка: уравнение не является квадратным (a = 0)");
    }

    double discriminant = b * b - 4 * a * c;

    if (discriminant <= 0)
    {
        throw runtime_error("Ошибка: дискриминант неположительный. Вещественных корней нет.");
    }

    double x1 = (-b + sqrt(discriminant)) / (2 * a);
    double x2 = (-b - sqrt(discriminant)) / (2 * a);

    cout << "Simple Solver обнаружил корни:" << endl;
    cout << "x1 = " << x1 << endl;
    cout << "x2 = " << x2 << endl;
}
