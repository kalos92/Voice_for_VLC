//
// Created by kalos on 13/08/19.
//

#ifndef VOICE_FOR_VLC_CURRENTSTATUS_H
#define VOICE_FOR_VLC_CURRENTSTATUS_H
#include <vlc/vlc.h>
#include <unistd.h>
#include <fstream>
#include <iomanip>
#include <unistd.h>
#include <fstream>
#include <iomanip>
#include "../database/Media.h"
#include "../utils/json.hpp"


class CurrentStatus {

public:

    CurrentStatus(){
        instance = nullptr;
        mediaPlayer = nullptr;
        media = nullptr;
    };

    ~CurrentStatus(){
        libvlc_release(instance);
        libvlc_media_player_release(mediaPlayer);
        libvlc_media_release(media);

        instance = nullptr;
        mediaPlayer = nullptr;
        media = nullptr;
    }

    libvlc_instance_t *getInstance() const;
    void setInstance(libvlc_instance_t *instance);
    libvlc_media_player_t *getMediaPlayer() const;
    void setMediaPlayer(libvlc_media_player_t *mediaPlayer);
    libvlc_media_t *getMedia() const;
    void setMedia(libvlc_media_t *media);
    const Media &getCurrentMedia() const;
    void setCurrentMedia(const Media &currentMedia);
    int getEpisode() const;
    void setEpisode(int episode);
    int getSeason() const;
    void setSeason(int season);
    void saveCurrentStatus(int64_t);

private:
    libvlc_instance_t *instance;
    libvlc_media_player_t *mediaPlayer;
    libvlc_media_t *media;
    Media current_media;
    int episode = 0 ;
    int season = 0;
};


#endif //VOICE_FOR_VLC_CURRENTSTATUS_H
