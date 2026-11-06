#pragma once

#include "Vehicle.h"

#include <string>

/**
 * @brief Stores a truck and its load capacity.
 */
class Truck final : public Vehicle {
public:
    /**
     * @brief Creates a truck.
     * @param registrationNumber Registration number.
     * @param engineNumber Engine number.
     * @param brand Truck brand.
     * @param model Truck model.
     * @param color Truck color.
     * @param owner Current truck owner.
     * @param loadKilograms Maximum load in kilograms.
     */
    Truck(std::string registrationNumber, std::string engineNumber,
          std::string brand, std::string model, std::string color,
          Owner owner, const int loadKilograms);

    /**
     * @brief Returns the vehicle type.
     * @return Truck type name.
     */
    std::string getType() const override;

    /**
     * @brief Returns the load capacity as text.
     * @return Load in kilograms.
     */
    std::string getExtraInfo() const override;

private:
    int loadKilograms_;
};
