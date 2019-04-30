//
// Created by kalos on 25/04/19.
//

#ifndef GOOGLE_ASSISTANT_FOR_VLC_VLC_MANAGER_H
#define GOOGLE_ASSISTANT_FOR_VLC_VLC_MANAGER_H

#include "synch_queue.h"
#include "media.h"
#include <vlc/vlc.h>

class vlc_manager {
    public:

        static void controller();
        vlc_manager()= default;
        ~vlc_manager()= default;

    private:

        typedef struct current_status{
            libvlc_instance_t *inst = nullptr ;
            libvlc_media_player_t *mp = nullptr;
            libvlc_media_t *m = nullptr;
            Media *current_media = nullptr;
            int episode = 0 ;
            int season = 0;
            bool paused = false;
        }Current_status;

        static void parse_json();
        static bool update_current_media(Current_status *cs, Message *msg);
        static const std::string calculate_season_and_episode(Current_status *cs, Message *msg, bool next);
};


#endif //GOOGLE_ASSISTANT_FOR_VLC_VLC_MANAGER_H
