#include "Date.h"

#include <stdexcept>
#include <tuple>

Date::Date(const int year, const int month, const int day)
    : year_(year), month_(month), day_(day) {
    if (year < 1 || month < 1 || month > 12) {
        throw std::invalid_argument("Invalid year or month");
    }

    int daysInMonth = 31;
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        daysInMonth = 30;
    } else if (month == 2) {
        daysInMonth = isLeapYear(year) ? 29 : 28;
    }

    if (day < 1 || day > daysInMonth) {
        throw std::invalid_argument("Invalid day");
    }
}

bool Date::operator<(const Date& other) const {
    return std::tie(year_, month_, day_) <
           std::tie(other.year_, other.month_, other.day_);
}

bool Date::operator<=(const Date& other) const {
    return !(other < *this);
}

std::string Date::toString() const {
    const std::string monthText = (month_ < 10 ? "0" : "") + std::to_string(month_);
    const std::string dayText = (day_ < 10 ? "0" : "") + std::to_string(day_);
    return std::to_string(year_) + "-" + monthText + "-" + dayText;
}

bool Date::isLeapYear(const int year) {
    return year % 4 == 0;
}
