//
// Created by kalos on 25/04/19.
//

#include <iostream>
#include "message.h"


const Command &Message::getCommand() const {
    return command;
}

const std::string &Message::getTitle() const {
    return title;
}

int Message::getSeason() const {
    return season;
}

int Message::getEpisode() const {
    return episode;
}

std::pair<std::string, int64_t> Message::getTime() const {
    return time;
}

Message &Message::operator=(const Message &other) {

        if (this != &other)
        {
            command = other.command;
            season = other.season;
            title = other.title;
            time = other.time;
            episode = other.episode;
        }
        return *this;
}

Response &Response::operator=(const Response &other) {
    if (this != &other)
    {
        status = other.status;
        response = other.response;

    }
    return *this;
}

const Result &Response::getResult() const {
    return status;
}

std::string Response::getResponse() const {
    return response;
}