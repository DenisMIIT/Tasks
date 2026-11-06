#pragma once

#include "Vehicle.h"

#include <string>

/**
 * @brief Stores a passenger car and its seat count.
 */
class PassengerCar final : public Vehicle {
public:
    /**
     * @brief Creates a passenger car.
     * @param registrationNumber Registration number.
     * @param engineNumber Engine number.
     * @param brand Car brand.
     * @param model Car model.
     * @param color Car color.
     * @param owner Current car owner.
     * @param seats Number of seats.
     */
    PassengerCar(const std::string& registrationNumber, const std::string& engineNumber,
                 const std::string& brand, const std::string& model,
                 const std::string& color, const Owner& owner, const int seats);

    /**
     * @brief Returns the vehicle type.
     * @return Passenger car type name.
     */
    std::string getType() const override;

    /**
     * @brief Returns information about the seats.
     * @return Number of seats as text.
     */
    std::string getExtraInfo() const override;

private:
    int seats_;
};
