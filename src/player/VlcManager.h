//
// Created by kalos on 25/04/19.
//

#ifndef VOICE_FOR_VLC_VLCMANAGER_H
#define VOICE_FOR_VLC_VLCMANAGER_H


#include <vlc/vlc.h>
#include <cstring>
#include <unistd.h>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include "../synchronization/ConcurrentQueue.h"
#include "../database/Media.h"
#include "../utils/json.hpp"
#include "../exceptions/NotRunningException.h"
#include "../exceptions/NotFoundException.h"


class vlc_manager {
    public:
        vlc_manager()= default;
        ~vlc_manager()= default;

        typedef struct current_status{
            libvlc_instance_t *instance = nullptr ;
            libvlc_media_player_t *mediaPlayer = nullptr;
            libvlc_media_t *media = nullptr;
            Media current_media;
            int episode = 0 ;
            int season = 0;
        }CurrentStatus;

        void controller();

private:

};


#endif //GOOGLE_ASSISTANT_FOR_VLC_VLC_MANAGER_H
