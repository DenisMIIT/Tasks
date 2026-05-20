#include "../include/ClassComplexSolver.h"
#include <cmath>

ComplexSolver::ComplexSolver(const double a, const double b, const double c)
: QuadraticEquationSolver(a, b, c) {}

void ComplexSolver::solve()
{
    if (a == 0)
    {
        cerr << "Error: уравнение не является квадратным" << endl;
        exit(1);
    }

    double discriminant = b * b - 4 * a * c;

    cout << "Complex Solver обнаружил корни:" << endl;

    if (discriminant >= 0)
    {
        double x1 = (-b + sqrt(discriminant)) / (2 * a);
        double x2 = (-b - sqrt(discriminant)) / (2 * a);

        ComplexNumber root1(x1, 0);
        ComplexNumber root2(x2, 0);

        cout << "x1 = " << root1 << endl;
        cout << "x2 = " << root2 << endl;
    }
    else
    {
        double realPart = -b / (2 * a);
        double imagPart = sqrt(-discriminant) / (2 * a);

        ComplexNumber root1(realPart, imagPart);
        ComplexNumber root2 = root1.getConjugate();

        cout << "x1 = " << root1.toAlgebraicString() << endl;
        cout << "x2 = " << root2.toAlgebraicString() << endl;

        cout << "Экспоненциальная форма первого корня: " << root1.toExponentialString() << endl;
    }
}
