#pragma once
#ifndef MOVIE_H
#define MOVIE_H

#include "Media.h"

class Movie : public Media {
private:
    int length;

public:
    // Constructor
    Movie(const std::string& name, int length, int year, const std::string& category);

    // Accessor
    int getLength() const;
    bool operator==(const Movie& other) const;
};



#endif // MOVIE_H
