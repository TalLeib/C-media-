#include "main.h"
#include <fstream>
#include "movie.h"
#include "series.h"


int main() {
    Database db;
    db.readMoviesFromFile("movies.txt");
    db.readSeriesFromFile("series.txt");
    User Ani("123456789", "aharon", "rishon", "12/24/97");
    db.loadUserSeriesWatchlistFromFile(Ani, "watchlistS.txt");
    db.loadUserMovieWatchlistFromFile(Ani, "watchlistM.txt");
    bool exit = false;
    while (!exit) {
        int choice = 0;
        choice = Menu::displayMainMenu();
        bool userExit = false;
        bool adminExit = false;
        switch (choice) {
        case 1: // User menu
            std::cout << "User Menu" << std::endl;
            while (!userExit) {
                int userChoice = Menu::displayUserMenu();
                switch (userChoice) {
                case 1: // Add series to watchlist
                    Menu::addUserSeries(db, Ani);
                    break;
                case 2: // Add movie to watchlist
                    Menu::addUserMovie(db,Ani);
                    break;
                case 3: // Search movie/series
                    Menu::searchMovieSeries(db);
                    break;
                case 4: // View series
                    Menu::viewSeries(db, Ani);
                    break;
                case 5: // Watch movie
                    Menu::watchMovie(db,Ani);
                    break;
                case 6: // Delete movie from watchlist
                    Menu::deleteMovieFromWatchlist(db,Ani);
                    break;
                case 7: // Delete series from watchlist
                    Menu::deleteSeriesFromWatchlist(db, Ani);
                    break;
                case 8: // Exit to main menu
                    userExit = true;
                    break;
                default:
                    std::cout << "Invalid choice. Please try again." << std::endl;
                }
            }
            break;
        case 2: // Administrator menu
            std::cout << "Administrator Menu" << std::endl;
            while (!adminExit) {
                int adminChoice = Menu::displayAdminMenu();
                switch (adminChoice) {
                case 1: // Insert new movie
                    Menu::insertNewMovie(db);
                    break;
                case 2: // Insert new series
                    Menu::insertNewSeries(db);
                    break;
                case 3: // Delete movie
                    Menu::deleteMovie(db,Ani);
                    break;
                case 4: // Delete series
                    Menu::deleteSeries(db,Ani);
                    break;
                case 5: // Exit to main menu
                    adminExit = true;
                    break;
                default:
                    std::cout << "Invalid choice. Please try again." << std::endl;
                }
            }
            break;
        case 3: // Exit
            exit = true;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
    db.writeUserSeriesWatchlistToFile(Ani, "watchlistS.txt");
    db.writeUserMovieWatchlistToFile(Ani, "watchlistM.txt");

    return 0;
}