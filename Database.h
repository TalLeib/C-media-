#ifndef DATABASE_H
#define DATABASE_H

#include "Category.h"
#include <string>
#include <vector>
#include "Movie.h"
#include "Series.h"
#include "User.h"
#include "Manager.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <unordered_map>
#include <algorithm>

class Database {
private:
    std::vector<Movie> movies;
    std::vector<Series> series;
    std::vector<User> users;
    std::vector<Manager> managers;
    std::map<Category, std::vector<Movie>> moviesByCategory;
    std::map<Category, std::vector<Series>> seriesByCategory;
    int movieEntryCounter = 0; // Counter for movie entry order
    int seriesEntryCounter = 0; // Counter for series entry order
    // Existing member variables
    std::unordered_map<std::string, std::vector<std::string>> suggestedMovies;
    std::unordered_map<std::string, std::vector<std::string>> suggestedSeries;
    std::vector<std::string> offeredMovies;  // List of offered movies for all users
    std::vector<std::string> offeredSeries;  // List of offered series for all user

    // Member functions to increment entry counters
    int getNextMovieEntryOrder();
    int getNextSeriesEntryOrder();


public:
    // Constructor
    Database();
    std::vector<Movie> searchMoviesByName(const std::string& name) const;
    std::vector<Series> searchSeriesByName(const std::string& name) const;
    // Functions for user operations
    void addUser(const User& user);
    void addMovieToUserWatchlist(User& user, const Movie& movie);
    void addSeriesToUserWatchlist(User& user, const Series& series);
    void removeMovieFromUserWatchlist(User& user, const std::string& movieName);
    void removeSeriesFromUserWatchlist(User& user, const std::string& seriesName);
    std::string categoryToString(Category category) const;
    std::vector<Movie> getMoviesByCategory(const Category category) const;
    std::vector<Series> getSeriesByCategory(const Category category) const;

    // Functions for administrator operations
    void addMovie(const Movie& movie);
    void addSeries(const Series& series);
    void deleteMovie(const std::string& movieName);
    void deleteSeries(const std::string& seriesName);
   
    void deleteMovieByCategory(const Category category,User& User);
    void deleteSeriesByCategory(const Category category,User& User);
    bool movieExists(const std::string& movieName) const;
    bool seriesExists(const std::string& seriesName) const;
    bool userExists(const std::string& userID) const;
    bool managerExists(const std::string& managerID) const;
    void writeMoviesToFile(const std::string& filename) const;
    void writeSeriesToFile(const std::string& filename) const;
    // Function declarations for searching movies and series
    std::vector<Series> searchSeries(const std::string& searchTerm);

    // New member functions for user watchlist operations
    std::vector<Movie> getMoviesByUser(User user) const;
    std::vector<Series> getSeriesByUser(User user) const;
    std::vector<Media> searchMovieSeries(const std::string& searchTerm) const;
    void addMediaToUserWatchlist(const std::string& userID, const Media& media);

    // Functions for reading data from files
    void readMoviesFromFile(const std::string& filename);
    void readSeriesFromFile(const std::string& filename);

    // Functions for sorting movies and series
    void sortMoviesByEntryOrder();
    void sortSeriesByEntryOrder();
    void sortMoviesByYearAndEntryOrder();
    void sortSeriesByYearAndEntryOrder();

    // Functions for checking if media is in user's watchlist
    bool isMovieInUserWatchlist(User userID, const std::string& movieName) const;
    bool isSeriesInUserWatchlist(User userID, const std::string& seriesName) const;
   

    void addSuggestedMovie(const std::string& userID, const std::string& movieName) {
        suggestedMovies[userID].push_back(movieName);
    }

    // Function to check if a movie has been suggested to a user
    bool isMovieSuggested(const std::string& userID, const std::string& movieName) {
        return std::find(suggestedMovies[userID].begin(), suggestedMovies[userID].end(), movieName) != suggestedMovies[userID].end();
    }

    // Function to add suggested series for a user
    void addSuggestedSeries(const std::string& userID, const std::string& seriesName) {
        suggestedSeries[userID].push_back(seriesName);
    }

    // Function to check if a series has been suggested to a user
    bool isSeriesSuggested(const std::string& userID, const std::string& seriesName) {
        return std::find(suggestedSeries[userID].begin(), suggestedSeries[userID].end(), seriesName) != suggestedSeries[userID].end();
    }

    void writeUserMovieWatchlistToFile(const User& user, const std::string& filename) const;
    void writeUserSeriesWatchlistToFile(const User& user, const std::string& filename) const;
    void loadUserSeriesWatchlistFromFile(User& user, const std::string& filename);
    void loadUserMovieWatchlistFromFile(User& user, const std::string& filename);
};

#endif // DATABASE_H
