//
// Created by kalos on 25/04/19.
//

#include <iostream>
#include "message.h"


const Command &Message::getCommand() const {
    return command;
}

std::string Message::getPath() const {
    return path;
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

double Message::getTime() const {
    return time;
}

Message &Message::operator=(const Message &other) {

        if (this != &other)
        {
            command = other.command;
            season = other.season;
            title = other.title;
            path = other.path;
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

const Status &Response::getStatus() const {
    return status;
}

std::string Response::getResponse() const {
    return response;
}
