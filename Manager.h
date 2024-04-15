#pragma once
#ifndef MANAGER_H
#define MANAGER_H

#include "Person.h"

class Manager : public Person {
public:
    // Constructor
    Manager(const std::string& SSN, const std::string& firstName, const std::string& lastName,
        const std::string& dateOfBirth);
};

#endif // MANAGER_H
