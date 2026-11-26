#pragma once

#include "Generator.h"

#include <random>

namespace miit::algebra
{
    /**
     * @brief Generates random integers in a given range.
     */
    class RandomGenerator : public Generator
    {
    private:
        /**
         * @brief Pseudo-random number engine.
         */
        mutable std::mt19937 engine_;
        /**
         * @brief Uniform integer distribution.
         */
        mutable std::uniform_int_distribution<int> distribution_;

    public:
        /**
         * @brief Creates a random number generator.
         * @param minimum Smallest possible number.
         * @param maximum Largest possible number.
         */
        RandomGenerator(const int minimum, const int maximum);

        /**
         * @brief Gets a random number.
         * @return Generated integer.
         */
        int generate() const override;
    };
}
