#include "Media.h"

int Media::totalMedia = 0; // Initialize static member variable



// Constructor implementation
Media::Media(const std::string& name, int year, const std::string& category)
    : name(name), year(year), category(category) {
    totalMedia++; // Increment total media
    entryOrder = totalMedia; // Assign entry order
}

// Getter function for entry order
int Media::getEntryOrder() const {
    return entryOrder;
}

std::string Media::getName() const {
    return name;
}

int Media::getYear() const {
    return year;
}

std::string Media::getCategory() const {
    return category;
}
