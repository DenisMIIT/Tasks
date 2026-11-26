#include <gtest/gtest.h>

#include <limits>
#include <sstream>
#include <stdexcept>
#include <utility>
#include "ConstantGenerator.h"
#include "IStreamGenerator.h"
#include "Matrix.h"
#include "RandomGenerator.h"
#include "Task1.h"
#include "Task2.h"
#include "ZeroGenerator.h"

using namespace miit::algebra;

namespace
{
    /** @brief Constructs a matrix from a whitespace-separated sequence. */
    Matrix<int> makeMatrix(const std::size_t rows, const std::size_t columns, const char* values)
    {
        if (values == nullptr)
        {
            throw std::invalid_argument("Matrix values must not be null");
        }
        Matrix<int> matrix(rows, columns);
        std::istringstream input(values);
        if (!(input >> matrix))
        {
            throw std::invalid_argument("Invalid matrix values");
        }
        return matrix;
    }
}

TEST(MatrixConstruction, StoresElementsAndMakesText)
{
    Matrix<int> matrix(2U, 3U, 4);
    matrix.at(1U, 0U) = -5;
    matrix[0U][1U] = 7;
    EXPECT_EQ(matrix.rowsCount(), 2U);
    EXPECT_EQ(matrix.columnsCount(), 3U);
    EXPECT_EQ(matrix.toString(), "4 7 4\n-5 4 4");
    EXPECT_EQ(matrix.flatAt(1U), 7);
}

TEST(MatrixConstruction, DefaultAndInvalidDimensions)
{
    const Matrix<int> matrix;
    EXPECT_TRUE(matrix.empty());
    EXPECT_EQ(matrix.rowsCount(), 0U);
    EXPECT_EQ(matrix.columnsCount(), 0U);
    EXPECT_THROW((Matrix<int>(0U, 2U)), std::invalid_argument);
    EXPECT_THROW((Matrix<int>(2U, 0U)), std::invalid_argument);
}

TEST(MatrixValueSemantics, CopiesAndMovesValues)
{
    Matrix<int> first(2U, 2U, 3);
    Matrix<int> copy(first);
    copy[0U][0U] = 8;
    EXPECT_EQ(first[0U][0U], 3);
    Matrix<int> assigned;
    assigned = copy;
    EXPECT_EQ(assigned, copy);
    Matrix<int> moved(std::move(assigned));
    EXPECT_EQ(moved, copy);
    EXPECT_EQ(moved.rowsCount(), 2U);
    EXPECT_TRUE(assigned.empty());
    EXPECT_EQ(assigned.columnsCount(), 0U);
    Matrix<int> movedAgain;
    movedAgain = std::move(moved);
    EXPECT_EQ(movedAgain, copy);
    EXPECT_EQ(moved.rowsCount(), 0U);
    EXPECT_EQ(moved.columnsCount(), 0U);
}

TEST(MatrixAccess, RejectsInvalidIndices)
{
    Matrix<int> matrix(2U, 2U);
    const Matrix<int>& constant = matrix;
    EXPECT_THROW(matrix.at(2U, 0U), std::out_of_range);
    EXPECT_THROW(matrix.at(0U, 2U), std::out_of_range);
    EXPECT_THROW(matrix.flatAt(4U), std::out_of_range);
    EXPECT_THROW(matrix[2U], std::out_of_range);
    EXPECT_THROW(constant[2U], std::out_of_range);
    EXPECT_THROW(Matrix<int>().flatAt(0U), std::out_of_range);
}

TEST(MatrixAccess, ReadsConstElements)
{
    const Matrix<int> matrix(1U, 2U, 5);
    EXPECT_EQ(matrix.at(0U, 0U), 5);
    EXPECT_EQ(matrix[0U][1U], 5);
    EXPECT_EQ(matrix.flatAt(1U), 5);
}

TEST(MatrixShifts, ShiftsRowsLeftAndRight)
{
    const Matrix<int> matrix = makeMatrix(2U, 3U, "1 2 3 4 5 6");
    EXPECT_EQ((matrix << 1U).toString(), "2 3 0\n5 6 0");
    EXPECT_EQ((matrix >> 1U).toString(), "0 1 2\n0 4 5");
    EXPECT_EQ((matrix << 3U).toString(), "0 0 0\n0 0 0");
    EXPECT_EQ((matrix >> 4U).toString(), "0 0 0\n0 0 0");
    EXPECT_EQ(matrix << 0U, matrix);
    EXPECT_EQ(matrix >> 0U, matrix);
}

TEST(Generators, GeneratesZerosAndConstants)
{
    const ZeroGenerator zero;
    const ConstantGenerator constant(-7);
    EXPECT_EQ(zero.generate(), 0);
    EXPECT_EQ(constant.generate(), -7);
}

TEST(Generators, GeneratesNumbersWithinRange)
{
    const RandomGenerator random(-2, 2);
    for (std::size_t count = 0U; count < 50U; ++count)
    {
        const int value = random.generate();
        EXPECT_GE(value, -2);
        EXPECT_LE(value, 2);
    }
    EXPECT_THROW((RandomGenerator(5, 1)), std::invalid_argument);
}

TEST(Generators, ReadsValuesFromStream)
{
    std::istringstream input("5 -6");
    const IStreamGenerator generator(input);
    EXPECT_EQ(generator.generate(), 5);
    EXPECT_EQ(generator.generate(), -6);
    EXPECT_THROW(generator.generate(), std::runtime_error);
}

TEST(MatrixFill, UsesGeneratorPolymorphically)
{
    Matrix<int> matrix(2U, 2U);
    const ConstantGenerator generator(6);
    const Generator& base = generator;
    matrix.fill(base);
    EXPECT_EQ(matrix, Matrix<int>(2U, 2U, 6));
}

TEST(MatrixStreams, ReadsAndWritesMatrices)
{
    Matrix<int> matrix(1U, 2U, 5);
    std::istringstream input("10 -20");
    input >> matrix;
    EXPECT_EQ(matrix.toString(), "10 -20");
    std::ostringstream output;
    output << matrix;
    EXPECT_EQ(output.str(), "10 -20");
}

TEST(MatrixStreams, InvalidReadDoesNotChangeValues)
{
    Matrix<int> matrix(1U, 2U, 9);
    std::istringstream input("3 bad");
    input >> matrix;
    EXPECT_TRUE(input.fail());
    EXPECT_EQ(matrix.toString(), "9 9");
}

TEST(Exercise, ConstructorFillsSourceMatrix)
{
    Matrix<int> matrix(1U, 3U);
    const ConstantGenerator generator(9);
    Task1 task(matrix, generator);
    EXPECT_EQ(matrix.toString(), "9 9 9");
}

TEST(Task1, ChangesSignOfLargestAbsoluteValue)
{
    Matrix<int> matrix(2U, 3U);
    std::istringstream input("1 -9 3 -4 2 1");
    const IStreamGenerator generator(input);
    Task1 task(matrix, generator);
    EXPECT_EQ(task.Solve().toString(), "1 9 3\n4 2 1");
}

TEST(Task1, UsesFirstElementInATie)
{
    Matrix<int> matrix(2U, 3U);
    std::istringstream input("5 5 5 -5 5 2");
    const IStreamGenerator generator(input);
    Task1 task(matrix, generator);
    EXPECT_EQ(task.Solve().toString(), "-5 5 5\n5 5 2");
}

TEST(Task1, DoesNotOverflowForSmallestInt)
{
    Matrix<int> matrix(1U, 2U);
    const ZeroGenerator generator;
    Task1 task(matrix, generator);
    matrix[0U][0U] = std::numeric_limits<int>::min();
    matrix[0U][1U] = 1;
    EXPECT_THROW(task.Solve(), std::overflow_error);
}

TEST(Task1, PreservesSourceAndRepeatsResult)
{
    Matrix<int> matrix(1U, 2U);
    const ConstantGenerator generator(8);
    Task1 task(matrix, generator);
    const Matrix<int> first = task.Solve();
    EXPECT_EQ(matrix.toString(), "8 8");
    EXPECT_EQ(task.Solve(), first);
    Matrix<int> copy = task.Solve();
    copy[0U][0U] = 100;
    EXPECT_EQ(task.Solve(), first);
}

TEST(Task2, InsertsFirstRowAfterEvenRows)
{
    Matrix<int> matrix(4U, 2U);
    std::istringstream input("1 2 3 4 5 6 7 8");
    const IStreamGenerator generator(input);
    Task2 task(matrix, generator);
    EXPECT_EQ(task.Solve().rowsCount(), 6U);
    EXPECT_EQ(task.Solve().toString(), "1 2\n3 4\n1 2\n5 6\n7 8\n1 2");
}

TEST(Task2, HandlesOddAndSingleRowMatrices)
{
    Matrix<int> odd(3U, 1U);
    std::istringstream input("1 2 3");
    const IStreamGenerator generator(input);
    Task2 oddTask(odd, generator);
    EXPECT_EQ(oddTask.Solve().toString(), "1\n2\n1\n3");
    Matrix<int> single(1U, 2U);
    const ConstantGenerator constant(4);
    Task2 singleTask(single, constant);
    EXPECT_EQ(singleTask.Solve().toString(), "4 4");
}

TEST(Task2, PreservesSourceAndRepeatsResult)
{
    Matrix<int> matrix(2U, 2U);
    std::istringstream input("1 2 3 4");
    const IStreamGenerator generator(input);
    Task2 task(matrix, generator);
    const Matrix<int> original(matrix);
    const Matrix<int> first = task.Solve();
    EXPECT_EQ(matrix, original);
    EXPECT_EQ(task.Solve(), first);
}

TEST(Exercise, SupportsEmptyMatrices)
{
    Matrix<int> first;
    Matrix<int> second;
    const ZeroGenerator generator;
    Task1 task1(first, generator);
    Task2 task2(second, generator);
    EXPECT_TRUE(task1.Solve().empty());
    EXPECT_TRUE(task2.Solve().empty());
}
