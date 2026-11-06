#include "Vehicle.h"

#include <stdexcept>
#include <utility>

Vehicle::Vehicle(std::string registrationNumber, std::string engineNumber,
                 std::string brand, std::string model, std::string color,
                 Owner owner)
    : registrationNumber_(std::move(registrationNumber)),
      engineNumber_(std::move(engineNumber)),
      brand_(std::move(brand)),
      model_(std::move(model)),
      color_(std::move(color)),
      owner_(std::move(owner)),
      stolen_(false) {
    if (registrationNumber_.empty() || engineNumber_.empty() ||
        brand_.empty() || model_.empty() || color_.empty()) {
        throw std::invalid_argument("Vehicle fields cannot be empty");
    }
}

Vehicle::~Vehicle() = default;

std::string Vehicle::getInfo() const {
    return getType() + ": " + brand_ + " " + model_ +
           ", registration: " + registrationNumber_ +
           ", engine: " + engineNumber_ +
           ", color: " + color_ + ", " + getExtraInfo();
}

std::string Vehicle::getRegistrationNumber() const {
    return registrationNumber_;
}

std::string Vehicle::getEngineNumber() const {
    return engineNumber_;
}

std::string Vehicle::getBrand() const {
    return brand_;
}

Owner Vehicle::getOwner() const {
    return owner_;
}

std::vector<Owner> Vehicle::getPreviousOwners() const {
    return previousOwners_;
}

std::vector<Accident> Vehicle::getAccidents() const {
    return accidents_;
}

bool Vehicle::isStolen() const {
    return stolen_;
}

void Vehicle::setStolen(const bool stolen) {
    stolen_ = stolen;
}

void Vehicle::addPreviousOwner(Owner owner) {
    previousOwners_.push_back(std::move(owner));
}

void Vehicle::addAccident(Accident accident) {
    accidents_.push_back(std::move(accident));
}
