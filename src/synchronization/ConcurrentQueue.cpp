//
// Created by kalos on 25/04/19.
//

#include "ConcurrentQueue.h"


std::once_flag ConcurrencyQueue::inited;
ConcurrencyQueue *ConcurrencyQueue::instance;

void ConcurrencyQueue::writeMessage(const CommandMessage& mex) {

    if(!is_running)
        throw NotRunningException();

    std::lock_guard<std::mutex> lock(this->mutex_mex);

    this->messages.push_back(mex);

    this->cv_mex.notify_one();
}

void ConcurrencyQueue::writeResponse(const CommandResponse& res) {

    if(!is_running)
        throw NotRunningException();

    std::lock_guard<std::mutex> lock(this->mutex_res);

    this->responses.push_back(res);

    this->cv_res.notify_all();
}

std::unique_ptr<CommandMessage> ConcurrencyQueue::readMessage() {

    if(!is_running)
        throw NotRunningException();

    CommandMessage message;

    while(true){
        std::unique_lock<std::mutex> lock(this->mutex_mex);

        while(messages.empty())
            this->cv_mex.wait(lock);

        if(messages.empty())
            continue;

        std::cout << messages.front().getCommand() << std::endl;

        this->messages.pop_front();

        std::unique_ptr<CommandMessage> pointer( new CommandMessage(message) );

        return pointer;
    }
}

std::unique_ptr<Response> ConcurrencyQueue::readResponse() {

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


ConcurrencyQueue* ConcurrencyQueue::getInstance() {
    std::call_once(inited,[]{
        instance = new ConcurrencyQueue();
    });
    return instance;
}

ConcurrencyQueue::ConcurrencyQueue() {

    this->is_running = true;
}




