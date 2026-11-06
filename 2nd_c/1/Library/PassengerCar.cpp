#include "PassengerCar.h"

#include <stdexcept>

PassengerCar::PassengerCar(const std::string& registrationNumber,
                           const std::string& engineNumber, const std::string& brand,
                           const std::string& model, const std::string& color,
                           const Owner& owner, const int seats)
    : Vehicle(registrationNumber, engineNumber, brand, model, color, owner) {
    this->seats_ = seats;
    if (this->seats_ < 1) {
        throw std::invalid_argument("Seat count must be positive");
    }
}

std::string PassengerCar::getType() const {
    return "Passenger car";
}

std::string PassengerCar::getExtraInfo() const {
    return "seats: " + std::to_string(seats_);
}
