#pragma once

#include "Exercise.h"

namespace miit::algebra
{
    /** @brief Changes the sign of the first element with the largest absolute value in each row. */
    class Task1 : public Exercise
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
        Task1(Matrix<int>& matrix, const Generator& generator);

        /**
         * @brief Changes the sign of the first element with the largest absolute value in each row.
         * @return Reference to the result, valid while the exercise lives.
         */
        Matrix<int>& Solve() override;
    };
}
