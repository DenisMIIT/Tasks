#include "Owner.h"

#include <stdexcept>
#include <utility>

Owner::Owner(std::string fullName, std::string address)
    : fullName_(std::move(fullName)), address_(std::move(address)) {
    if (fullName_.empty() || address_.empty()) {
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
