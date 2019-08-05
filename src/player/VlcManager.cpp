//
// Created by kalos on 25/04/19.
//

#include "VlcManager.h"

using json = nlohmann::json;
/*
 * The main function that handles all messages and sends commands to VLC
 *
 * */
void vlc_manager::controller() {

    //New current status
    CurrentStatus cs;

    // load the vlc engine
    cs.instance = libvlc_new(0, nullptr);

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
                        if (cs.mediaPlayer != nullptr)
                            libvlc_media_player_release(cs.mediaPlayer);

                        //searching for the requested media in the DB
                        Media *media = vlc_manager::search_media_from_title(msg->getTitle());

                        //no media is found, block this action
                        if (media == nullptr)
                            throw NotFoundException();

                        //insert media into the current status
                        cs.current_media = media;

                        //calculate where is this media
                        std::string episode_path = vlc_manager::calculate_what_to_play(&cs, msg.get(), media, k);

                        //maybe you have requested something that do have such episode
                        if (episode_path.empty())
                            throw NotFoundException();

                        // create a new item
                        cs.media = libvlc_media_new_path(cs.instance, (episode_path).c_str());

                        // create a media play playing environment
                        cs.mediaPlayer = libvlc_media_player_new_from_media(cs.media);

                        // no need to keep the media now
                        libvlc_media_release(cs.media);

                        // play the media_player
                        libvlc_media_player_play(cs.mediaPlayer);

                        //set the volume for debugging reason to 0
                        libvlc_audio_set_volume(cs.mediaPlayer, 100);

                        //go to fullscreen
                        libvlc_set_fullscreen(cs.mediaPlayer, true);

                        //Create a success response
                        Response res(SUCCESS,
                                        "Now playing: " + msg->getTitle() + " Episode: " + std::to_string(cs.episode));
                        //Write on the queue
                        sq->write_response(res);
                    }
                        break;
                    case PAUSE: {
                        //put the player in pause
                        libvlc_media_player_pause(cs.mediaPlayer);

                        //Create a success response
                        Response res(SUCCESS, "Video Paused");

                        //Write on the queue
                        sq->write_response(res);

                    }
                        break;
                    case STOP: {
                        //Put the player in pause
                        libvlc_media_player_pause(cs.mediaPlayer);

                        //Get the current time of the video
                        auto time = libvlc_media_player_get_time(cs.mediaPlayer);

                        //Save on the json
                        vlc_manager::save_current_status(cs, time);

                        //Stop the player
                        libvlc_media_player_stop(cs.mediaPlayer);

                        //Create a success response
                        Response res(SUCCESS, "Video Stopped");

                        //Write on the queue
                        sq->write_response(res);
                    }
                        break;
                    case NEXT: {

                        //Stop the player
                        libvlc_media_player_stop(cs.mediaPlayer);

                        //Next command comes without any indication, so we need a little bit of computing
                        //in order to know whats next
                        const std::string media_path = calculate_next_or_previous(&cs, true, k);

                        //create the new media
                        cs.media = libvlc_media_new_path(cs.instance, media_path.c_str());

                        //create a media play playing environment
                        cs.mediaPlayer = libvlc_media_player_new_from_media(cs.media);

                        //no need to keep the media now
                        libvlc_media_release(cs.media);

                        // play the media_player
                        libvlc_media_player_play(cs.mediaPlayer);

                        //debugging
                        //libvlc_audio_set_volume(cs.mediaPlayer, 0);

                        //go to fullscreen
                        libvlc_set_fullscreen(cs.mediaPlayer, true);

                        //Create a success response
                        Response res(SUCCESS, "Next video is played");

                        //Write on the queue
                        sq->write_response(res);


                    }
                        break;
                    case PREVIOUS: {
                        //same as the NEXT command
                        libvlc_media_player_stop(cs.mediaPlayer);

                        const std::string media_path = calculate_next_or_previous(&cs, false, k);

                        cs.media = libvlc_media_new_path(cs.instance, media_path.c_str());

                        cs.mediaPlayer = libvlc_media_player_new_from_media(cs.media);

                        libvlc_media_release(cs.media);

                        libvlc_media_player_play(cs.mediaPlayer);

                        //libvlc_audio_set_volume(cs.mediaPlayer, 0);

                        //go to fullscreen
                        libvlc_set_fullscreen(cs.mediaPlayer, true);

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
                        libvlc_media_player_set_time(cs.mediaPlayer, time.second);

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
                        libvlc_media_player_set_position(cs.mediaPlayer, (float_t)time.second/100);

                        //Create a success response
                        Response res(SUCCESS, "Percentage set at " + std::to_string((float_t) time.second/100) + "%");

                        //Write on the queue
                        sq->write_response(res);

                    }
                        break;
                    case DESTROY: {
                        //Same as STOP but now this thread returns
                        libvlc_media_player_pause(cs.mediaPlayer);

                        auto time = libvlc_media_player_get_time(cs.mediaPlayer);

                        vlc_manager::save_current_status(cs, time);

                        Response res(SUCCESS, "Process killed");

                        sq->write_response(res);

                        return;
                    }
                    case RESUME: {
                        //simply play from where is was paused
                        libvlc_media_player_play(cs.mediaPlayer);

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
                        cs.media = libvlc_media_new_path(cs.instance, (details.first).c_str());

                        // create a media play playing environment
                        cs.mediaPlayer = libvlc_media_player_new_from_media(cs.media);

                        // no need to keep the media now
                        libvlc_media_release(cs.media);

                        // play the media_player
                        libvlc_media_player_play(cs.mediaPlayer);

                        //restart from the last known status
                        libvlc_media_player_set_time(cs.mediaPlayer, details.second);

                        //set the volume for debugging reason to 0
                        //libvlc_audio_set_volume(cs.mediaPlayer, 0);

                        //go to fullscreen
                        libvlc_set_fullscreen(cs.mediaPlayer, true);
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

                if (cs.mediaPlayer != nullptr) {
                    //if any error, stop the player
                    libvlc_media_player_stop(cs.mediaPlayer);

                    //release the counter
                    libvlc_media_player_release(cs.mediaPlayer);
                }

                //Write on the queue
                sq->write_response(res);
            }
        }
    }
}









