#include "Series.h"

// Constructor 
Series::Series(const std::string& name, int year, const std::string& category, int seasons, int episodesPerSeason)
    : Media(name, year, category), seasons(seasons), episodesPerSeason(episodesPerSeason) {
    // Automatically assign entry order
    static int seriesCount = 0;
    entryOrder = seriesCount++;
}

//  accessors
int Series::getSeasons() const {
    return seasons;
}

int Series::getEpisodesPerSeason() const {
    return episodesPerSeason;
}
