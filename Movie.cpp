#include "Movie.h"

// Constructor definition
Movie::Movie(const std::string& name, int length, int year, const std::string& category)
    : Media(name, year, category), length(length) {
    // Automatically assign entry order
    static int movieCount = 0;
    entryOrder = movieCount++;
}

int Movie::getLength() const {
    return length;
}

// Equality operator definition
bool Movie::operator==(const Movie& other) const {
    return name == other.name; 
}