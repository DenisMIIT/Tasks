#include "Owner.h"

#include <stdexcept>

Owner::Owner(const std::string& fullName, const std::string& address) {
    this->fullName_ = fullName;
    this->address_ = address;

    if (this->fullName_.empty() || this->address_.empty()) {
        throw std::invalid_argument("Owner fields cannot be empty");
    }
}

std::string Owner::getFullName() const {
    return fullName_;
}

std::string Owner::getAddress() const {
    return address_;
}

std::string Owner::toString() const {
    return fullName_ + ", " + address_;
}
