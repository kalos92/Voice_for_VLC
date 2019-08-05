//
// Created by kalos on 25/04/19.
//

#include "ConcurrentQueue.h"
#include "NotRunningException.h"
#include <mutex>

std::once_flag synch_queue::inited;
synch_queue *synch_queue::instance;

void synch_queue::write_message(const Message& mex) {

    if(!is_running)
        throw NotRunningException();

    std::lock_guard<std::mutex> lock(this->mutex_mex);

    this->messages.push_back(mex);

    this->cv_mex.notify_one();
}

void synch_queue::write_response(const Response& res) {

    if(!is_running)
        throw NotRunningException();

    std::lock_guard<std::mutex> lock(this->mutex_res);

    this->responses.push_back(res);

    this->cv_res.notify_all();
}

std::unique_ptr<Message> synch_queue::read_message() {

    if(!is_running)
        throw NotRunningException();

    Message mex;
    while(true){
        std::unique_lock<std::mutex> lock(this->mutex_mex);

        while(messages.empty())
            this->cv_mex.wait(lock);

        if(messages.empty())
            continue;

        mex = this->messages.front();
        std::cout << mex.getCommand() << std::endl;
        this->messages.pop_front();

//        if(mex.getCommand() == DESTROY) {
//            while (!messages.empty()) {
//                this->messages.pop_front();
//            }
//            this->is_running = false;
//        }
       // else
            std::cout << mex.getCommand() << std::endl;

        std::unique_ptr<Message> pointer( new Message(mex) );
        return pointer;
    }

}

std::unique_ptr<Response> synch_queue::read_response() {

    if(!is_running)
        throw NotRunningException();

    Response res;
    while(true){
        std::unique_lock<std::mutex> lock(this->mutex_res);

        while(responses.empty())
            this->cv_res.wait(lock);

        if(responses.empty())
            continue;

        res = this->responses.front();
        this->responses.pop_front();

        std::unique_ptr<Response> pointer( new Response(res) );
        return pointer;
    }
}


synch_queue* synch_queue::get_instance() {
    std::call_once(inited,[]{
        instance = new synch_queue();
    });
    return instance;
}

synch_queue::synch_queue() {

    this->is_running = true;
}




