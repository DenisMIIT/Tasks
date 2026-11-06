#include "PassengerCar.h"

#include <stdexcept>
#include <utility>

PassengerCar::PassengerCar(std::string registrationNumber,
                           std::string engineNumber, std::string brand,
                           std::string model, std::string color,
                           Owner owner, const int seats)
    : Vehicle(std::move(registrationNumber), std::move(engineNumber),
              std::move(brand), std::move(model), std::move(color),
              std::move(owner)),
      seats_(seats) {
    if (seats_ < 1) {
        throw std::invalid_argument("Seat count must be positive");
    }
}

std::string PassengerCar::getType() const {
    return "Passenger car";
}

std::string PassengerCar::getExtraInfo() const {
    return "seats: " + std::to_string(seats_);
}
