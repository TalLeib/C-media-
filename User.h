#pragma once
#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "Person.h"
#include "Movie.h"
#include "Series.h"

class User : public Person {
private:
    std::vector<Movie> movieWatchlist;
    std::vector<Series> seriesWatchlist;
    std::vector<Media> watchlist;

public:
    // Constructor
    User(const std::string& SSN, const std::string& firstName, const std::string& lastName,
        const std::string& dateOfBirth);

    // Accessors
    std::vector<Movie> getMovieWatchlist() const;
    std::vector<Series> getSeriesWatchlist() const;

    // Mutators
    void addMovieToWatchlist(const Movie& movie);
    void addSeriesToWatchlist(const Series& series);
    void removeMovieFromWatchlist(const std::string& movieName);
    void removeSeriesFromWatchlist(const std::string& seriesName);
    void addMediaToWatchlist(const Media& media);
    bool isMovieInWatchlist(const std::string& movieName) const;
    bool isSeriesInWatchlist(const std::string& seriesName) const;

};

#endif // USER_H
