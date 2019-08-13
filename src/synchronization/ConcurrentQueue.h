//
// Created by kalos on 25/04/19.
//

#ifndef VOICE_FOR_VLC_CONCURRENTQUEUE_H
#define VOICE_FOR_VLC_CONCURRENTQUEUE_H

#include <iostream>
#include <thread>
#include "Message.h"
#include <mutex>
#include <condition_variable>
#include <list>
#include "../exceptions/NotRunningException.h"


class ConcurrencyQueue {

    public:
    static ConcurrencyQueue* getInstance();
    std::unique_ptr<CommandMessage> readMessage();
    void writeMessage(const CommandMessage&);
    std::unique_ptr<CommandResponse> readResponse();
    void writeResponse(const CommandResponse&);

    private:
        ConcurrencyQueue();
        ~ConcurrencyQueue()= default;
        std::mutex mutex_mex;
        std::condition_variable cv_mex;
        std::mutex mutex_res;
        std::condition_variable cv_res;
        std::list<CommandMessage> messages;
        std::list<CommandResponse> responses;
        bool is_running = false;
        static std::once_flag inited;
        static ConcurrencyQueue *instance;
};


#endif //GOOGLE_ASSISTANT_FOR_VLC_SYNCH_QUEUE_H
