#pragma once

#include "Generator.h"

namespace miit::algebra
{
    /**
     * @brief Generates the same integer every time.
     */
    class ConstantGenerator : public Generator
    {
    private:
        /**
         * @brief Stored constant value.
         */
        int value_;

    public:
        /**
         * @brief Sets the integer to generate.
         * @param value Value for every element.
         */
        explicit ConstantGenerator(const int value);

        /**
         * @brief Returns the stored integer.
         * @return Constant value.
         */
        int generate() const override;
    };
}
