#include "../include/IStreamGenerator.h"

#include <istream>
#include <stdexcept>

namespace miit::algebra
{
    IStreamGenerator::IStreamGenerator(std::istream& input)
        : input_(input)
    {
    }

    int IStreamGenerator::generate() const
    {
        int value = 0;
        if (!(input_ >> value))
        {
            throw std::runtime_error("Cannot read an integer");
        }
        return value;
    }
}
