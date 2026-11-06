#include "Accident.h"
#include "Date.h"
#include "Owner.h"
#include "PassengerCar.h"
#include "Truck.h"
#include "VehicleRegistry.h"

#include <gtest/gtest.h>

#include <stdexcept>
#include <string>
#include <vector>

/** @brief Checks search by registration number. */
TEST(VehicleRegistryTests, FindsVehicleByRegistration) {
    PassengerCar car("A123BC", "ENG1", "Lada", "Vesta", "White", Owner("Ivan", "Moscow"), 5);
    VehicleRegistry registry;
    registry.addVehicle(car);
    const Vehicle& found = registry.findByRegistration("A123BC");
    EXPECT_EQ(found.getBrand(), "Lada");
    EXPECT_EQ(found.getType(), "Passenger car");
    EXPECT_NE(found.getInfo().find("White"), std::string::npos);
}

/** @brief Checks search for the current owner. */
TEST(VehicleRegistryTests, FindsOwnerByRegistration) {
    Truck truck("T100", "ENG2", "Kamaz", "5490", "Blue", Owner("Petr", "Tver"), 10000);
    VehicleRegistry registry;
    registry.addVehicle(truck);
    const Owner owner = registry.findOwnerByRegistration("T100");
    EXPECT_EQ(owner.getFullName(), "Petr");
    EXPECT_EQ(owner.getAddress(), "Tver");
}

/** @brief Checks history by engine number. */
TEST(VehicleRegistryTests, FindsVehicleHistoryByEngine) {
    PassengerCar car("A1", "ENGINE42", "Toyota", "Corolla", "Red", Owner("New", "Moscow"), 5);
    car.addPreviousOwner(Owner("Old", "Kazan"));
    car.addAccident(Accident(Date(2024, 5, 20), "Front bumper"));
    VehicleRegistry registry;
    registry.addVehicle(car);
    const Vehicle& found = registry.findByEngine("ENGINE42");
    ASSERT_EQ(found.getPreviousOwners().size(), std::size_t{1});
    ASSERT_EQ(found.getAccidents().size(), std::size_t{1});
    EXPECT_EQ(found.getPreviousOwners().at(0).getFullName(), "Old");
    EXPECT_EQ(found.getAccidents().at(0).getDate().toString(), "2024-05-20");
}

/** @brief Checks stolen vehicle selection. */
TEST(VehicleRegistryTests, ListsStolenVehicles) {
    PassengerCar stolen("STOLEN", "E1", "Lada", "Vesta", "Black", Owner("A", "M"), 5);
    Truck safe("SAFE", "E2", "Kamaz", "5320", "Blue", Owner("B", "T"), 5000);
    stolen.setStolen(true);
    VehicleRegistry registry;
    registry.addVehicle(stolen);
    registry.addVehicle(safe);
    const auto found = registry.getStolenRegistrationNumbers();
    ASSERT_EQ(found.size(), std::size_t{1});
    EXPECT_EQ(found.at(0), "STOLEN");
}

/** @brief Checks accident selection without duplicate results. */
TEST(VehicleRegistryTests, ListsVehiclesWithAccidentsInPeriod) {
    PassengerCar first("A", "E1", "Lada", "Vesta", "Red", Owner("A", "M"), 5);
    Truck second("B", "E2", "Kamaz", "Model", "Blue", Owner("B", "T"), 5000);
    first.addAccident(Accident(Date(2025, 1, 1), "First"));
    first.addAccident(Accident(Date(2025, 4, 15), "Second"));
    second.addAccident(Accident(Date(2024, 12, 31), "Old"));
    VehicleRegistry registry;
    registry.addVehicle(first);
    registry.addVehicle(second);
    const auto found = registry.getAccidentRegistrationNumbers(Date(2025, 1, 1), Date(2025, 12, 31));
    ASSERT_EQ(found.size(), std::size_t{1});
    EXPECT_EQ(found.at(0), "A");
}

/** @brief Checks stolen brand ranking. */
TEST(VehicleRegistryTests, RanksStolenBrands) {
    PassengerCar first("A", "E1", "Lada", "One", "Red", Owner("A", "M"), 5);
    PassengerCar second("B", "E2", "Lada", "Two", "Red", Owner("B", "M"), 5);
    Truck third("C", "E3", "Kamaz", "Three", "Blue", Owner("C", "M"), 5000);
    first.setStolen(true);
    second.setStolen(true);
    third.setStolen(true);
    VehicleRegistry registry;
    registry.addVehicle(first);
    registry.addVehicle(second);
    registry.addVehicle(third);
    const auto result = registry.getStolenBrandRanking();
    ASSERT_EQ(result.size(), std::size_t{2});
    EXPECT_EQ(result.at(0).first, "Lada");
    EXPECT_EQ(result.at(0).second, std::size_t{2});
    EXPECT_EQ(result.at(1).first, "Kamaz");
}

/** @brief Checks duplicate registration and engine numbers. */
TEST(VehicleRegistryTests, RejectsDuplicateNumbers) {
    PassengerCar first("A", "E1", "Lada", "Vesta", "Red", Owner("A", "M"), 5);
    Truck sameRegistration("A", "E2", "Kamaz", "Model", "Blue", Owner("B", "M"), 1000);
    Truck sameEngine("B", "E1", "Kamaz", "Model", "Blue", Owner("B", "M"), 1000);
    VehicleRegistry registry;
    registry.addVehicle(first);
    EXPECT_THROW(registry.addVehicle(sameRegistration), std::invalid_argument);
    EXPECT_THROW(registry.addVehicle(sameEngine), std::invalid_argument);
}

/** @brief Checks errors for missing vehicles. */
TEST(VehicleRegistryTests, MissingVehicleThrows) {
    const VehicleRegistry registry;
    EXPECT_THROW(registry.findByRegistration("UNKNOWN"), std::out_of_range);
    EXPECT_THROW(registry.findByEngine("UNKNOWN"), std::out_of_range);
}

/** @brief Checks invalid dates and date ranges. */
TEST(VehicleRegistryTests, RejectsInvalidDatesAndRanges) {
    EXPECT_THROW(Date(2025, 2, 29), std::invalid_argument);
    EXPECT_EQ(Date(2024, 2, 29).toString(), "2024-02-29");
    const VehicleRegistry registry;
    EXPECT_THROW(registry.getAccidentRegistrationNumbers(Date(2026, 1, 1), Date(2025, 1, 1)),
                 std::invalid_argument);
}

/** @brief Checks empty search results. */
TEST(VehicleRegistryTests, EmptyRankingIsValid) {
    const VehicleRegistry registry;
    EXPECT_TRUE(registry.getStolenRegistrationNumbers().empty());
    EXPECT_TRUE(registry.getStolenBrandRanking().empty());
}

/** @brief Checks that result lists are copies. */
TEST(VehicleRegistryTests, ReturnedListsAreCopies) {
    PassengerCar car("A", "E", "Lada", "Vesta", "White", Owner("Ivan", "Moscow"), 5);
    car.setStolen(true);
    VehicleRegistry registry;
    registry.addVehicle(car);
    std::vector<std::string> numbers = registry.getStolenRegistrationNumbers();
    numbers.clear();
    EXPECT_EQ(registry.getStolenRegistrationNumbers().size(), std::size_t{1});
}

/** @brief Checks that the registry uses the original vehicle object. */
TEST(VehicleRegistryTests, ReadsUpdatedVehicle) {
    PassengerCar car("A", "E", "Lada", "Vesta", "White", Owner("Ivan", "Moscow"), 5);
    VehicleRegistry registry;
    registry.addVehicle(car);
    car.setStolen(true);
    EXPECT_EQ(registry.getStolenRegistrationNumbers().size(), std::size_t{1});
}
