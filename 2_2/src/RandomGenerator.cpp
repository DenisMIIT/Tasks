#include "../include/RandomGenerator.h"

#include <stdexcept>

namespace miit::algebra
{
    RandomGenerator::RandomGenerator(const int minimum, const int maximum)
        : engine_(std::random_device{}())
    {
        if (minimum > maximum)
        {
            throw std::invalid_argument("Minimum is greater than maximum");
        }
        distribution_ = std::uniform_int_distribution<int>(minimum, maximum);
    }

    int RandomGenerator::generate() const
    {
        return distribution_(engine_);
    }
}
