//
// Created by kalos on 25/04/19.
//

#include "vlc_manager.h"
#include <cstring>
#include <unistd.h>
#include <fstream>
#include "json/single_include/nlohmann/json.hpp"
#include "NotRunningException.h"
#include "NotFoundException.h"
#include <algorithm>
#include <iomanip>

//Global vector that maintains within all the video that are available
std::vector<Media> medias;

using json = nlohmann::json;
/*
 * The main function that handles all messages and sends commands to VLC
 *
 * */
void vlc_manager::controller(const Costants& k) {

    //New current status
    Current_status cs;

    // load the vlc engine
    cs.inst = libvlc_new(0, nullptr);

    //The application starts with in the STOP status (No video are played
    Status state = S_STOP;

    //creating the DB based on the Json so it can be consulted on demand
    vlc_manager::parse_json();

    //getting an instance of the synchronization Queue to get and put all messages
    synch_queue *sq = synch_queue::get_instance();

    //infinite loop to read/write messages
    while(true) {

        //A message, only one per time can handle it
        std::unique_ptr<Message> msg;

        //wait for a message
        msg = sq->read_message();

        //if the action is permitted
        if((state = State_Machine::change_status(state, msg->getCommand())) == EXCEPTION) {
            //Create an error response
            Response res(ERROR, "Action not permitted");
            //Write on the queue
            sq->write_response(res);
        }
        else {
            //catch all the possible exception (not the best way however but VLC does not use exceptions)
            try {
                //which command has send the user?
                switch (msg->getCommand()) {

                    case PLAY: {
                        //if you want to play another media while another is currently playing, this close the current VLC
                        //window
                        if (cs.mp != nullptr)
                            libvlc_media_player_release(cs.mp);

                        //searching for the requested media in the DB
                        Media *media = vlc_manager::search_media_from_title(msg->getTitle());

                        //no media is found, block this action
                        if (media == nullptr)
                            throw NotFoundException();

                        //calculate where is this media
                        std::string episode_path = vlc_manager::calculate_what_to_play(&cs, msg.get(), media, k);

                        //maybe you have requested something that do have such episode
                        if (episode_path.empty())
                            throw NotFoundException();

                        // create a new item
                        cs.m = libvlc_media_new_path(cs.inst, (episode_path).c_str());

                        // create a media play playing environment
                        cs.mp = libvlc_media_player_new_from_media(cs.m);

                        // no need to keep the media now
                        libvlc_media_release(cs.m);

                        // play the media_player
                        libvlc_media_player_play(cs.mp);

                        //set the volume for debugging reason to 0
                        libvlc_audio_set_volume(cs.mp, 50);

                        //go to fullscreen
                        libvlc_set_fullscreen(cs.mp, true);

                        //Create a success response
                        Response res(SUCCESS,
                                        "Now playing: " + msg->getTitle() + " Episode: " + std::to_string(cs.episode));
                        //Write on the queue
                        sq->write_response(res);
                    }
                        break;
                    case PAUSE: {
                        //put the player in pause
                        libvlc_media_player_pause(cs.mp);

                        //Create a success response
                        Response res(SUCCESS, "Video Paused");

                        //Write on the queue
                        sq->write_response(res);

                    }
                        break;
                    case STOP: {
                        //Put the player in pause
                        libvlc_media_player_pause(cs.mp);

                        //Get the current time of the video
                        auto time = libvlc_media_player_get_time(cs.mp);

                        //Save on the json
                        vlc_manager::save_current_status(cs, time);

                        //Stop the player
                        libvlc_media_player_stop(cs.mp);

                        //Create a success response
                        Response res(SUCCESS, "Video Stopped");

                        //Write on the queue
                        sq->write_response(res);
                    }
                        break;
                    case NEXT: {

                        //Stop the player
                        libvlc_media_player_stop(cs.mp);

                        //Next command comes without any indication, so we need a little bit of computing
                        //in order to know whats next
                        const std::string media_path = calculate_next_or_previous(&cs, true, k);

                        //create the new media
                        cs.m = libvlc_media_new_path(cs.inst, media_path.c_str());

                        //create a media play playing environment
                        cs.mp = libvlc_media_player_new_from_media(cs.m);

                        //no need to keep the media now
                        libvlc_media_release(cs.m);

                        // play the media_player
                        libvlc_media_player_play(cs.mp);

                        //debugging
                        libvlc_audio_set_volume(cs.mp, 0);

                        //Create a success response
                        Response res(SUCCESS, "Next video is played");

                        //Write on the queue
                        sq->write_response(res);


                    }
                        break;
                    case PREVIOUS: {
                        //same as the NEXT command
                        libvlc_media_player_stop(cs.mp);

                        const std::string media_path = calculate_next_or_previous(&cs, false, k);

                        cs.m = libvlc_media_new_path(cs.inst, media_path.c_str());

                        cs.mp = libvlc_media_player_new_from_media(cs.m);

                        libvlc_media_release(cs.m);

                        libvlc_media_player_play(cs.mp);

                        libvlc_audio_set_volume(cs.mp, 0);

                        Response res(SUCCESS, "Previous video is played");

                        sq->write_response(res);
                    }
                        break;
                    case TIME: {
                        //Getting the time from the message
                        auto time = msg->getTime();

                        //converting it into ms
                        time = vlc_manager::convert_to_ms(time);

                        //setting the time
                        libvlc_media_player_set_time(cs.mp, time.second);

                        //Create a success response
                        Response res(SUCCESS, "Video moved to" + std::to_string(time.second) + " ms");

                        //Write on the queue
                        sq->write_response(res);

                    }
                        break;

                    case PERCENTAGE: {
                        //getting the requested percentage
                        auto time = msg->getTime();

                        //moving the media time with a percentage between 0.0 and 1.0
                        libvlc_media_player_set_position(cs.mp, (float_t)time.second/100);

                        //Create a success response
                        Response res(SUCCESS, "Percentage set at " + std::to_string((float_t) time.second/100) + "%");

                        //Write on the queue
                        sq->write_response(res);

                    }
                        break;
                    case DESTROY: {
                        //Same as STOP but now this thread returns
                        libvlc_media_player_pause(cs.mp);

                        auto time = libvlc_media_player_get_time(cs.mp);

                        vlc_manager::save_current_status(cs, time);

                        Response res(SUCCESS, "Process killed");

                        sq->write_response(res);

                        return;
                    }
                    case RESUME: {
                        //simply play from where is was paused
                        libvlc_media_player_play(cs.mp);

                        //Create a success response
                        Response res(SUCCESS, "Video resumed");

                        //Write on the queue
                        sq->write_response(res);
                    }
                        break;
                    case RESTART: {

                        //getting the last media and where it was stopped
                        std::pair<std::string, uint64_t> details = vlc_manager::resume_from_save_state(k, &cs);

                        //if the media is not available block
                        if (details.first.empty())
                            throw NotFoundException();

                        // create a new item
                        cs.m = libvlc_media_new_path(cs.inst, (details.first).c_str());

                        // create a media play playing environment
                        cs.mp = libvlc_media_player_new_from_media(cs.m);

                        // no need to keep the media now
                        libvlc_media_release(cs.m);

                        // play the media_player
                        libvlc_media_player_play(cs.mp);

                        //restart from the last known status
                        libvlc_media_player_set_time(cs.mp, details.second);

                        //set the volume for debugging reason to 0
                        libvlc_audio_set_volume(cs.mp, 0);

                        //go to fullscreen
                        libvlc_set_fullscreen(cs.mp, true);
                        //Create a success response
                        Response res(SUCCESS,
                                     "Now playing: " + msg->getTitle() + " Episode:" + std::to_string(cs.episode));
                        //Write on the queue
                        sq->write_response(res);
                    }
                        break;
                }


            }
            catch (const NotFoundException &nfe) {
                //An exception has been caught write an error response
                Response res(ERROR, "Command " + State_Machine::command_to_string(msg->getCommand()) + " Failed"+"\n");

                //if any error set to to S_STOP status
                State_Machine::change_status(state, STOP);

                if (cs.mp != nullptr) {
                    //if any error, stop the player
                    libvlc_media_player_stop(cs.mp);

                    //release the counter
                    libvlc_media_player_release(cs.mp);
                }

                //Write on the queue
                sq->write_response(res);
            }
        }
    }
}

/*
 * Loads into the media vector all the parsed list.JSON file
 */
void vlc_manager::parse_json() {
    json j;

    std::ifstream file("list.json");

    j = json::parse(file);

    for(int i = 0 ; i < j["media"].size() ; i++){
        Media m;
        m.setTitle(j["media"][i]["title"]);
        m.setPath(j["media"][i]["path"]);
        m.setFormat(j["media"][i]["format"]);
        m.setEpisodes(j["media"][i]["episodes"]);


        for(int k = 0 ; k < j["media"][i]["seasons"].size() ; k++ ) {
            m.putEpisodeXSeason(j["media"][i]["seasons"][k]["season"],j["media"][i]["seasons"][k]["episodes"]);
        }
        medias.push_back(m);
    }
}


/*
 * When the user wants to RESTART, we only have a title to search into the media's vector
 */
Media* vlc_manager::search_media_from_title(std::string title){

    auto it = std::find_if(medias.begin(), medias.end(), [&title](Media const& item){
        return item.getTitle() == title;
    });

    if (it != medias.end()) {

        long index = std::distance(medias.begin(), it);
        return new Media(medias[index]);
    }

    return nullptr;

}

/*
 * A RESTART request needs to parse the save.JSON file and to update the current status of vlc_manager
 *
 */
std::pair<std::string, uint64_t> vlc_manager::resume_from_save_state(const Costants& k, Current_status *cs){

    json j;

    std::ifstream file("save.json");

    j = json::parse(file);


    cs->current_media = vlc_manager::search_media_from_title(j["status"]["last_title"]);
    cs->episode = j["status"]["last_episode"];
    cs->season = j["status"]["last_season"];
    uint64_t time = j["status"]["stopped_time"];

    std::string path;

    if(cs->current_media != nullptr)
        path = k.getPath() + "/" + cs->current_media->getPath() + "/" + std::to_string(cs->season) + "/" +
                                      cs->current_media->getTitle() + "S" + std::to_string(cs->season) + "E" +
                                      std::to_string(cs->episode) + cs->current_media->getFormat();

    else
        path = "";


    return std::make_pair(path,time);


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
const std::string vlc_manager::calculate_next_or_previous(Current_status *cs, bool next, const Costants &k) {

    int episode_in_season = cs->current_media->getEpisodeXSeason()[cs->season-1].second;
    int seasons = cs->current_media->getEpisodeXSeason().size();

    if(next){
        //if I'm at the last episode a middle season
       if(cs->episode == episode_in_season && cs->season < seasons){
           cs->episode = 1;
           cs->season++;
       }//if I'm at the last episode of the last season
       else if(cs->episode == episode_in_season && cs->season == seasons){
           cs->season = 1;
           cs->episode = 1;
       }else//if I'm at whatever episode of a season
            cs->episode++;


    }else{
        //if I'm at the first episode of a middle season
        if (cs->episode == 1 && cs->season != 1) {
            cs->season--;
            cs->episode = cs->current_media->getEpisodeXSeason()[cs->season-1].second;
        }//if I'm at the first episode of the first season
        else if(cs->episode == 1 && cs->season == 1){
            cs->season = seasons;
            cs->episode = cs->current_media->getEpisodeXSeason()[cs->season-1].second;
        }else//if I'm at whatever episode of a season
            cs->episode--;
    }

    //Return the right path
    return k.getPath() + "/" + cs->current_media->getPath() + "/" + std::to_string(cs->season) + "/" +
            cs->current_media->getTitle() + "S" + std::to_string(cs->season) + "E" +
            std::to_string(cs->episode) + cs->current_media->getFormat();

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
 std::string vlc_manager::calculate_what_to_play(Current_status *cs, Message *msg, const Media& media, const Costants& k) {

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
void vlc_manager::save_current_status(vlc_manager::Current_status cs, int64_t time) {

    json j;

    std::ofstream file("save.json");

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


