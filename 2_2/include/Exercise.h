#pragma once

#include "Generator.h"
#include "Matrix.h"

namespace miit::algebra
{
    /** @brief Base class for exercises performed on a matrix. */
    class Exercise
    {
    protected:
        /** @brief Non-owning reference to the caller's matrix. */
        Matrix<int>& source_;

    public:
        /**
         * @brief Fills the supplied matrix when creating the exercise.
         * @param matrix Source matrix; must outlive the exercise.
         * @param generator Generator used during construction only.
         */
        Exercise(Matrix<int>& matrix, const Generator& generator);

        /** @brief Destroys the exercise without destroying its source matrix. */
        virtual ~Exercise() = default;

        /**
         * @brief Solves the exercise using the original source matrix.
         * @return Reference to the result owned by the exercise.
         */
        virtual Matrix<int>& Solve() = 0;
    };
}
