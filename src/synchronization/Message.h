

//
// Created by kalos on 25/04/19.
//
#ifndef VOICE_FOR_VLC_MESSAGE_H
#define VOICE_FOR_VLC_MESSAGE_H

#include <string>
#include "../utils/StateMachine.h"

class Message{

public:
    Message() = default;
    ~Message()= default;
};

class CommandMessage : public Message {

    public:

        CommandMessage(StateMachine::Command command, std::string title, int season, int episode,
                std::pair<std::string, int64_t> time) :
            command(command), title(std::move(title)), season(season), episode(episode), time(std::move(time)){};

        CommandMessage& operator=(const CommandMessage& other);
        const StateMachine::Command &getCommand() const; //& return a const reference
        const std::string &getTitle() const;
        int getSeason() const;
        int getEpisode() const;
        std::pair<std::string, int64_t> getTime() const;

    private:
        StateMachine::Command command;
        std::string title;
        int season;
        int episode;
        std::pair<std::string, int64_t> time;  //<[hours minutes seconds none, time]>

};

class CommandResponse : public Message {

public:
    CommandResponse()= default;

    CommandResponse(StateMachine::Result result, std::string response):
             result(result), response(std::move(response)){};
    ~CommandResponse()= default;

    CommandResponse& operator=(const CommandResponse& other);

    const StateMachine::Result &getResult() const; //& return a const reference

    std::string getResponse() const;

private:
    StateMachine::Result result;
    std::string response;

};


#endif //GOOGLE_ASSISTANT_FOR_VLC_MESSAGE_H
