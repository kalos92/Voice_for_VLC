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

std::vector<Media> medias;

using json = nlohmann::json;

void vlc_manager::controller(const Costants& k) {

    Current_status cs;
    // load the vlc engine
    cs.inst = libvlc_new(0, nullptr);
    //initial status
    Status state = S_STOP;
    //creating the DB based on the Json
    vlc_manager::parse_json();

    while(true) {
        std::unique_ptr<Message> msg;
        synch_queue *sq = synch_queue::get_instance();
        msg = sq->read_message();

        if(msg->getCommand() == DESTROY) {
            if(State_Machine::change_status(state, msg->getCommand()) == EXCEPTION) {
                Response res(ERROR, "L'azione richiesta non è permessa");
                sq->write_response(res);
            }

            vlc_manager::save_current_status();
            return;
        }

        if(msg->getCommand() == PLAY)
        {
            if(State_Machine::change_status(state, msg->getCommand()) == EXCEPTION) {
                Response res(ERROR, "L'azione richiesta non è permessa");
                sq->write_response(res);
            }
            else {

                try {
                    if (!cs.paused || !msg->getTitle().empty()) {
                        if (cs.mp != nullptr)
                            libvlc_media_player_release(cs.mp);

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

                        Response res(SUCCESS, "Now playing: " + msg->getTitle());
                        sq->write_response(res);


                    } else {
                        cs.paused = false;
                        libvlc_media_player_play(cs.mp);
                    }

                } catch (...) {
                    Response res(ERROR, "Qualcosa e' andato storto nel comando Play");
                    sq->write_response(res);
                }
            }
        }

        else if(msg->getCommand() == NEXT)
        {
            try{
                if(libvlc_media_player_is_playing(cs.mp) || cs.paused)
                {

                    libvlc_media_player_stop(cs.mp);

                    const std::string media_path = calculate_next_or_previous(&cs, msg.get(), true, k);
                    cs.m = libvlc_media_new_path(cs.inst, media_path.c_str());

                    cs.mp = libvlc_media_player_new_from_media(cs.m);

                    libvlc_media_release(cs.m);
                    // play the media_player
                    libvlc_media_player_play(cs.mp);
                    libvlc_audio_set_volume(cs.mp, 0);
                    std::cout << "next" << std::endl;
                    Response res(SUCCESS, "Impostato il video successivo");
                    sq->write_response(res);
                }
                else{
                    Response res(ERROR, "Non c'e' nulla in riproduzione, impossibile andare avanti");
                    sq->write_response(res);
                }
            }catch(...){
                Response res(ERROR, "Qualcosa e' andato storto nel comando NEXT");
                sq->write_response(res);
            }


        }

        else if(msg->getCommand() == PREVIOUS )
        {
            try {
                if (libvlc_media_player_is_playing(cs.mp) || cs.paused) {

                    libvlc_media_player_stop(cs.mp);

                    const std::string media_path = calculate_next_or_previous(&cs, msg.get(), false, k);
                    cs.m = libvlc_media_new_path(cs.inst, media_path.c_str());

                    cs.mp = libvlc_media_player_new_from_media(cs.m);

                    libvlc_media_release(cs.m);
                    // play the media_player
                    libvlc_media_player_play(cs.mp);
                    libvlc_audio_set_volume(cs.mp, 0);
                    std::cout << "previous" << std::endl;
                    Response res(SUCCESS, "Impostato il video precendente");
                    sq->write_response(res);

                } else{
                    Response res(ERROR, "Non c'e' nulla in riproduzione, impossibile andare indietro");
                    sq->write_response(res);
                }
            }catch(...){
                Response res(ERROR, "Qualcosa e' andato storto nel comando PREVIOUS");
                sq->write_response(res);
            }
        }
        else if(msg->getCommand() == FF)
        {
            try {
                if (libvlc_media_player_is_playing(cs.mp) || cs.paused) {
                    auto time = (libvlc_time_t) msg->getTime();
                    libvlc_media_player_set_time(cs.mp, time);
                    Response res(SUCCESS, "Video mandato avanti");
                    sq->write_response(res);

                } else{
                    Response res(ERROR, "Non c'e' nulla in riproduzione, impossibile andare indietro");
                    sq->write_response(res);
                }
            }catch(...){
                Response res(ERROR, "Qualcosa e' andato storto nel comando FF");
                sq->write_response(res);
            }
        }
        else if(msg->getCommand() == REW )
        {
            try {
                if (libvlc_media_player_is_playing(cs.mp) || cs.paused) {
                    auto time = (libvlc_time_t) msg->getTime();
                    libvlc_media_player_set_time(cs.mp, time);
                    Response res(SUCCESS, "Video mandato indietro");
                    sq->write_response(res);

                } else{
                    Response res(ERROR, "Non c'e' nulla in riproduzione, impossibile andare indietro");
                    sq->write_response(res);
                }
            }catch(...){
                Response res(ERROR, "Qualcosa e' andato storto nel comando REW");
                sq->write_response(res);
            }
        }
        else if(msg->getCommand() == PAUSE )
        {
            try {
                if (libvlc_media_player_is_playing(cs.mp) || cs.paused) {
                    libvlc_media_player_pause(cs.mp);
                    cs.paused = true;
                    Response res(SUCCESS, "Video messo in pausa");
                    sq->write_response(res);

                } else{
                    Response res(ERROR, "Non c'e' nulla in riproduzione, impossibile mettere in pausa");
                    sq->write_response(res);
                }
            }catch(...){
                Response res(ERROR, "Qualcosa e' andato storto nel comando PAUSA");
                sq->write_response(res);
            }
        }
        else if(msg->getCommand() == STOP )
        {
            try {
                if (libvlc_media_player_is_playing(cs.mp) || cs.paused) {
                    libvlc_media_player_stop(cs.mp);
                    Response res(SUCCESS, "Video messo stoppato");
                    sq->write_response(res);

                } else{
                    Response res(ERROR, "Non c'e' nulla in riproduzione, impossibile mettere in stop");
                    sq->write_response(res);
                }
            }catch(...){
                Response res(ERROR, "Qualcosa e' andato storto nel comando STOP");
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

bool vlc_manager::search_a_media(Current_status *cs, Message *msg){

    auto it = std::find_if(medias.begin(), medias.end(), [&msg](Media const& item){
        return item.getTitle() == msg->getTitle();
    });

    if (it != medias.end()) {

        return true;
    }

    return false;

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


