#include "Person.h"

// Constructor
Person::Person(const std::string& SSN, const std::string& firstName, const std::string& lastName,
    const std::string& dateOfBirth)
    : SSN(SSN), firstName(firstName), lastName(lastName), dateOfBirth(dateOfBirth) {}

std::string Person::getSSN() const {
    return SSN;
}

std::string Person::getFirstName() const {
    return firstName;
}

std::string Person::getLastName() const {
    return lastName;
}

std::string Person::getDateOfBirth() const {
    return dateOfBirth;
}
