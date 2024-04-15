#pragma once
#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <limits>
#include "Database.h"
#include "Category.h"

class Menu {
public:
    // Display main menu and return user's choice
    static int displayMainMenu();

    // Display user menu and return user's choice
    static int displayUserMenu();

    // Display administrator menu and return user's choice
    static int displayAdminMenu();

    // Display submenu for selecting category and return user's choice
    static int displayCategoryMenu();

    // Display submenu for selecting deletion option and return user's choice
    static int displayDeletionOptionMenu();

    // Function to handle adding a new series to the user's watch list
    static void addUserSeries(Database& db,User& user);

    // Function to handle adding a new movie to the user's watch list
    static void addUserMovie(Database& db,User& user);

    // Function to handle searching for a movie/series by name
    static void searchMovieSeries(Database& db);

    // Function to handle viewing a series from the list
    static void viewSeries(Database& db, User user);

    // Function to handle watching a movie from the list
    static void watchMovie(Database& db,User user);

    // Function to handle deleting a movie from the user's watch list
    static void deleteMovieFromWatchlist(Database& db,User& user);

    // Function to handle deleting a series from the user's watch list
    static void deleteSeriesFromWatchlist(Database& db,User& user);

    // Function to handle inserting a new film into the system (for administrator)
    static void insertNewMovie(Database& db);

    // Function to handle inserting a new series into the system (for administrator)
    static void insertNewSeries(Database& db);

    // Function to handle deleting a movie from the system (for administrator)
    static void deleteMovie(Database& db,User& User);

    // Function to handle deleting a series from the system (for administrator)
    static void deleteSeries(Database& db,User& User);

};

#endif // MENU_H

