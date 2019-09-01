//
// Created by kalos on 13/08/19.
//

#include "CurrentStatus.h"
using json = nlohmann::json;

libvlc_instance_t *CurrentStatus::getInstance() const {
    return instance;
}

void CurrentStatus::setInstance(libvlc_instance_t *instance) {
    CurrentStatus::instance = instance;
}

libvlc_media_player_t *CurrentStatus::getMediaPlayer() const {
    return mediaPlayer;
}

void CurrentStatus::setMediaPlayer(libvlc_media_player_t *mediaPlayer) {
    CurrentStatus::mediaPlayer = mediaPlayer;
}

libvlc_media_t *CurrentStatus::getMedia() const {
    return media;
}

void CurrentStatus::setMedia(libvlc_media_t *media) {
    CurrentStatus::media = media;
}

const Media &CurrentStatus::getCurrentMedia() const {
    return current_media;
}

void CurrentStatus::setCurrentMedia(const Media &currentMedia) {
    current_media = currentMedia;
}

int CurrentStatus::getEpisode() const {
    return episode;
}

void CurrentStatus::setEpisode(int episode) {
    CurrentStatus::episode = episode;
}

int CurrentStatus::getSeason() const {
    return season;
}

void CurrentStatus::setSeason(int season) {
    CurrentStatus::season = season;
}

void CurrentStatus::saveCurrentStatus(int64_t time) {

    json j;

    std::ofstream file("LastState.json");

    j["status"]["last_title"] = current_media.getTitle();
    j["status"]["last_episode"] = episode;
    j["status"]["last_season"] = season;
    j["status"]["stopped_time"] = time;

    file << std::setw(4) << j << std::endl;
}

std::string CurrentStatus::getCurrentPath() {

    return current_media.getPath() + "/" + std::to_string(season) + "/" +
           current_media.getTitle() + "S" + std::to_string(season) + "E" +
           std::to_string(episode) + current_media.getFormat();
}

void CurrentStatus::decreaseEpisode(){

    if(episode - 1 > 0)
        episode--;
    else
        throw NotFoundException();

}

void CurrentStatus::decreaseSeason(){

    if(season - 1 > 0 )
        season--;
    else
        throw NotFoundException();
}

void CurrentStatus::increaseEpisode(){
        episode++;
}

void CurrentStatus::increaseSeason(){

    if(season + 1 <= current_media.getEpisodeXSeason().size() )
        season++;
    else
        throw NotFoundException();
}

