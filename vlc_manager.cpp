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

std::vector<Media> medias;

using json = nlohmann::json;
/*
 * The main function that handle all messages and sends commands to VLC
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

    //getting an istance of the Synch Queue to get and put all messages
    synch_queue *sq = synch_queue::get_instance();

    //infinite loop to read/write messages
    while(true) {


        std::unique_ptr<Message> msg;

        //wait for a message
        msg = sq->read_message();
        //if the action is permitted
        if((state = State_Machine::change_status(state, msg->getCommand())) == EXCEPTION) {
            Response res(ERROR, "Action not permitted");
            sq->write_response(res);

        }
        else {
            try {
                switch (msg->getCommand()) {

                    case PLAY: {
                        //if you want to play another media while another is currently playing, this close the current VLC
                        //window
                        if (cs.mp != nullptr)
                            libvlc_media_player_release(cs.mp);

                        //searching for the requested media in the DB
                        Media *media = vlc_manager::search_media_from_title_and_update_current_media(&cs, msg.get());

                        if (media == nullptr)
                            throw NotFoundException();

                        std::string episode_path = vlc_manager::calculate_what_to_play(msg.get(), media, k);

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
                        libvlc_audio_set_volume(cs.mp, 0);

                        //go to fullscreen
                        libvlc_set_fullscreen(cs.mp, true);

                        Response res(SUCCESS,
                                     "Now playing: " + msg->getTitle() + " Episode: " + std::to_string(cs.episode));

                        sq->write_response(res);
                    }
                        break;
                    case PAUSE: {

                        libvlc_media_player_pause(cs.mp);

                        Response res(SUCCESS, "Video Paused");

                        sq->write_response(res);

                    }
                        break;
                    case STOP: {

                        libvlc_media_player_pause(cs.mp);

                        auto time = libvlc_media_player_get_time(cs.mp);

                        vlc_manager::save_current_status(cs, time);

                        libvlc_media_player_stop(cs.mp);

                        Response res(SUCCESS, "Video Stopped");

                        sq->write_response(res);
                    }
                        break;
                    case NEXT: {

                        libvlc_media_player_stop(cs.mp);

                        const std::string media_path = calculate_next_or_previous(&cs, msg.get(), true, k);

                        cs.m = libvlc_media_new_path(cs.inst, media_path.c_str());

                        cs.mp = libvlc_media_player_new_from_media(cs.m);

                        libvlc_media_release(cs.m);
                        // play the media_player
                        libvlc_media_player_play(cs.mp);

                        libvlc_audio_set_volume(cs.mp, 0);

                        Response res(SUCCESS, "Next video is played");

                        sq->write_response(res);


                    }
                        break;

                    case PREVIOUS: {
                        const std::string media_path = calculate_next_or_previous(&cs, msg.get(), false, k);

                        cs.m = libvlc_media_new_path(cs.inst, media_path.c_str());

                        cs.mp = libvlc_media_player_new_from_media(cs.m);

                        libvlc_media_release(cs.m);
                        // play the media_player
                        libvlc_media_player_play(cs.mp);

                        libvlc_audio_set_volume(cs.mp, 0);

                        Response res(SUCCESS, "Previous video is played");

                        sq->write_response(res);
                    }
                        break;
                    case FF: {

                        auto time = (libvlc_time_t) msg->getTime();

                        libvlc_media_player_set_time(cs.mp, time);

                        Response res(SUCCESS, "Fast fowarded video of " + std::to_string(time) + "ms");

                        sq->write_response(res);

                    }
                        break;

                    case REW: {

                        auto time = (libvlc_time_t) msg->getTime();

                        libvlc_media_player_set_time(cs.mp, time);

                        Response res(SUCCESS, "Rewinded video of " + std::to_string(time) + "ms");

                        sq->write_response(res);

                    }
                        break;
                    case DESTROY: {

                        libvlc_media_player_pause(cs.mp);

                        auto time = libvlc_media_player_get_time(cs.mp);

                        vlc_manager::save_current_status(cs, time);

                        Response res(SUCCESS, "Process killed");

                        sq->write_response(res);

                        return;
                    }
                    case RESUME: {

                        libvlc_media_player_play(cs.mp);

                        Response res(SUCCESS, "Video resumed");

                        sq->write_response(res);
                    }
                        break;
                    case RESTART: {

                        std::pair<std::string, uint64_t> details = vlc_manager::resume_from_save_state(k, &cs);

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

                        Response res(SUCCESS,
                                     "Now playing: " + msg->getTitle() + " Episode:" + std::to_string(cs.episode));

                        sq->write_response(res);
                    }
                        break;
                }
            }
            catch (...) {
                Response res(ERROR, "Command " + State_Machine::command_to_string(msg->getCommand()) + " Failed");

                State_Machine::change_status(state, STOP);

                if (cs.mp != nullptr)
                    libvlc_media_player_release(cs.mp);

                sq->write_response(res);
            }
        }
    }
}

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


Media* vlc_manager::search_media_from_title_and_update_current_media(Current_status *cs, Message *msg){

    auto it = std::find_if(medias.begin(), medias.end(), [&msg](Media const& item){
        return item.getTitle() == msg->getTitle();
    });

    if (it != medias.end()) {

        long index = std::distance(medias.begin(), it);
        cs->current_media = new Media(medias[index]);
        cs->episode = msg->getEpisode();
        cs->season = msg->getSeason();
        return cs->current_media;
    }

    return nullptr;

}

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

std::pair<std::string, uint64_t> vlc_manager::resume_from_save_state(Costants k, Current_status *cs){

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


const std::string vlc_manager::calculate_next_or_previous(Current_status *cs, Message *msg, bool next, Costants k){

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
        }//if I'm at the first episode of the first seson
        else if(cs->episode == 1 && cs->season == 1){
            cs->season = seasons;
            cs->episode = cs->current_media->getEpisodeXSeason()[cs->season-1].second;
        }else//if I'm at whatever episode of a season
            cs->episode--;
    }


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
 */
 std::string vlc_manager::calculate_what_to_play(Message *msg, const Media& media, Costants k) {

    if(msg->getSeason() == 0){
        int season = 0;
        int episode = 0;

        if(msg->getEpisode() > media.getEpisodes())
            return "";
        else if(msg->getEpisode() == 1){
            season = 1;
            episode = 1;
        }
        else if(msg->getEpisode() == media.getEpisodes()){
            season = media.getEpisodeXSeason().size();
            episode = media.getEpisodeXSeason()[media.getEpisodeXSeason().size()-1].second;
        }
        else{

            auto exs = media.getEpisodeXSeason();
            int sum = 0;

            for( auto es : exs ){

                sum += es.second;

                if(sum >= msg->getEpisode())
                    break;

                season++;
            }

            episode = msg->getEpisode() - sum + exs[season].second;
            season++;
        }



        return k.getPath() + "/" +media.getPath() + "/" + std::to_string(season) + "/" + media.getTitle() + "S"
               + std::to_string(season) + "E" + std::to_string(episode) + media.getFormat();

    }
    else{
        return k.getPath() + "/" +media.getPath() + "/" + std::to_string(msg->getSeason()) + "/" + media.getTitle() + "S"
        + std::to_string(msg->getSeason()) + "E" + std::to_string(1) + media.getFormat();

    }
}

void vlc_manager::save_current_status(vlc_manager::Current_status cs, int64_t time) {

    json j;

    std::ofstream file("save.json");

    j["status"]["last_title"] = cs.current_media->getTitle();
    j["status"]["last_episode"] = cs.episode;
    j["status"]["last_season"] = cs.season;
    j["status"]["stopped_time"] = time;

    file << std::setw(4) << j << std::endl;

}


