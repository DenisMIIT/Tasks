#include <cstddef>
#include <exception>
#include <iostream>
#include <stdexcept>
#include "../include/Matrix.h"
#include "../include/ConstantGenerator.h"
#include "../include/IStreamGenerator.h"
#include "../include/RandomGenerator.h"
#include "../include/Task1.h"
#include "../include/Task2.h"
#include "../include/ZeroGenerator.h"

using namespace miit::algebra;

/** @brief Available matrix filling modes. */
enum FillMode
{
    RANDOM_FILL = 1,
    KEYBOARD_FILL,
    ZERO_FILL,
    CONSTANT_FILL
};

/** @brief Available Variant 1 exercises. */
enum TaskNumber
{
    CHANGE_SIGNS = 1,
    INSERT_FIRST_ROW
};

/** @brief Reads an integer after validating the prompt pointer. */
int readInteger(const char* message);

/** @brief Reads a strictly positive matrix dimension. */
std::size_t readPositiveSize(const char* message);

/**
 * @brief Reads the task selection and executes it with the supplied generator.
 * @param rows Number of rows.
 * @param columns Number of columns.
 * @param generator Generator used for the source matrix.
 * @param keyboardFill Whether to display the element input prompt.
 */
void executeTask(const std::size_t rows, const std::size_t columns,
    const Generator& generator, const bool keyboardFill = false);

/** @brief Prints the source and the result of the selected exercise. */
void printResult(const Matrix<int>& matrix, Exercise& exercise);

/** @return Zero on success, one on error. */
int main()
{
    try
    {
        std::cout << "Enter row count and column count: ";
        const std::size_t rows = readPositiveSize("");
        const std::size_t columns = readPositiveSize("");

        switch (readInteger("Fill: 1 - random, 2 - keyboard, 3 - zeros, 4 - constant: "))
        {
        case RANDOM_FILL:
        {
            const RandomGenerator generator(-10, 10);
            executeTask(rows, columns, generator);
            break;
        }
        case KEYBOARD_FILL:
        {
            const IStreamGenerator generator(std::cin);
            executeTask(rows, columns, generator, true);
            break;
        }
        case ZERO_FILL:
        {
            const ZeroGenerator generator;
            executeTask(rows, columns, generator);
            break;
        }
        case CONSTANT_FILL:
        {
            const ConstantGenerator generator(readInteger("Enter the constant value: "));
            executeTask(rows, columns, generator);
            break;
        }
        default:
            throw std::invalid_argument("Unknown fill mode");
        }
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
    return 0;
}

int readInteger(const char* message)
{
    if (message == nullptr)
    {
        throw std::invalid_argument("Input prompt must not be null");
    }
    std::cout << message;
    int value = 0;
    if (!(std::cin >> value))
    {
        throw std::invalid_argument("An integer is required");
    }
    return value;
}

std::size_t readPositiveSize(const char* message)
{
    if (message == nullptr)
    {
        throw std::invalid_argument("Input prompt must not be null");
    }
    const int value = readInteger(message);
    if (value <= 0)
    {
        throw std::invalid_argument("Matrix size must be positive");
    }
    return static_cast<std::size_t>(value);
}

void executeTask(const std::size_t rows, const std::size_t columns,
    const Generator& generator, const bool keyboardFill)
{
    const int taskNumber = readInteger("Task: 1 - change signs, 2 - insert first row: ");
    if (taskNumber != CHANGE_SIGNS && taskNumber != INSERT_FIRST_ROW)
    {
        throw std::invalid_argument("Unknown task number");
    }

    Matrix<int> matrix(rows, columns);
    if (keyboardFill)
    {
        std::cout << "Enter " << rows * columns << " integers: ";
    }

    switch (taskNumber)
    {
    case CHANGE_SIGNS:
    {
        Task1 task(matrix, generator);
        printResult(matrix, task);
        break;
    }
    case INSERT_FIRST_ROW:
    {
        Task2 task(matrix, generator);
        printResult(matrix, task);
        break;
    }
    }
}

void printResult(const Matrix<int>& matrix, Exercise& exercise)
{
    std::cout << "\nBefore:\n" << matrix << '\n';
    std::cout << "\nAfter:\n" << exercise.Solve() << '\n';
}
