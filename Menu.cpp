#include "Menu.h"
#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

int Menu::displayMainMenu() {
    std::cout << "Main Menu:\n";
    std::cout << "1. User\n";
    std::cout << "2. Administrator\n";
    std::cout << "3. Exit\n";
    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
    return choice;
}

int Menu::displayUserMenu() {
    std::cout << "User Menu:\n";
    std::cout << "1. Add series to watch list\n";
    std::cout << "2. Add movie to watch list\n";
    std::cout << "3. Search for movie/series\n";
    std::cout << "4. View series from watch list\n";
    std::cout << "5. View movie from watch list\n";
    std::cout << "6. Delete movie from watch list\n";
    std::cout << "7. Delete series from watch list\n";
    std::cout << "8. Exit to main menu\n";
    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
    return choice;
}

int Menu::displayAdminMenu() {
    std::cout << "Administrator Menu:\n";
    std::cout << "1. Insert new movie\n";
    std::cout << "2. Insert new series\n";
    std::cout << "3. Delete movie\n";
    std::cout << "4. Delete series\n";
    std::cout << "5. Exit to main menu\n";
    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
    return choice;
}

int Menu::displayCategoryMenu() {
    std::cout << "Please select a category:\n";
    std::cout << "1. Science fiction / fantasy\n";
    std::cout << "2. Horror\n";
    std::cout << "3. Comedy\n";
    std::cout << "4. Tension\n";
    std::cout << "5. Return to previous menu\n";
    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
    return choice;
}

int Menu::displayDeletionOptionMenu() {
    std::cout << "Select deletion option:\n";
    std::cout << "1. Delete by search\n";
    std::cout << "2. Delete by category\n";
    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
    return choice;
}
void Menu::addUserMovie(Database& db, User& user) {
    std::cout << "Adding a new movie to the user's watch list...\n";
    int choice;
    std::vector<std::string> offeredMovies;  
    do {
        choice = displayCategoryMenu();

        if (choice != 5) {
            Category category = static_cast<Category>(choice - 1); 
            db.sortMoviesByEntryOrder();  
            db.sortMoviesByYearAndEntryOrder();  
            std::vector<Movie> filteredMovies;
            for (const auto& movie : db.getMoviesByCategory(category)) {
                if (!db.isMovieInUserWatchlist(user, movie.getName()) &&
                    !db.isMovieSuggested(user.getSSN(), movie.getName()) &&
                    std::find(offeredMovies.begin(), offeredMovies.end(), movie.getName()) == offeredMovies.end()) {
                    filteredMovies.push_back(movie);
                }
            }

            for (const auto& movie : filteredMovies) {
                std::cout << "Title: " << movie.getName() << ", Year: " << movie.getYear() << std::endl;
                std::cout << "Do you want to add this movie to your watchlist? (1 for Yes, 0 for No, 2 to return to user menu): ";
                int addChoice;
                std::cin >> addChoice;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
                if (addChoice == 1) {
                    db.addMovieToUserWatchlist(user, movie);
                    std::cout << "Movie added to watchlist.\n";
                    return; // Return to user menu after adding one movie
                }
                else if (addChoice == 0) {
                    // Add the movie to the list of offered movies
                    offeredMovies.push_back(movie.getName());
                }
                else if (addChoice == 2) {
                    return; // Return to user menu
                }
                else {
                    std::cout << "Invalid choice.\n";
                }
            }
        }
    } while (choice != 5); // Repeat until user selects "Return to the previous menu"
}

void Menu::addUserSeries(Database& db, User& user) {
    std::cout << "Adding a new series to the user's watch list...\n";
    int choice;
    std::vector<std::string> offeredSeries;  // List to keep track of offered series
    do {
        // Display category menu
        choice = displayCategoryMenu();

        if (choice != 5) {
            // Retrieve series from the chosen category from the database
            Category category = static_cast<Category>(choice - 1); // Convert choice to Category enum
            db.sortSeriesByEntryOrder();  // Sort series by entry order
            db.sortSeriesByYearAndEntryOrder();  // Sort series by year of release and then by order of entry

            // Filter out series that are already in the user's watchlist or have been offered before
            std::vector<Series> filteredSeries;
            for (const auto& series : db.getSeriesByCategory(category)) {
                if (!db.isSeriesInUserWatchlist(user, series.getName()) &&
                    !db.isSeriesSuggested(user.getSSN(), series.getName()) &&
                    std::find(offeredSeries.begin(), offeredSeries.end(), series.getName()) == offeredSeries.end()) {
                    filteredSeries.push_back(series);
                }
            }

            // Display newest series from the category to the user
            for (const auto& series : filteredSeries) {
                std::cout << "Title: " << series.getName() << ", Year: " << series.getYear() << std::endl;
                std::cout << "Do you want to add this series to your watchlist? (1 for Yes, 0 for No, 2 to return to user menu): ";
                int addChoice;
                std::cin >> addChoice;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
                if (addChoice == 1) {
                    db.addSeriesToUserWatchlist(user, series);
                    std::cout << "Series added to watchlist.\n";
                    return; // Return to user menu after adding one series
                }
                else if (addChoice == 0) {
                    // Add the series to the list of offered series
                    offeredSeries.push_back(series.getName());
                }
                else if (addChoice == 2) {
                    return; // Return to user menu
                }
                else {
                    std::cout << "Invalid choice.\n";
                }
            }
        }
    } while (choice != 5); // Repeat until user selects "Return to the previous menu"
}

void Menu::searchMovieSeries(Database& db) {
    std::cout << "Searching for a movie/series by name...\n";

    // Prompt the user to enter the name of the movie or series to search for
    std::string searchTerm;
    std::cout << "Enter the name of the movie/series to search for: ";
    std::cin.ignore(); // Ignore any remaining newline characters in the input buffer
    std::getline(std::cin, searchTerm);

    // Search for the movie or series in the database
    std::vector<Movie> foundMovies = db.searchMoviesByName(searchTerm);
    std::vector<Series> foundSeries = db.searchSeriesByName(searchTerm);

    // Display the search results
    if (!foundMovies.empty()) {
        const auto& movie = foundMovies.front();
        std::cout << "Found Movie:\n";
        std::cout << "Movie: " << movie.getName() << " (Year: " << movie.getYear() << ")\n";
        // Offer to add the movie to the user's watch list
        std::cout << "Do you want to add this movie to your watch list? (Y/N): ";
        char choice;
        std::cin >> choice;
        if (choice == 'Y' || choice == 'y') {
            // Add the movie to the user's watch list
            std::cout << "Movie added to your watch list.\n";
        }
        else {
            std::cout << "Movie not added to your watch list.\n";
        }
    }
    else if (!foundSeries.empty()) {
        const auto& series = foundSeries.front();
        std::cout << "Found Series:\n";
        std::cout << "Series: " << series.getName() << " (Year: " << series.getYear() << ")\n";
        // Offer to add the series to the user's watch list
        std::cout << "Do you want to add this series to your watch list? (Y/N): ";
        char choice;
        std::cin >> choice;
        if (choice == 'Y' || choice == 'y') {
            // Add the series to the user's watch list      
            std::cout << "Series added to your watch list.\n";
        }
        else {
            std::cout << "Series not added to your watch list.\n";
        }
    }
    else {
        // If no movies or series were found
        std::cout << "No movies or series found with the given name.\n";
    }
}


void Menu::viewSeries(Database& db,User user) {
    std::cout << "Viewing series from the user's watch list...\n";
    // Retrieve user's watchlist
    std::vector<Series> userWatchlist = db.getSeriesByUser(user);
    // Check if the watchlist is empty
    if (userWatchlist.empty()) {
        std::cout << "Your watchlist is empty.\n";
        return;
    }

    
    // Display all series in the watchlist
    for (const auto& series : userWatchlist) {
        std::cout << "Series Name: " << series.getName() << std::endl;
        std::cout << "Year: " << series.getYear() << std::endl;
        std::cout << "Category: " << series.getCategory() << std::endl;
        std::cout << "Seasons: " << series.getSeasons() << std::endl;
        std::cout << "Episodes per Season: " << series.getEpisodesPerSeason() << std::endl;
        std::cout << std::endl;
    }
}

void Menu::watchMovie(Database& db, User user) {
    std::cout << "Watching a movie from the user's watch list...\n";
    // Retrieve user's watchlist
    std::vector<Movie> userWatchlist = db.getMoviesByUser(user);

    // Check if the watchlist is empty
    if (userWatchlist.empty()) {
        std::cout << "Your watchlist is empty.\n";
        return;
    }

    // Display the first movie in the watchlist
    for (const auto& movie : userWatchlist) {
        std::cout << "Movie Name: " << movie.getName() << std::endl;
        std::cout << "Year: " << movie.getYear() << std::endl;
        std::cout << "Category: " << movie.getCategory() << std::endl;
        std::cout << "Length: " << movie.getLength() << " minutes" << std::endl;
        std::cout << std::endl;
    }
}




void Menu::deleteMovieFromWatchlist(Database& db,User& user) {
    std::vector<Movie> userWatchlist = user.getMovieWatchlist();
    if (userWatchlist.empty()) {
        std::cout << "Your watchlist is empty.\n";
        return;
    }
    std::cout << "Deleting a movie from the user's watch list...\n";
    // Retrieve user's watchlist
   

    // Display user's watchlist
    std::cout << "Movies in watchlist:\n";
    for (size_t i = 0; i < userWatchlist.size(); ++i) {
        std::cout << i + 1 << ". " << userWatchlist[i].getName() << std::endl;
    }

    // Prompt user to enter the index of the movie to delete
    size_t indexToDelete;
    std::cout << "Enter the number of the movie to delete: ";
    std::cin >> indexToDelete;

    // Check if the entered index is valid
    if (indexToDelete > 0 && indexToDelete <= userWatchlist.size()) {
        // Delete the selected movie from the user's watchlist
        db.removeMovieFromUserWatchlist(user, userWatchlist[indexToDelete - 1].getName());
        std::cout << "Movie deleted successfully.\n";
    }
    else {
        std::cout << "Invalid input. No movie deleted.\n";
    }
}

void Menu::deleteSeriesFromWatchlist(Database& db,User& user) {
    std::vector<Series> userWatchlist = user.getSeriesWatchlist();
    if (userWatchlist.empty()) {
        std::cout << "Your watchlist is empty.\n";
        return;
    }
    std::cout << "Deleting a series from the user's watch list...\n";
    // Display user's watchlist
    std::cout << "Series in watchlist:\n";
    for (size_t i = 0; i < userWatchlist.size(); ++i) {
        std::cout << i + 1 << ". " << userWatchlist[i].getName() << std::endl;
    }

    // Prompt user to enter the index of the series to delete
    size_t indexToDelete;
    std::cout << "Enter the number of the series to delete: ";
    std::cin >> indexToDelete;

    // Check if the entered index is valid
    if (indexToDelete > 0 && indexToDelete <= userWatchlist.size()) {
        // Delete the selected series from the user's watchlist
        db.removeSeriesFromUserWatchlist(user, userWatchlist[indexToDelete - 1].getName());
        std::cout << "Series deleted successfully.\n";
    }
    else {
        std::cout << "Invalid input. No series deleted.\n";
    }
}

void Menu::insertNewMovie(Database& db) {
    std::cout << "Inserting a new movie into the system...\n";

    // Prompt user to enter movie details
    std::string movieName;
    int length;
    int year;
    int categoryChoice; // Variable to store user's category choice
    std::string category;
    bool validChoice = false;

    std::cout << "Enter movie name: ";
    //std::cin.ignore(); // Ignore any remaining newline characters in the input buffer
    std::getline(std::cin, movieName);

    std::cout << "Enter movie length (in minutes): ";
    std::cin >> length;

    std::cout << "Enter year of release: ";
    std::cin >> year;

    // Prompt user to choose category
    std::cout << "Select movie category:\n";
    std::cout << "1. Science Fiction/Fantasy\n";
    std::cout << "2. Horror\n";
    std::cout << "3. Comedy\n";
    std::cout << "4. Tension\n";
    
    
    while (!validChoice) {
        std::cin >> categoryChoice;
        switch (categoryChoice) {
        case 1:
            validChoice = true;
            category = "Science Fiction/Fantasy";
            break;
        case 2:
            validChoice = true;
            category = "Horror";
            break;
        case 3:
            validChoice = true;
            category = "Comedy";
            break;
        case 4:
            validChoice = true;
            category = "Tension";
            break;
        default:
            std::cout << "Invalid category choice. Please choose a valid category (1-4): ";
            break;
        }
    }

    // Create a new Movie object with the provided details
    Movie newMovie(movieName, length, year, category);

    // Add the new movie to the system
    db.addMovie(newMovie);

    db.writeMoviesToFile("movies.txt");
}

void Menu::insertNewSeries(Database& db) {
    std::cout << "Inserting a new series into the system...\n";

    
    std::string seriesName;
    int year;
    std::string category;
    int seasons;
    int episodesPerSeason;
    bool validChoice = false;
    int categoryChoice; 

    std::cout << "Enter series name: ";
    std::cin.ignore(); 
    std::getline(std::cin, seriesName);

    std::cout << "Enter year of release: ";
    std::cin >> year;

    // Prompt user to choose category
    std::cout << "Select serie category:\n";
    std::cout << "1. Science Fiction/Fantasy\n";
    std::cout << "2. Horror\n";
    std::cout << "3. Comedy\n";
    std::cout << "4. Tension\n";


    while (!validChoice) {
        std::cin >> categoryChoice;
        switch (categoryChoice) {
        case 1:
            validChoice = true;
            category = "Science Fiction/Fantasy";
            break;
        case 2:
            validChoice = true;
            category = "Horror";
            break;
        case 3:
            validChoice = true;
            category = "Comedy";
            break;
        case 4:
            validChoice = true;
            category = "Tension";
            break;
        default:
            std::cout << "Invalid category choice. Please choose a valid category (1-4): ";
            break;
        }
    }
   

    std::cout << "Enter number of seasons: ";
    std::cin >> seasons;

    std::cout << "Enter number of episodes per season: ";
    std::cin >> episodesPerSeason;

    // Create a new Series object with the provided details
    Series newSeries(seriesName, year, category, seasons, episodesPerSeason);

    // Add the new series to the system
    db.addSeries(newSeries);

    db.writeSeriesToFile("series.txt");
}

void Menu::deleteMovie(Database& db,User& User) {
    std::cout << "Deleting a movie from the system...\n";
    std::cout << "Please select a deletion option:\n";
    std::cout << "1. Delete by search\n";
    std::cout << "2. Delete by category\n";
    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer

    if (choice == 1) {
        // Delete by search
        std::string movieName;
        std::cout << "Enter the name of the movie to delete: ";
        std::cin >> movieName;
        db.deleteMovie(movieName);
        db.removeMovieFromUserWatchlist(User, movieName);
        std::cout << "Movie deleted successfully." << std::endl;

    }
    else if (choice == 2) {
        // Delete by category
        std::cout << "Please select a category:\n";
        std::cout << "1. Science fiction / fantasy\n";
        std::cout << "2. Horror\n";
        std::cout << "3. Comedy\n";
        std::cout << "4. Tension\n";
        int categoryChoice;
        std::cin >> categoryChoice;
        db.deleteMovieByCategory(static_cast<Category>(categoryChoice - 1),User);
       
    }
    else {
        std::cout << "Invalid choice.\n";
    }
    db.writeMoviesToFile("movies.txt");

}

void Menu::deleteSeries(Database& db,User& User) {
    std::cout << "Deleting a series from the system...\n";
    std::cout << "Please select a deletion option:\n";
    std::cout << "1. Delete by search\n";
    std::cout << "2. Delete by category\n";
    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer

    if (choice == 1) {
        // Delete by search
        std::string seriesName;
        std::cout << "Enter the name of the series to delete: ";
        std::cin >> seriesName;
        db.deleteSeries(seriesName);
        db.removeSeriesFromUserWatchlist(User, seriesName);
        std::cout << "Serie deleted successfully." << std::endl;
    }
    else if (choice == 2) {
        // Delete by category
        std::cout << "Please select a category:\n";
        std::cout << "1. Science fiction / fantasy\n";
        std::cout << "2. Horror\n";
        std::cout << "3. Comedy\n";
        std::cout << "4. Tension\n";
        int categoryChoice;
        std::cin >> categoryChoice;
        db.deleteSeriesByCategory(static_cast<Category>(categoryChoice - 1),User);
    }
    else {
        std::cout << "Invalid choice.\n";
    }
    db.writeSeriesToFile("series.txt");
}


std::vector<Series> Database::searchSeriesByName(const std::string& name) const {
    std::vector<Series> foundSeries;

    for (const auto& series : series) {
        if (series.getName().find(name) != std::string::npos) {
            foundSeries.push_back(series);
        }
    }

    return foundSeries;
}




