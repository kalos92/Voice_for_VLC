//
// Created by kalos on 05/08/19.
//

#ifndef VOICE_FOR_VLC_DATABASEMANAGER_H
#define VOICE_FOR_VLC_DATABASEMANAGER_H

#include "../utils/json.hpp"
#include <vlc/vlc.h>
#include <cstring>
#include <unistd.h>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include "../synchronization/ConcurrentQueue.h"
#include "../player/VlcManager.h"
#include "../utils/json.hpp"
#include "../exceptions/NotRunningException.h"
#include "../exceptions/NotFoundException.h"
#include "Media.h"

class DatabaseManager {

public:
        static DatabaseManager* getDatabaseInstance();
        std::pair<std::string, uint64_t> resumePlaying(vlc_manager::CurrentStatus *cs);
        const std::string calculateNextMedia(vlc_manager::CurrentStatus *cs, bool next);
        static std::string calculate_what_to_play(CurrentStatus *, Message *, const Media& , const Costants&);
        static void save_current_status(CurrentStatus, int64_t);
        static std::pair<std::string, int64_t> convert_to_ms(const std::pair<std::string, int64_t>& pair);


private:
        DatabaseManager() = default;
        ~DatabaseManager() = default;

        void buildDatabaseFromJson();
        Media getMediafromString(const std::string&);

        std::vector<Media> mediaDatabase;
        std::string mediaBasePath = "";


        static DatabaseManager *instance;
        static std::once_flag inited;

};


#endif //VOICE_FOR_VLC_DATABASEMANAGER_H
