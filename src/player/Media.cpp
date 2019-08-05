//
// Created by kalos on 26/04/19.
//

#include <cstring>
#include "Media.h"

const std::string &Media::getTitle() const {
    return title;
}

void Media::setTitle(const std::string &title) {
    Media::title = title;
}

const std::string &Media::getPath() const {
    return path;
}

void Media::setPath(const std::string &path) {
    Media::path = path;
}

const std::string &Media::getFormat() const {
    return format;
}

void Media::setFormat(const std::string &format) {
    Media::format = format;
}

const std::vector<std::pair<int, int>> &Media::getEpisodeXSeason() const {
    return episode_x_season;
}

void Media::putEpisodeXSeason(int s, int e) {
    episode_x_season.emplace_back(std::make_pair(s,e));
}

void Media::setEpisodeXSeason(const std::vector<std::pair<int, int>> &episodeXSeason) {
    episode_x_season = episodeXSeason;
}

int Media::getEpisodes() const {
    return episodes;
}

void Media::setEpisodes(int episodes) {
    Media::episodes = episodes;
}
