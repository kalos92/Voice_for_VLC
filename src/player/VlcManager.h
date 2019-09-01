//
// Created by kalos on 25/04/19.
//

#ifndef VOICE_FOR_VLC_VLCMANAGER_H
#define VOICE_FOR_VLC_VLCMANAGER_H

#include <cstring>
#include <unistd.h>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include "../synchronization/ConcurrentQueue.h"
#include "../synchronization/Message.h"
#include "../database/Media.h"
#include "../utils/json.hpp"
#include "../exceptions/NotRunningException.h"
#include "../exceptions/NotFoundException.h"
#include "CurrentStatus.h"
#include "../database/DatabaseManager.h"
#include "../utils/Utils.cpp"



class VlcManager {
    public:
        VlcManager();
        ~VlcManager() = default;

        void controller();

private:

        void Play(const CommandMessage &);
        void Pause();
        void Stop();
        void Next();
        void Previous();
        void goToTime(const CommandMessage &);
        void goToPercentage(const CommandMessage &);
        void Restart();
        void Resume();
        CurrentStatus currentStatus;
        StateMachine::State state;
        DatabaseManager *database;
        ConcurrencyQueue *concurrencyQueue;

};


#endif //GOOGLE_ASSISTANT_FOR_VLC_VLC_MANAGER_H
