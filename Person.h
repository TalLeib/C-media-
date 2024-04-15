#pragma once
#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person {
protected:
    std::string SSN;
    std::string firstName;
    std::string lastName;
    std::string dateOfBirth;

public:
    // Constructor
    Person(const std::string& SSN, const std::string& firstName, const std::string& lastName,
        const std::string& dateOfBirth);

    // Accessors
    std::string getSSN() const;
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getDateOfBirth() const;
};

#endif // PERSON_H
