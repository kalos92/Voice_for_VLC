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
#include "../player/CurrentStatus.h"

class DatabaseManager {

public:
        static DatabaseManager* getDatabaseInstance();
        std::pair<std::string, uint64_t> resumePlaying(CurrentStatus *cs);
        const std::string calculateNextMedia(CurrentStatus *cs);
        const std::string calculatePreviousMedia(CurrentStatus *cs);
        std::string calculateRequestedMedia(CurrentStatus *,const CommandMessage&, const Media&);
        Media getMediafromString(const std::string&);

private:
        DatabaseManager() = default;
        ~DatabaseManager() = default;
        void buildDatabaseFromJson();
        std::vector<Media> mediaDatabase;
        std::string mediaBasePath = "";
        static DatabaseManager *instance;
        static std::once_flag inited;
};


#endif //VOICE_FOR_VLC_DATABASEMANAGER_H
