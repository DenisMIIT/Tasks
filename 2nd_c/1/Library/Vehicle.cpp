#include "Vehicle.h"

#include <stdexcept>

Vehicle::Vehicle(const std::string& registrationNumber, const std::string& engineNumber,
                 const std::string& brand, const std::string& model,
                 const std::string& color, const Owner& owner)
    : owner_(owner) {
    this->registrationNumber_ = registrationNumber;
    this->engineNumber_ = engineNumber;
    this->brand_ = brand;
    this->model_ = model;
    this->color_ = color;
    this->stolen_ = false;

    if (this->registrationNumber_.empty() || this->engineNumber_.empty() ||
        this->brand_.empty() || this->model_.empty() || this->color_.empty()) {
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

void Vehicle::addPreviousOwner(const Owner& owner) {
    previousOwners_.push_back(owner);
}

void Vehicle::addAccident(const Accident& accident) {
    accidents_.push_back(accident);
}
