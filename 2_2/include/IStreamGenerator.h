#pragma once

#include "Generator.h"

#include <iostream>

namespace miit::algebra
{
    /**
     * @brief Reads integers from an input stream.
     */
    class IStreamGenerator : public Generator
    {
    private:
        /**
         * @brief Non-owning reference to the input stream.
         */
        std::istream& input_;

    public:
        /**
         * @brief Sets the stream used to read integers.
         * @param input Input stream.
         */
        explicit IStreamGenerator(std::istream& input = std::cin);

        /**
         * @brief Reads one integer from the stream.
         * @return Integer entered by the user.
         */
        int generate() const override;
    };
}
