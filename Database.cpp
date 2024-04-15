#include "Database.h"
#include <algorithm>

// Constructor
Database::Database() {
}

std::vector<Media> Database::searchMovieSeries(const std::string& searchTerm) const {
    std::vector<Media> results;

    // Search for movies matching the search term
    for (const auto& movie : movies) {
        if (movie.getName().find(searchTerm) != std::string::npos) {
            results.push_back(movie);
        }
    }

    // Search for series matching the search term
    for (const auto& serie : series) {
        if (serie.getName().find(searchTerm) != std::string::npos) {
            results.push_back(serie);
        }
    }
    return results;
}


std::vector<Movie> Database::searchMoviesByName(const std::string& name) const {
    std::vector<Movie> foundMovies;

    // Iterate through the list of movies in the database
    for (const auto& movie : movies) {
        // Check if the movie name contains the search query
        if (movie.getName().find(name) != std::string::npos) {
            // If the movie name contains the search query, add it to the foundMovies vector
            foundMovies.push_back(movie);
        }
    }

    return foundMovies;
}



// Functions for user operations
void Database::addUser(const User& user) {
    users.push_back(user);
}

void Database::addMovieToUserWatchlist(User& user, const Movie& movie) {
            user.addMovieToWatchlist(movie);
}

void Database::addSeriesToUserWatchlist(User& user, const Series& series) {
           user.addSeriesToWatchlist(series);
}

void Database::removeMovieFromUserWatchlist(User& user, const std::string& movieName) {
            user.removeMovieFromWatchlist(movieName);
           
}

void Database::removeSeriesFromUserWatchlist(User& user, const std::string& seriesName) {
            user.removeSeriesFromWatchlist(seriesName);
            std::cout << "Serie deleted successfully." << std::endl;
}

std::string Database::categoryToString(Category category) const {
    switch (category) {
    case Category::SCIENCE_FICTION_FANTASY:
        return "Science Fiction/Fantasy";
    case Category::HORROR:
        return "Horror";
    case Category::COMEDY:
        return "Comedy";
    case Category::TENSION:
        return "Tension";
    default:
        return "Unknown";
    }
}

std::vector<Movie> Database::getMoviesByCategory(const Category category) const {
    std::vector<Movie> result;

    for (const auto& movie : movies) {
        if (movie.getCategory() == categoryToString(category)) {
            result.push_back(movie);
        }
    }
    return result;
}

std::vector<Series> Database::getSeriesByCategory(const Category category) const {
    std::vector<Series> result;
    for (const auto& s : series) {
        if (s.getCategory() == categoryToString(category)) {
            result.push_back(s);
        }
    }
    return result;
}

void Database::addMovie(const Movie& movie) {
    movies.push_back(movie);
}

void Database::addSeries(const Series& serie) {
    series.push_back(serie);
}

void Database::deleteMovie(const std::string& movieName) {
    movies.erase(std::remove_if(movies.begin(), movies.end(), [&](const Movie& movie) {
        return movie.getName() == movieName;
        }), movies.end());
}

void Database::deleteSeries(const std::string& seriesName) {
    series.erase(std::remove_if(series.begin(), series.end(), [&](const Series& serie) {
        return serie.getName() == seriesName;
        }), series.end());
}



// Modified deleteMovieByCategory method
void Database::deleteMovieByCategory(const Category category,User& User) {
    // Get movies in the specified category
    std::vector<Movie> moviesInCategory = getMoviesByCategory(category);

    // Display movies in the category
    if (moviesInCategory.empty()) {
        std::cout << "No movies found in this category." << std::endl;
        return;
    }
    else {
        std::cout << "Movies in the " << categoryToString(category) << " category:" << std::endl;
        for (size_t i = 0; i < moviesInCategory.size(); ++i) {
            std::cout << i + 1 << ". " << moviesInCategory[i].getName() << std::endl;
        }
    }

    // Prompt the user to choose a movie for deletion
    int choice;
    std::cout << "Enter the number of the movie you want to delete (0 to cancel): ";
    std::cin >> choice;

    // Validate user input
    if (choice >= 1 && static_cast<size_t>(choice) <= moviesInCategory.size()) {
        // Delete the chosen movie
        const std::string& movieNameToDelete = moviesInCategory[choice - 1].getName();
        auto it = std::remove_if(movies.begin(), movies.end(), [&](const Movie& movie) {
            return movie.getName() == movieNameToDelete;
            });
        if (it != movies.end()) {
            movies.erase(it, movies.end());
            removeMovieFromUserWatchlist(User, movieNameToDelete);
            std::cout << "Movie deleted successfully." << std::endl;
        }
        else {
            std::cout << "Movie not found." << std::endl;
        }
    }
    else if (choice != 0) {
        std::cout << "Invalid choice. Movie not deleted." << std::endl;
    }

    // Clear input buffer
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Modified deleteSeriesByCategory method
void Database::deleteSeriesByCategory(const Category category,User& User) {
    // Get series in the specified category
    std::vector<Series> seriesInCategory = getSeriesByCategory(category);

    // Display series in the category
    if (seriesInCategory.empty()) {
        std::cout << "No series found in this category." << std::endl;
        return;
    }
    else {
        std::cout << "Series in the " << categoryToString(category) << " category:" << std::endl;
        for (size_t i = 0; i < seriesInCategory.size(); ++i) {
            std::cout << i + 1 << ". " << seriesInCategory[i].getName() << std::endl;
        }
    }

    // Prompt the user to choose a series for deletion
    int choice;
    std::cout << "Enter the number of the series you want to delete (0 to cancel): ";
    std::cin >> choice;

    // Validate user input
    if (choice >= 1 && static_cast<size_t>(choice) <= seriesInCategory.size()) {
        // Delete the chosen series
        const std::string& seriesNameToDelete = seriesInCategory[choice - 1].getName();
        auto it = std::remove_if(series.begin(), series.end(), [&](const Series& s) {
            return s.getName() == seriesNameToDelete;
            });
        if (it != series.end()) {
            series.erase(it, series.end());
            removeSeriesFromUserWatchlist(User, seriesNameToDelete);
            std::cout << "Series deleted successfully." << std::endl;
        }
        else {
            std::cout << "Series not found." << std::endl;
        }
    }
    else if (choice != 0) {
        std::cout << "Invalid choice. Series not deleted." << std::endl;
    }

    // Clear input buffer
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool Database::movieExists(const std::string& movieName) const {
    for (const auto& movie : movies) {
        if (movie.getName() == movieName) {
            return true;
        }
    }
    return false;
}

bool Database::seriesExists(const std::string& seriesName) const {
    for (const auto& s : series) {
        if (s.getName() == seriesName) {
            return true;
        }
    }
    return false;
}

bool Database::userExists(const std::string& userID) const {
    for (const auto& user : users) {
        if (user.getSSN() == userID) {
            return true;
        }
    }
    return false;
}

bool Database::managerExists(const std::string& managerID) const {
    for (const auto& manager : managers) {
        if (manager.getSSN() == managerID) {
            return true;
        }
    }
    return false;
}

std::vector<Series> Database::searchSeries(const std::string& searchTerm) {
    std::vector<Series> matchingSeries;
    for (const auto& serie : series) {
        if (serie.getName().find(searchTerm) != std::string::npos) {
            matchingSeries.push_back(serie);
        }
    }
    return matchingSeries;
}

std::vector<Movie> Database::getMoviesByUser(User user) const {
    std::vector<Movie> userMovies;
    return user.getMovieWatchlist();
}

std::vector<Series> Database::getSeriesByUser(User user) const {
            return  user.getSeriesWatchlist();
}

void Database::addMediaToUserWatchlist(const std::string& userID, const Media& media) {
    for (auto& user : users) {
        if (user.getSSN() == userID) {
            user.addMediaToWatchlist(media);
            return;
        }
    }
}

void Database::readMoviesFromFile(const std::string& filename) {
    std::ifstream movieFile(filename);
    if (!movieFile) {
        std::cerr << "Error opening " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(movieFile, line)) {
        std::stringstream ss(line);
        std::string name, category;
        int year, length;
        std::getline(ss, name, ','); // Extract movie name
        std::getline(ss, category, ',');
        ss >> year;
        ss.ignore(); // Ignore comma
        ss >> length;
        Movie movie(name, year, length, category);
        addMovie(movie);
    }
    movieFile.close();
}

void Database::readSeriesFromFile(const std::string& filename) {
    std::ifstream seriesFile(filename);
    if (!seriesFile) {
        std::cerr << "Error opening " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(seriesFile, line)) {
        std::stringstream ss(line);
        std::string name, category;
        int year, seasons, episodes;
        std::getline(ss, name, ','); // Extract series name
        std::getline(ss, category, ',');
        ss >> year;
        ss.ignore(); // Ignore comma
        ss >> seasons;
        ss.ignore(); // Ignore comma
        ss >> episodes;
        Series serie(name, year, category, seasons, episodes);
        addSeries(serie);
    }
    seriesFile.close();
}

void Database::sortMoviesByEntryOrder() {
    std::sort(movies.begin(), movies.end(), [](const Movie& a, const Movie& b) {
        return a.getEntryOrder() < b.getEntryOrder();
        });
}

void Database::sortSeriesByEntryOrder() {
    std::sort(series.begin(), series.end(), [](const Series& a, const Series& b) {
        return a.getEntryOrder() < b.getEntryOrder();
        });
}

void Database::sortMoviesByYearAndEntryOrder() {
    std::sort(movies.begin(), movies.end(), [](const Movie& a, const Movie& b) {
        if (a.getYear() != b.getYear()) {
            return a.getYear() > b.getYear(); // Sort by year of release (descending)
        }
        else {
            return a.getEntryOrder() < b.getEntryOrder(); // Then by order of entry (ascending)
        }
        });
}

void Database::sortSeriesByYearAndEntryOrder() {
    std::sort(series.begin(), series.end(), [](const Series& a, const Series& b) {
        if (a.getYear() != b.getYear()) {
            return a.getYear() > b.getYear(); // Sort by year of release (descending)
        }
        else {
            return a.getEntryOrder() < b.getEntryOrder(); // Then by order of entry (ascending)
        }
        });
}

bool Database::isMovieInUserWatchlist(User userID, const std::string& movieName) const {
            return userID.isMovieInWatchlist(movieName);
}

bool Database::isSeriesInUserWatchlist(User userID, const std::string& seriesName) const {
            return userID.isSeriesInWatchlist(seriesName);
}

int Database::getNextMovieEntryOrder() {
    return ++movieEntryCounter;
}

int Database::getNextSeriesEntryOrder() {
    return ++seriesEntryCounter;
}


void Database::writeMoviesToFile(const std::string& filename) const {
    std::ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    // Iterate through each movie and write its details to the file
    for (const auto& movie : movies) {
        outputFile << movie.getName() << "," << movie.getCategory() << "," << movie.getLength() << "," << movie.getYear() << std::endl;
    }

    outputFile.close();
}

void Database::writeSeriesToFile(const std::string& filename) const {
    std::ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    // Iterate through each series and write its details to the file
    for (const auto& serie : series) {
        outputFile << serie.getName() << "," << serie.getCategory() << "," << serie.getYear() << "," << serie.getSeasons() << "," << serie.getEpisodesPerSeason() << std::endl;
    }

    outputFile.close();
}

void Database::writeUserMovieWatchlistToFile(const User& user, const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << " for writing." << std::endl;
        return;
    }

    // Write the user's movie watchlist to the file
    for (const Movie& movie : user.getMovieWatchlist()) {
        file << movie.getName() << ',' << movie.getYear() << ',' << movie.getCategory() << ',' << movie.getLength() << std::endl;
    }

    file.close();
}

void Database::writeUserSeriesWatchlistToFile(const User& user, const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << " for writing." << std::endl;
        return;
    }

    // Write the user's series watchlist to the file
    for (const Series& series : user.getSeriesWatchlist()) {
        file << series.getName() << ',' << series.getYear() << ',' << series.getCategory() << ',' << series.getSeasons() << ',' << series.getEpisodesPerSeason() << std::endl;
    }

    file.close();
}
void Database::loadUserSeriesWatchlistFromFile(User& user, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << " for reading." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name, category;
        int year, seasons, episodes;
        std::getline(ss, name, ','); // Extract series name
        std::getline(ss, category, ',');
        ss >> year;
        ss.ignore(); // Ignore comma
        ss >> seasons;
        ss.ignore(); // Ignore comma
        ss >> episodes;
        Series serie(name, year, category, seasons, episodes);
        user.addSeriesToWatchlist(serie);
    }

    file.close();
}

void Database::loadUserMovieWatchlistFromFile(User& user, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << " for reading." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name, category;
        int year, length;
        std::getline(ss, name, ','); // Extract movie name
        std::getline(ss, category, ',');
        ss >> year;
        ss.ignore(); // Ignore comma
        ss >> length;
        Movie movie(name, year, length, category);
        user.addMovieToWatchlist(movie);
    }

    file.close();
}


