//
// Created by kalos on 05/08/19.
//

#include "DatabaseManager.h"
using json = nlohmann::json;

DatabaseManager* DatabaseManager::getDatabaseInstance() {
    std::call_once(inited,[]{
        instance = new DatabaseManager();
        instance->buildDatabaseFromJson();
    });

    return instance;
}

/*
 * Loads into the media vector all the parsed list.JSON file
 */
void DatabaseManager::buildDatabaseFromJson() {
    json j;

    std::ifstream file("OfflineDB.json");

    j = json::parse(file);

    mediaBasePath = j["path"];

    for(int i = 0 ; i < j["media"].size() ; i++){
        Media media;
        media.setTitle(j["media"][i]["title"]);
        media.setPath(j["media"][i]["path"]);
        media.setFormat(j["media"][i]["format"]);
        media.setEpisodes(j["media"][i]["episodes"]);

        for(int k = 0 ; k < j["media"][i]["seasons"].size() ; k++ ) {
            media.putEpisodeXSeason(j["media"][i]["seasons"][k]["season"], j["media"][i]["seasons"][k]["episodes"]);
        }
        mediaDatabase.push_back(media);
    }
}

/*
 * A RESTART request needs to parse the save.JSON file and to update the current status of VlcManager
 *
 */
std::pair<std::string, uint64_t> DatabaseManager::resumePlaying(CurrentStatus *cs){

    json j;

    std::ifstream file("LastState.json");

    j = json::parse(file);


    cs->current_media = DatabaseManager::getMediafromString(j["status"]["last_title"]);
    cs->episode = j["status"]["last_episode"];
    cs->season = j["status"]["last_season"];
    uint64_t time = j["status"]["stopped_time"];

    std::string path;

    if(cs->current_media != nullptr)
        path = mediaBasePath + "/" + cs->current_media->getPath() + "/" + std::to_string(cs->season) + "/" +
               cs->current_media->getTitle() + "S" + std::to_string(cs->season) + "E" +
               std::to_string(cs->episode) + cs->current_media->getFormat();

    else
        path = "";


    return std::make_pair(path,time);


}

/*
 * When the user wants to RESTART, we only have a title to search into the media's vector
 */
Media DatabaseManager::getMediafromString(const std::string& title){

    for(const auto& media : mediaDatabase){
        if (media.getTitle() == title)
            return media;
    }

    return new Media();

}

/*
 * On a NEXT or PREVIOUS command we do not have any information about what the user wants to play
 * so in order to fulfill in any case the request this is what happens:
 *
 * (PREVIOUS)
 * - If we are on the first episode of the first season:
 *      Go to the last episode of the last season
 *
 * - If we are the first episode of a middle season:
 *      Go to the last episode of the previous season
 *
 * - Default:
 *      Go to the previous episode
 *
 * (NEXT)
 *
 * - If we are on the last episode of the last season:
 *      Go to the first episode of the first season
 *
 * - If we are at the last episode of a middle season:
 *      Go to the first episode of the next season
 *
 * - Default:
 *      Go to the next episode
 *
 */
const std::string DatabaseManager::calculateNextMedia(CurrentStatus *cs) {

    int episode_in_season = cs->current_media.getEpisodeXSeason()[cs->season-1].second;
    int seasons = cs->current_media.getEpisodeXSeason().size();

    //if I'm at the last episode a middle season
    if(cs->episode == episode_in_season && cs->season < seasons){
        cs->episode = 1;
        cs->season++;
    }//if I'm at the last episode of the last season
    else if(cs->episode == episode_in_season && cs->season == seasons){
        cs->season = 1;
        cs->episode = 1;
    }else//if I'media at whatever episode of a season
        cs->episode++;

    //Return the right path
    return mediaBasePath + "/" + cs->current_media.getPath() + "/" + std::to_string(cs->season) + "/" +
           cs->current_media.getTitle() + "S" + std::to_string(cs->season) + "E" +
           std::to_string(cs->episode) + cs->current_media.getFormat();

}

const std::string DatabaseManager::calculatePreviousMedia(CurrentStatus *cs) {

    int episode_in_season = cs->current_media.getEpisodeXSeason()[cs->season-1].second;
    int seasons = cs->current_media.getEpisodeXSeason().size();

    //if I'm at the first episode of a middle season
    if (cs->episode == 1 && cs->season != 1) {
        cs->season--;
        cs->episode = cs->current_media.getEpisodeXSeason()[cs->season-1].second;
    }//if I'm at the first episode of the first season
    else if(cs->episode == 1 && cs->season == 1){
        cs->season = seasons;
        cs->episode = cs->current_media.getEpisodeXSeason()[cs->season-1].second;
    }else//if I'm at whatever episode of a season
        cs->episode--;


    //Return the right path
    return mediaBasePath + "/" + cs->current_media.getPath() + "/" + std::to_string(cs->season) + "/" +
           cs->current_media.getTitle() + "S" + std::to_string(cs->season) + "E" +
           std::to_string(cs->episode) + cs->current_media.getFormat();

}


/*This function calculate the episode that you want to play
 * IFTTT on google assistants permits only 1 number and 1 string, so the message can be:
 *
 * PLAY THE 138 EPISODE OF SAILOR MOON
 *
 * this calculate in which season is the 138 episode an streams it.
 *
 *                      -OR-
 *
 * PLAY THE SEASON 1 OF SAILOR MOON
 *
 * this function returns the first episode of the selected season 1.
 *
 */
std::string DatabaseManager::calculateRequestedMedia(CurrentStatus *cs, const CommandMessage &message, const Media& media) {

    //If is specified the episode but not the season
    if(message.getSeason() == 0){
        int season = 0;
        int episode = 0;

        if(message.getEpisode() > media.getEpisodes())
            return "";

        else if(message.getEpisode() == 1){
            season = 1;
            episode = 1;
        }

        else if(message.getEpisode() == media.getEpisodes()){
            season = media.getEpisodeXSeason().size();
            episode = media.getEpisodeXSeason()[media.getEpisodeXSeason().size()-1].second;
        }

        else{

            auto seasons = media.getEpisodeXSeason();
            int sum = 0;

            for(auto episodesInSeason : seasons){

                sum += episodesInSeason.second;

                //if our episode is less than this sum, means that the episode is in this season
                if(sum >= message.getEpisode())
                    break;

                //else is in the next season
                season++;
            }

            // #episode - the summary of the previous episode * + the episode in that season give us
            // the right episode number
            episode = message.getEpisode() - sum + seasons[season].second;

            season++;
        }

        cs->setEpisode(episode);
        cs->setSeason(season);
    }
    else{
        cs->setEpisode(1);
        cs->setSeason(message.getSeason());
    }

    return mediaBasePath + "/" + media.getPath() + "/" + std::to_string(cs->getSeason()) + "/" + media.getTitle() + "S"
           + std::to_string(cs->getSeason()) + "E" + std::to_string(cs->getEpisode()) + media.getFormat();
}





