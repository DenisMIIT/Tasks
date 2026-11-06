#pragma once

#include <string>

/**
 * @brief Stores information about a vehicle owner.
 */
class Owner {
public:
    /**
     * @brief Creates an owner.
     * @param fullName Full name of the owner.
     * @param address Address of the owner.
     */
    Owner(std::string fullName, std::string address);

    /**
     * @brief Returns the owner's full name.
     * @return Full name.
     */
    std::string getFullName() const;

    /**
     * @brief Returns the owner's address.
     * @return Address.
     */
    std::string getAddress() const;

    /**
     * @brief Makes a short description of the owner.
     * @return Text with the owner details.
     */
    std::string toString() const;

private:
    std::string fullName_;
    std::string address_;
};
