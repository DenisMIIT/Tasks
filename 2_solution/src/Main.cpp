#include <iostream>
#include "../include/ClassSimpleSolver.h"
#include "../include/ClassComplexSolver.h"

using namespace std;

/**
 * @brief Точка входа в программу
 * @return Если программа выполнена корректно - 0, иначе 1
 */
int main()
{
    system("chcp 1251");
    system("CLS");

    cout << "--- Тест SimpleSolver ---" << endl;
    SimpleSolver simpleSolver(1, -5, 4); // x^2 - 5x + 4 = 0
    try
    {
        simpleSolver.solve();
    }
    catch (const exception& e)
    {
        cerr << e.what() << endl;
    }

    cout << "\n--- Тест ComplexSolver ---" << endl;
    ComplexSolver complexSolver(1, 2, 5); // x^2 + 2x + 5 = 0
    complexSolver.solve();

    return 0;
}
