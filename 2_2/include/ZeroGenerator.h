#pragma once

#include "Generator.h"

namespace miit::algebra
{
    /**
     * @brief Generates only zero values.
     */
    class ZeroGenerator : public Generator
    {
    public:
        /**
         * @brief Returns zero.
         * @return Zero.
         */
        int generate() const override;
    };
}
