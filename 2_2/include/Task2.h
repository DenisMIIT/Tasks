#pragma once

#include "Exercise.h"

namespace miit::algebra
{
    /** @brief Inserts a copy of the first row after each even-numbered original row. */
    class Task2 : public Exercise
    {
    private:
        /** @brief Matrix containing the result of the exercise. */
        Matrix<int> result_;

    public:
        /**
         * @brief Creates the exercise and fills its source matrix.
         * @param matrix Source matrix; must outlive the exercise.
         * @param generator Generator used for the initial values.
         */
        Task2(Matrix<int>& matrix, const Generator& generator);

        /**
         * @brief Inserts a copy of the first row after each even-numbered original row.
         * @return Reference to the result, valid while the exercise lives.
         */
        Matrix<int>& Solve() override;
    };
}
