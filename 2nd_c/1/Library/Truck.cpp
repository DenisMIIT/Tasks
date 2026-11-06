#include "Truck.h"

#include <stdexcept>

Truck::Truck(const std::string& registrationNumber,
             const std::string& engineNumber, const std::string& brand,
             const std::string& model, const std::string& color,
             const Owner& owner, const int loadKilograms)
    : Vehicle(registrationNumber, engineNumber, brand, model, color, owner) {
    this->loadKilograms_ = loadKilograms;
    if (this->loadKilograms_ < 1) {
        throw std::invalid_argument("Load must be positive");
    }
}

std::string Truck::getType() const {
    return "Truck";
}

std::string Truck::getExtraInfo() const {
    return "max load (kg): " + std::to_string(loadKilograms_);
}
