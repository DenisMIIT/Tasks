#define _USE_MATH_DEFINES
#include <gtest/gtest.h>

#include "../include/ClassComplexNumber.h"
#include "../include/ClassSimpleSolver.h"
#include "../include/ClassComplexSolver.h"

#include <cmath>
#include <sstream>

/**
 * @brief Тест базовых операторов ==; !=; класса комплексных чисел
 */
TEST(ComplexNumberTest, Basic_Operators)
{
	ComplexNumber c1(1.0, 2.0);
	ComplexNumber c2(1.0, 2.0);
	ComplexNumber c3(3.0, 4.0);

	ASSERT_TRUE(c1 == c2);
	ASSERT_TRUE(c1 != c3);
}

/**
 * @brief Тест арифметических операций класса комплексных чисел
 */
TEST(ComplexNumberTest, Arithmetic_Operations)
{
	ComplexNumber c1(1.0, 2.0);
	ComplexNumber c2(3.0, 4.0);

	// Тест сложения
	ComplexNumber sum = c1 + c2;
	ASSERT_DOUBLE_EQ(sum.getReal(), 4.0);
	ASSERT_DOUBLE_EQ(sum.getImag(), 6.0);

	// Тест вычитания
	ComplexNumber diff = c2 - c1;
	ASSERT_DOUBLE_EQ(diff.getReal(), 2.0);
	ASSERT_DOUBLE_EQ(diff.getImag(), 2.0);

	// Тест умножения
	ComplexNumber prod = c1 * c2;
	ASSERT_DOUBLE_EQ(prod.getReal(), -5.0);
	ASSERT_DOUBLE_EQ(prod.getImag(), 10.0);
}

/**
 * @brief Тест сопряжения и строковых представлений комплексного числа
 */
TEST(ComplexNumberTest, Conjugate_And_Methods)
{
	ComplexNumber c(3.0, -4.0);
	ComplexNumber conj = c.getConjugate();

	ASSERT_DOUBLE_EQ(conj.getReal(), 3.0);
	ASSERT_DOUBLE_EQ(conj.getImag(), 4.0);
}

/**
 * @brief Тест операторов ввода/вывода для класса комплексного числа
 */
TEST(ComplexNumberTest, IO_Operators)
{
	stringstream input("5.5 -2.5");
	ComplexNumber c;
	input >> c;

	ASSERT_DOUBLE_EQ(c.getReal(), 5.5);
	ASSERT_DOUBLE_EQ(c.getImag(), -2.5);
}

/**
 * @brief Тест валидации входных данных и генерации исключений в SimpleSolver
 */
TEST(SimpleSolverTest, Validation_And_Exceptions)
{
	// Корректное уравнение с вещественными корнями: x^2 - 5x + 4 = 0 (D > 0)
	SimpleSolver validSolver(1, -5, 4);
	ASSERT_NO_THROW(validSolver.solve());

	// Уравнение с комплексными корнями: x^2 + 2x + 5 = 0 (D < 0) -> должно выбросить runtime_error
	SimpleSolver complexRootsSolver(1, 2, 5);
	ASSERT_THROW(complexRootsSolver.solve(), runtime_error);

	// Не квадратное уравнение: 0x^2 + 3x + 2 = 0 (a = 0) -> должно выбросить invalid_argument
	SimpleSolver nonQuadraticSolver(0, 3, 2);
	ASSERT_THROW(nonQuadraticSolver.solve(), invalid_argument);
}

/**
 * @brief Тест стабильности работы комплексного решателя ComplexSolver
 */
TEST(ComplexSolverTest, Execution_Stability)
{
	// Проверка работы без падений при любых дискриминантах
	ComplexSolver solverReal(1, -5, 4);
	ASSERT_NO_THROW(solverReal.solve());

	ComplexSolver solverComplex(1, 2, 5);
	ASSERT_NO_THROW(solverComplex.solve());
}
