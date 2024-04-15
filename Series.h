#pragma once
#ifndef SERIES_H
#define SERIES_H

#include "Media.h"

class Series : public Media {
private:
    int seasons;
    int episodesPerSeason;

public:
    // Constructor
    Series(const std::string& name, int year, const std::string& category, int seasons, int episodesPerSeason);

    // Accessors
    int getSeasons() const;
    int getEpisodesPerSeason() const;
};

#endif // SERIES_H
