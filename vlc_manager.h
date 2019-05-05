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

        static void controller(const Costants& k);
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
        }Current_status;


        static void parse_json();
        static Media *search_media_from_title_and_update_current_media(Current_status *, Message *);
        static const std::string calculate_next_or_previous(Current_status *, Message *, bool, Costants);
        static std::string calculate_what_to_play(Message *, const Media& , Costants);
        static void save_current_status(Current_status, int64_t);
        static std::pair<std::string, uint64_t > resume_from_save_state(Costants, Current_status *);
        static Media *search_media_from_title(std::string title);
};


#endif //GOOGLE_ASSISTANT_FOR_VLC_VLC_MANAGER_H
