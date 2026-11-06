#pragma once

#include "Accident.h"
#include "Owner.h"

#include <string>
#include <vector>

/**
 * @brief Stores common information about a registered vehicle.
 */
class Vehicle {
public:
    /**
     * @brief Creates a vehicle with its owner and basic details.
     * @param registrationNumber Registration number.
     * @param engineNumber Engine number.
     * @param brand Vehicle brand.
     * @param model Vehicle model.
     * @param color Vehicle color.
     * @param owner Current vehicle owner.
     */
    Vehicle(const std::string& registrationNumber, const std::string& engineNumber,
            const std::string& brand, const std::string& model, const std::string& color,
            const Owner& owner);

    /**
     * @brief Destroys a vehicle through its base class.
     */
    virtual ~Vehicle();

    /**
     * @brief Returns the type of the vehicle.
     * @return Type name.
     */
    virtual std::string getType() const = 0;

    /**
     * @brief Returns details that depend on the vehicle type.
     * @return Extra information.
     */
    virtual std::string getExtraInfo() const = 0;

    /**
     * @brief Returns information about the vehicle.
     * @return Text with vehicle details.
     */
    std::string getInfo() const;

    /**
     * @brief Returns the registration number.
     * @return Registration number.
     */
    std::string getRegistrationNumber() const;

    /**
     * @brief Returns the engine number.
     * @return Engine number.
     */
    std::string getEngineNumber() const;

    /**
     * @brief Returns the vehicle brand.
     * @return Brand name.
     */
    std::string getBrand() const;

    /**
     * @brief Returns the current owner.
     * @return Owner information.
     */
    Owner getOwner() const;

    /**
     * @brief Returns the previous owners.
     * @return List of previous owners.
     */
    std::vector<Owner> getPreviousOwners() const;

    /**
     * @brief Returns the accident records.
     * @return List of accidents.
     */
    std::vector<Accident> getAccidents() const;

    /**
     * @brief Checks if the vehicle is stolen.
     * @return True for a stolen vehicle.
     */
    bool isStolen() const;

    /**
     * @brief Changes the stolen status.
     * @param stolen New stolen status.
     */
    void setStolen(const bool stolen);

    /**
     * @brief Adds a previous owner.
     * @param owner Owner to add.
     */
    void addPreviousOwner(const Owner& owner);

    /**
     * @brief Adds an accident record.
     * @param accident Accident to add.
     */
    void addAccident(const Accident& accident);

private:
    std::string registrationNumber_;
    std::string engineNumber_;
    std::string brand_;
    std::string model_;
    std::string color_;
    Owner owner_;
    std::vector<Owner> previousOwners_;
    std::vector<Accident> accidents_;
    bool stolen_;
};
