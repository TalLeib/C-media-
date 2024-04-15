#include "User.h"

// Constructor
User::User(const std::string& SSN, const std::string& firstName, const std::string& lastName,
    const std::string& dateOfBirth)
    : Person(SSN, firstName, lastName, dateOfBirth) {}

std::vector<Movie> User::getMovieWatchlist() const {
    return movieWatchlist;
}

std::vector<Series> User::getSeriesWatchlist() const {
    return seriesWatchlist;
}

void User::addMovieToWatchlist(const Movie& movie) {
    movieWatchlist.push_back(movie);
}

void User::addSeriesToWatchlist(const Series& series) {
    seriesWatchlist.push_back(series);
}

void User::removeMovieFromWatchlist(const std::string& movieName) {
    for (auto it = movieWatchlist.begin(); it != movieWatchlist.end(); ++it) {
        if (it->getName() == movieName) {
            movieWatchlist.erase(it);
            break;
        }
    }
}

void User::removeSeriesFromWatchlist(const std::string& seriesName) {
    for (auto it = seriesWatchlist.begin(); it != seriesWatchlist.end(); ++it) {
        if (it->getName() == seriesName) {
            seriesWatchlist.erase(it);
            break;
        }
    }
}
void User::addMediaToWatchlist(const Media& media) {
    watchlist.push_back(media);
}

bool User::isMovieInWatchlist(const std::string& movieName) const {
    for (const auto& movie : movieWatchlist) {
        if (movie.getName() == movieName) {
            return true;
        }
    }
    return false;
}

bool User::isSeriesInWatchlist(const std::string& seriesName) const {
    for (const auto& series : seriesWatchlist) {
        if (series.getName() == seriesName) {
            return true;
        }
    }
    return false;
}