//
// Created by kalos on 25/04/19.
//

#include "Message.h"

const StateMachine::Command &CommandMessage::getCommand() const {
    return command;
}

const std::string &CommandMessage::getTitle() const {
    return title;
}

int CommandMessage::getSeason() const {
    return season;
}

int CommandMessage::getEpisode() const {
    return episode;
}

std::pair<std::string, int64_t> CommandMessage::getTime() const {
    return time;
}

CommandMessage &CommandMessage::operator=(const CommandMessage &other) {

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

CommandResponse &CommandResponse::operator=(const CommandResponse &other) {
    if (this != &other)
    {
        result = other.result;
        response = other.response;

    }
    return *this;
}

const StateMachine::Result &CommandResponse::getResult() const {
    return result;
}

std::string CommandResponse::getResponse() const {
    return response;
}
