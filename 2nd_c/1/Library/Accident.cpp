#include "Accident.h"

#include <stdexcept>
#include <utility>

Accident::Accident(Date date, std::string description)
    : date_(std::move(date)), description_(std::move(description)) {
    if (description_.empty()) {
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
