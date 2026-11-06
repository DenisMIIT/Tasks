#include "Accident.h"
#include "Date.h"
#include "Owner.h"
#include "PassengerCar.h"
#include "Truck.h"
#include "VehicleRegistry.h"

#include <exception>
#include <iostream>
#include <functional>
#include <string>
#include <vector>

/**
 * @brief Shows searches in the vehicle registry.
 * @return Zero on success, nonzero on error.
 */
int main() {
    try {
        PassengerCar firstCar("A123BC", "ENG-100", "Lada", "Vesta", "White",
                              Owner("Ivan Petrov", "Moscow"), 5);
        firstCar.addPreviousOwner(Owner("Petr Ivanov", "Tver"));
        firstCar.addAccident(Accident(Date(2025, 4, 10), "Rear bumper"));
        firstCar.setStolen(true);

        PassengerCar secondCar("B234CD", "ENG-200", "Lada", "Granta", "Gray",
                               Owner("Anna Sidorova", "Kazan"), 5);
        secondCar.addAccident(Accident(Date(2025, 6, 2), "Front door"));
        secondCar.setStolen(true);

        Truck thirdCar("C345DE", "ENG-300", "Kamaz", "5490", "Blue",
                       Owner("Oleg Smirnov", "Moscow"), 18000);

        const std::vector<std::reference_wrapper<const Vehicle>> vehicles{
            firstCar, secondCar, thirdCar
        };

        std::cout << "All vehicles:\n";
        for (const Vehicle& vehicle : vehicles) {
            std::cout << vehicle.getInfo() << '\n';
        }

        VehicleRegistry registry;
        for (const Vehicle& vehicle : vehicles) {
            registry.addVehicle(vehicle);
        }

        std::cout << "\nSearch by registration:\n"
                  << registry.findByRegistration("A123BC").getInfo() << '\n';
        std::cout << "\nOwner by registration:\n"
                  << registry.findOwnerByRegistration("A123BC").toString() << '\n';

        const Vehicle& found = registry.findByEngine("ENG-100");
        std::cout << "\nVehicle by engine:\n" << found.getInfo() << '\n';
        for (const Owner& owner : found.getPreviousOwners()) {
            std::cout << "Previous owner: " << owner.toString() << '\n';
        }
        for (const Accident& accident : found.getAccidents()) {
            std::cout << "Accident: " << accident.toString() << '\n';
        }

        std::cout << "\nStolen vehicles:\n";
        for (const std::string& registration : registry.getStolenRegistrationNumbers()) {
            std::cout << registry.findByRegistration(registration).getInfo() << '\n';
        }

        std::cout << "\nAccidents in 2025:\n";
        for (const std::string& registration : registry.getAccidentRegistrationNumbers(
                 Date(2025, 1, 1), Date(2025, 12, 31))) {
            std::cout << registry.findByRegistration(registration).getInfo() << '\n';
        }

        std::cout << "\nMost stolen brands:\n";
        for (const auto& brandAndCount : registry.getStolenBrandRanking()) {
            std::cout << brandAndCount.first << ": " << brandAndCount.second << '\n';
        }
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
