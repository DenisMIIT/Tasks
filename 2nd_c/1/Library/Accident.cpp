#include "Accident.h"

#include <stdexcept>

Accident::Accident(const Date& date, const std::string& description)
    : date_(date) {
    this->description_ = description;
    if (this->description_.empty()) {
        throw std::invalid_argument("Accident description cannot be empty");
    }
}

Date Accident::getDate() const {
    return date_;
}

std::string Accident::getDescription() const {
    return description_;
}

std::string Accident::toString() const {
    return date_.toString() + ": " + description_;
}
