//
// Created by kalos on 25/04/19.
//

#include "VlcManager.h"
#include "../database/DatabaseManager.h"

using json = nlohmann::json;

VlcManager::VlcManager() {
    state = StateMachine::State::STATE_STOP;
    currentStatus.setInstance(libvlc_new(0, nullptr));
    database = DatabaseManager::getDatabaseInstance();
    concurrencyQueue = ConcurrencyQueue::getInstance();
}


/*
 * The main function that handles all messages and sends commands to VLC
 *
 * */
void VlcManager::controller() {

    while(true) {

        std::unique_ptr<CommandMessage> message;

        message = concurrencyQueue->readMessage();

        if((state = StateMachine::changeState(state, message->getCommand())) == StateMachine::State::EXCEPTION) {
            CommandResponse response(StateMachine::Result::ERROR, "Command is not permitted in the current status");
            concurrencyQueue->writeResponse(response);
        }
        else {
            //catch all the possible exception (not the best way however but VLC does not use exceptions)
            try {

                switch (message->getCommand()) {

                    case StateMachine::PLAY:
                        Play(*(message.get()));
                        break;
                    case StateMachine::PAUSE:
                        Pause();
                        break;
                    case StateMachine::STOP:
                        Stop();
                        break;
                    case StateMachine::NEXT:
                        Next();
                        break;
                    case StateMachine::PREVIOUS:
                        Previuos();
                        break;
                    case StateMachine::TIME:
                        goToTime(*(message.get()));
                        break;
                    case StateMachine::PERCENTAGE:
                        goToPercentage(*(message.get()));
                        break;
                    case StateMachine::DESTROY:
                        Stop();
                        return;
                    case StateMachine::RESUME:
                        Resume();
                        break;
                    case StateMachine::RESTART:
                        Restart();
                        break;
                }


            }
            catch (const NotFoundException &nfe) {
                CommandResponse response(StateMachine::Result::ERROR, "Command " + StateMachine::fromCommandToString(
                        message->getCommand()) + " Failed"+"\n");

                StateMachine::changeState(state, StateMachine::Command::STOP);

                if (currentStatus.getMediaPlayer() != nullptr) {
                    libvlc_media_player_stop(currentStatus.getMediaPlayer());
                    libvlc_media_player_release(currentStatus.getMediaPlayer());
                }

                concurrencyQueue->writeResponse(response);
            }
        }
    }
}

void VlcManager::Play(const CommandMessage &message){

    if (currentStatus.getMediaPlayer() != nullptr)
        libvlc_media_player_release(currentStatus.getMediaPlayer());

    Media media = database->getMediafromString(message.getTitle());

    if (media.getTitle().empty())
        throw NotFoundException();

    currentStatus.setCurrentMedia(media);
    std::string episode_path = database->calculateRequestedMedia(&currentStatus, message, media);

    if (episode_path.empty())
        throw NotFoundException();

    currentStatus.setMedia(libvlc_media_new_path(currentStatus.getInstance(), (episode_path).c_str()));
    currentStatus.setMediaPlayer(libvlc_media_player_new_from_media(currentStatus.getMedia()));

    libvlc_media_player_play(currentStatus.getMediaPlayer());

    //set the volume for debugging reason to 0
    libvlc_audio_set_volume(currentStatus.getMediaPlayer(), 100);

    libvlc_set_fullscreen(currentStatus.getMediaPlayer(), true);
    CommandResponse response(StateMachine::Result::SUCCESS,
                 "Now playing: " + message.getTitle() + " Episode: " + std::to_string(currentStatus.getEpisode()));

    concurrencyQueue->writeResponse(response);
}

void VlcManager::Pause() {

    libvlc_media_player_pause(currentStatus.getMediaPlayer());
    CommandResponse response(StateMachine::Result::SUCCESS, "Video Paused");
    concurrencyQueue->writeResponse(response);
}

void VlcManager::Stop() {

    libvlc_media_player_pause(currentStatus.getMediaPlayer());
    auto time = libvlc_media_player_get_time(currentStatus.getMediaPlayer());
    currentStatus.saveCurrentStatus(time);

    libvlc_media_player_stop(currentStatus.getMediaPlayer());

    CommandResponse response(StateMachine::Result::SUCCESS, "Video Stopped");
    concurrencyQueue->writeResponse(response);
}

void VlcManager::Next() {

    libvlc_media_player_stop(currentStatus.getMediaPlayer());

    const std::string media_path = database->calculateNextMedia(&currentStatus);

    currentStatus.setMedia(libvlc_media_new_path(currentStatus.getInstance(), media_path.c_str()));
    currentStatus.setMediaPlayer(libvlc_media_player_new_from_media(currentStatus.getMedia()));

    libvlc_media_player_play(currentStatus.getMediaPlayer());

    //debugging
    //libvlc_audio_set_volume(currentStatus.getMediaPlayer(), 0);

    libvlc_set_fullscreen(currentStatus.getMediaPlayer(), true);

    CommandResponse response(StateMachine::Result::SUCCESS, "Next video is played");
    concurrencyQueue->writeResponse(response);
}

void VlcManager::Previuos() {

    libvlc_media_player_stop(currentStatus.getMediaPlayer());

    const std::string media_path = database->calculatePreviousMedia(&currentStatus);

    currentStatus.setMedia(libvlc_media_new_path(currentStatus.getInstance(), media_path.c_str()));
    currentStatus.setMediaPlayer(libvlc_media_player_new_from_media(currentStatus.getMedia()));

    libvlc_media_player_play(currentStatus.getMediaPlayer());

    //debugging
    //libvlc_audio_set_volume(currentStatus.getMediaPlayer(), 0);

    libvlc_set_fullscreen(currentStatus.getMediaPlayer(), true);

    CommandResponse response(StateMachine::Result::SUCCESS, "Previous video is played");
    concurrencyQueue->writeResponse(response);

}

void VlcManager::goToTime(const CommandMessage &message) {
    auto time = message.getTime();
    time = convertInMilliseconds(time);
    libvlc_media_player_set_time(currentStatus.getMediaPlayer(), time.second);
    CommandResponse response(StateMachine::Result::SUCCESS, "Video moved to" + std::to_string(time.second) + " ms");
    concurrencyQueue->writeResponse(response);
}

void VlcManager::goToPercentage(const CommandMessage &message) {
    auto time = message.getTime();
    libvlc_media_player_set_position(currentStatus.getMediaPlayer(), (float_t)time.second/100);
    CommandResponse response(StateMachine::Result::SUCCESS, "Percentage set at " +
                                std::to_string((float_t) time.second/100) + "%");
    concurrencyQueue->writeResponse(response);
}

void VlcManager::Restart() {

    std::pair<std::string, uint64_t> details = database->resumePlaying(&currentStatus);

    if (details.first.empty())
        throw NotFoundException();

    currentStatus.setMedia(libvlc_media_new_path(currentStatus.getInstance(), (details.first).c_str()));
    currentStatus.setMediaPlayer(libvlc_media_player_new_from_media(currentStatus.getMedia()));

    libvlc_media_player_set_time(currentStatus.getMediaPlayer(), details.second);

    //set the volume for debugging reason to 0
    //libvlc_audio_set_volume(currentStatus.getMediaPlayer(), 0);
    libvlc_set_fullscreen(currentStatus.getMediaPlayer(), true);

    CommandResponse response(StateMachine::Result::SUCCESS,
                             "Now playing: " + currentStatus.getCurrentMedia().getTitle() + " Episode:" +
                                                                std::to_string(currentStatus.getEpisode()));
    concurrencyQueue->writeResponse(response);
}

void VlcManager::Resume() {
    libvlc_media_player_play(currentStatus.getMediaPlayer());

    CommandResponse response(StateMachine::Result::SUCCESS, "Video resumed");
    concurrencyQueue->writeResponse(response);
}
