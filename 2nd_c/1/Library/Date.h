#pragma once

#include <string>

/**
 * @brief Stores a valid calendar date.
 */
class Date {
public:
    /**
     * @brief Creates a date and checks its values.
     * @param year Year of the date.
     * @param month Month from 1 to 12.
     * @param day Day of the month.
     */
    Date(const int year, const int month, const int day);

    /**
     * @brief Compares two dates.
     * @param other Date to compare with.
     * @return True if this date is earlier.
     */
    bool operator<(const Date& other) const;

    /**
     * @brief Checks if this date is not later than another date.
     * @param other Date to compare with.
     * @return True if this date is earlier or equal.
     */
    bool operator<=(const Date& other) const;

    /**
     * @brief Returns the date as YYYY-MM-DD.
     * @return Text with the date.
     */
    std::string toString() const;

private:
    /**
     * @brief Checks if a year is a leap year.
     * @param year Year to check.
     * @return True for a leap year.
     */
    static bool isLeapYear(const int year);

    int year_;
    int month_;
    int day_;
};
