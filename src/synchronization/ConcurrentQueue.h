//
// Created by kalos on 25/04/19.
//

#ifndef GOOGLE_ASSISTANT_FOR_VLC_SYNCH_QUEUE_H
#define GOOGLE_ASSISTANT_FOR_VLC_SYNCH_QUEUE_H

#include <iostream>
#include <thread>
#include "Message.h"
#include <mutex>
#include <condition_variable>
#include <list>


class synch_queue {

    public:
    static synch_queue* get_instance();
    std::unique_ptr<Message> read_message();
    void write_message(const Message&);
    std::unique_ptr<Response> read_response();
    void write_response(const Response&);

    private:
        synch_queue();
        ~synch_queue()= default;
        std::mutex mutex_mex;
        std::condition_variable cv_mex;
        std::mutex mutex_res;
        std::condition_variable cv_res;
        std::list<Message> messages;
        std::list<Response> responses;
        bool is_running = false;
        static std::once_flag inited;
        static synch_queue *instance;
};


#endif //GOOGLE_ASSISTANT_FOR_VLC_SYNCH_QUEUE_H
