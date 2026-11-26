#include <limits>
#include <stdexcept>
#include "../include/Task2.h"

namespace miit::algebra
{
    Task2::Task2(Matrix<int>& matrix, const Generator& generator)
        : Exercise(matrix, generator)
    {
    }

    Matrix<int>& Task2::Solve()
    {
        if (source_.empty())
        {
            result_ = source_;
            return result_;
        }

        const std::size_t rows = source_.rowsCount();
        const std::size_t columns = source_.columnsCount();
        const std::size_t extraRows = rows / 2U;
        if (rows > std::numeric_limits<std::size_t>::max() - extraRows)
        {
            throw std::length_error("Too many matrix rows");
        }

        result_ = Matrix<int>(rows + extraRows, columns);
        std::size_t resultRow = 0U;
        for (std::size_t row = 0U; row < rows; ++row)
        {
            for (std::size_t column = 0U; column < columns; ++column)
            {
                result_[resultRow][column] = source_[row][column];
            }
            ++resultRow;

            if (row % 2U == 1U)
            {
                for (std::size_t column = 0U; column < columns; ++column)
                {
                    result_[resultRow][column] = source_[0U][column];
                }
                ++resultRow;
            }
        }
        return result_;
    }
}
