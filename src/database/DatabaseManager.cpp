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
 * A RESTART request needs to parse the save.JSON file and to update the current status of vlc_manager
 *
 */
std::pair<std::string, uint64_t> DatabaseManager::resumePlaying( vlc_manager::CurrentStatus *cs){

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
const std::string DatabaseManager::calculateNextMedia(vlc_manager::CurrentStatus *cs, bool next) {

    int episode_in_season = cs->current_media.getEpisodeXSeason()[cs->season-1].second;
    int seasons = cs->current_media.getEpisodeXSeason().size();

    if(next){
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


    }else{
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
    }

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
std::string vlc_manager::calculate_what_to_play(CurrentStatus *cs, Message *msg, const Media& media, const Costants& k) {

    //If is specified the episode but not the season
    if(msg->getSeason() == 0){
        int season = 0;
        int episode = 0;

        //User has specified an episode that do not exists
        if(msg->getEpisode() > media.getEpisodes())
            return "";

            //first episode of first season, do not lose time
        else if(msg->getEpisode() == 1){
            season = 1;
            episode = 1;
        }

            //last episode of last season, do not lose time
        else if(msg->getEpisode() == media.getEpisodes()){
            season = media.getEpisodeXSeason().size();
            episode = media.getEpisodeXSeason()[media.getEpisodeXSeason().size()-1].second;
        }

            //calculate
        else{

            auto exs = media.getEpisodeXSeason();
            int sum = 0;

            //Adding episodes while our episode is greater than the sum of the season episode
            for( auto es : exs ){

                sum += es.second;

                //if our episode is less than this sum, means that the episode is in this season
                if(sum >= msg->getEpisode())
                    break;

                //else is in the next season
                season++;
            }

            // #episode - the summary of the previous episode * + the episode in that season give us
            // the right episode number
            episode = msg->getEpisode() - sum + exs[season].second;

            //index from computer notation to human notation
            season++;
        }

        //update the current status
        cs->episode = episode;
        cs->season = season;

        //return the right path
        return k.getPath() + "/" +media.getPath() + "/" + std::to_string(season) + "/" + media.getTitle() + "S"
               + std::to_string(season) + "E" + std::to_string(episode) + media.getFormat();

    }
        //The season is specified, so first episode of the selected season
    else{

        //update the current status
        cs->episode = 1;
        cs->season = msg->getSeason();

        //return the right path
        return k.getPath() + "/" +media.getPath() + "/" + std::to_string(msg->getSeason()) + "/" + media.getTitle() + "S"
               + std::to_string(msg->getSeason()) + "E" + std::to_string(1) + media.getFormat();

    }
}

/*
 * This function save the the current state in case of STOP or DESTROY
 * in order to allow the use of the RESTART command
 */
void vlc_manager::save_current_status(vlc_manager::CurrentStatus cs, int64_t time) {

    json j;

    std::ofstream file("LastState.json");

    j["status"]["last_title"] = cs.current_media->getTitle();
    j["status"]["last_episode"] = cs.episode;
    j["status"]["last_season"] = cs.season;
    j["status"]["stopped_time"] = time;

    file << std::setw(4) << j << std::endl;

}

/*
 * From hours, minutes, seconds to milliseconds that libvlc_media_player_set_time needs
 */
std::pair<std::string, int64_t> vlc_manager::convert_to_ms(const std::pair<std::string, int64_t>& pair) {

    if(pair.first == "seconds")
        return std::make_pair("seconds", pair.second*1000);

    if(pair.first == "minutes")
        return std::make_pair("minutes", pair.second*60*1000);

    if(pair.first == "hours")
        return std::make_pair("seconds", pair.second*60*60*1000);

    if(pair.first == "none")
        return pair;
}

