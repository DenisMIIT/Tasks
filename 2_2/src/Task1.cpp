#include <cstdint>
#include <limits>
#include <stdexcept>
#include "../include/Task1.h"

namespace miit::algebra
{
    Task1::Task1(Matrix<int>& matrix, const Generator& generator)
        : Exercise(matrix, generator)
    {
    }

    Matrix<int>& Task1::Solve()
    {
        result_ = source_;
        if (result_.empty())
        {
            return result_;
        }

        for (std::size_t row = 0U; row < result_.rowsCount(); ++row)
        {
            std::size_t largestColumn = 0U;
            std::int64_t largestAbsolute = -1;
            for (std::size_t column = 0U; column < result_.columnsCount(); ++column)
            {
                const std::int64_t value = result_[row][column];
                const std::int64_t absoluteValue = value < 0 ? -value : value;
                if (absoluteValue > largestAbsolute)
                {
                    largestAbsolute = absoluteValue;
                    largestColumn = column;
                }
            }

            const int element = result_[row][largestColumn];
            if (element == std::numeric_limits<int>::min())
            {
                throw std::overflow_error("Cannot change the sign of the smallest int");
            }
            result_[row][largestColumn] = -element;
        }
        return result_;
    }
}
