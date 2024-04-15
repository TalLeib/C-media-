#pragma once
#ifndef MEDIA_H
#define MEDIA_H

#include <string>

class Media {
protected:
    std::string name;
    int year;
    std::string category;
    int entryOrder; // Entry order variable

    static int totalMedia; // Static variable to keep track of total media
public:
    Media(const std::string& name, int year, const std::string& category);

    // Accessors
    std::string getName() const;
    int getYear() const;
    std::string getCategory() const;
    int getEntryOrder() const;

};

#endif // MEDIA_H
