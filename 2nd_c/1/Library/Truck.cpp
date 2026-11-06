#include "Truck.h"

#include <stdexcept>
#include <utility>

Truck::Truck(std::string registrationNumber, std::string engineNumber,
             std::string brand, std::string model, std::string color,
             Owner owner, const int loadKilograms)
    : Vehicle(std::move(registrationNumber), std::move(engineNumber),
              std::move(brand), std::move(model), std::move(color),
              std::move(owner)),
      loadKilograms_(loadKilograms) {
    if (loadKilograms_ < 1) {
        throw std::invalid_argument("Load must be positive");
    }
}

std::string Truck::getType() const {
    return "Truck";
}

std::string Truck::getExtraInfo() const {
    return "max load (kg): " + std::to_string(loadKilograms_);
}
