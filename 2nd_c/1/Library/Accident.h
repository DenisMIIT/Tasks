#pragma once

#include "Date.h"

#include <string>

/**
 * @brief Stores the date and details of a road accident.
 */
class Accident {
public:
    /**
     * @brief Creates an accident record.
     * @param date Date of the accident.
     * @param description Short text about the accident.
     */
    Accident(Date date, std::string description);

    /**
     * @brief Returns the accident date.
     * @return Date of the accident.
     */
    Date getDate() const;

    /**
     * @brief Returns the accident text.
     * @return Accident description.
     */
    std::string getDescription() const;

    /**
     * @brief Makes text about the accident.
     * @return Date and description.
     */
    std::string toString() const;

private:
    Date date_;
    std::string description_;
};
