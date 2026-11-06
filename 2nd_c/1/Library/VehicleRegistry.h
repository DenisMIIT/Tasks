#pragma once

#include "Date.h"
#include "Vehicle.h"

#include <cstddef>
#include <functional>
#include <string>
#include <utility>
#include <vector>

/**
 * @brief Searches vehicles without owning them.
 */
class VehicleRegistry {
public:
    /**
     * @brief Adds a vehicle with a unique registration and engine number.
     * @param vehicle Vehicle to add. It must outlive the registry.
     */
    void addVehicle(const Vehicle& vehicle);

    /**
     * @brief Finds a vehicle by its registration number.
     * @param registrationNumber Registration number to find.
     * @return Vehicle in the registry. The registry must still exist.
     */
    const Vehicle& findByRegistration(const std::string& registrationNumber) const;

    /**
     * @brief Finds a vehicle by its engine number.
     * @param engineNumber Engine number to find.
     * @return Vehicle in the registry. The registry must still exist.
     */
    const Vehicle& findByEngine(const std::string& engineNumber) const;

    /**
     * @brief Finds the current owner by the registration number.
     * @param registrationNumber Registration number of a vehicle.
     * @return Current owner of the vehicle.
     */
    Owner findOwnerByRegistration(const std::string& registrationNumber) const;

    /**
     * @brief Returns the registration numbers of stolen vehicles.
     * @return List of registration numbers.
     */
    std::vector<std::string> getStolenRegistrationNumbers() const;

    /**
     * @brief Finds registration numbers of vehicles with accidents in a period.
     * @param start First date of the period.
     * @param end Last date of the period.
     * @return List of registration numbers.
     */
    std::vector<std::string> getAccidentRegistrationNumbers(
        const Date start, const Date end) const;

    /**
     * @brief Ranks stolen vehicle brands by their number of stolen cars.
     * @return Brand names and stolen counts, from highest to lowest.
     */
    std::vector<std::pair<std::string, std::size_t>> getStolenBrandRanking() const;

private:
    std::vector<std::reference_wrapper<const Vehicle>> vehicles_;
};
