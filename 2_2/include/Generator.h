#pragma once

namespace miit::algebra
{
    /**
     * @brief Gives the next integer for a matrix.
     */
    class Generator
    {
    public:
        /**
         * @brief Destroys a generator through its base class.
         */
        virtual ~Generator() = default;

        /**
         * @brief Gets the next integer.
         * @return Generated value.
         */
        virtual int generate() const = 0;
    };
}
