#include "VehicleRegistry.h"

#include <algorithm>
#include <map>
#include <stdexcept>
#include <utility>

void VehicleRegistry::addVehicle(const Vehicle& vehicle) {
    for (const Vehicle& current : vehicles_) {
        if (current.getRegistrationNumber() == vehicle.getRegistrationNumber() ||
            current.getEngineNumber() == vehicle.getEngineNumber()) {
            throw std::invalid_argument("Registration or engine number already exists");
        }
    }

    vehicles_.push_back(std::cref(vehicle));
}

const Vehicle& VehicleRegistry::findByRegistration(
    const std::string& registrationNumber) const {
    for (const Vehicle& vehicle : vehicles_) {
        if (vehicle.getRegistrationNumber() == registrationNumber) {
            return vehicle;
        }
    }
    throw std::out_of_range("Registration number was not found");
}

const Vehicle& VehicleRegistry::findByEngine(const std::string& engineNumber) const {
    for (const Vehicle& vehicle : vehicles_) {
        if (vehicle.getEngineNumber() == engineNumber) {
            return vehicle;
        }
    }
    throw std::out_of_range("Engine number was not found");
}

Owner VehicleRegistry::findOwnerByRegistration(
    const std::string& registrationNumber) const {
    return findByRegistration(registrationNumber).getOwner();
}

std::vector<std::string> VehicleRegistry::getStolenRegistrationNumbers() const {
    std::vector<std::string> result;
    for (const Vehicle& vehicle : vehicles_) {
        if (vehicle.isStolen()) {
            result.push_back(vehicle.getRegistrationNumber());
        }
    }
    return result;
}

std::vector<std::string> VehicleRegistry::getAccidentRegistrationNumbers(
    const Date& start, const Date& end) const {
    if (end < start) {
        throw std::invalid_argument("The end date is before the start date");
    }

    std::vector<std::string> result;
    for (const Vehicle& vehicle : vehicles_) {
        for (const Accident& accident : vehicle.getAccidents()) {
            if (start <= accident.getDate() && accident.getDate() <= end) {
                result.push_back(vehicle.getRegistrationNumber());
                break;
            }
        }
    }
    return result;
}

std::vector<std::pair<std::string, std::size_t>>
VehicleRegistry::getStolenBrandRanking() const {
    std::map<std::string, std::size_t> counts;
    for (const Vehicle& vehicle : vehicles_) {
        if (vehicle.isStolen()) {
            ++counts[vehicle.getBrand()];
        }
    }

    std::vector<std::pair<std::string, std::size_t>> ranking(counts.begin(), counts.end());
    std::sort(ranking.begin(), ranking.end(),
              [](const auto& left, const auto& right) {
                  if (left.second != right.second) {
                      return left.second > right.second;
                  }
                  return left.first < right.first;
              });
    return ranking;
}

