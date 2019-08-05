#include <utility>

//
// Created by kalos on 25/04/19.
//
#ifndef GOOGLE_ASSISTANT_FOR_VLC_MESSAGE_H
#define GOOGLE_ASSISTANT_FOR_VLC_MESSAGE_H


#include <arpa/nameser.h>
#include <string>
#include "command.h"

class Message {

    public:
        Message()= default;

        Message(Command command, std::string title, int season, int episode, std::pair<std::string, int64_t> time) :
            command(command), title(std::move(title)), season(season), episode(episode), time(std::move(time)){};

        ~Message()= default;

        Message& operator=(const Message& other);

        const Command &getCommand() const; //& return a const reference

        const std::string &getTitle() const;

        int getSeason() const;

        int getEpisode() const;

        std::pair<std::string, int64_t> getTime() const;


    private:
        Command command;
        std::string title;
        int season;
        int episode;
        std::pair<std::string, int64_t> time;  //<[hours minutes seconds none, time]

};

class Response {

public:
    Response()= default;

    Response(Result status, std::string response):
             status(status), response(std::move(response)){};
    ~Response()= default;

    Response& operator=(const Response& other);

    const Result &getResult() const; //& return a const reference

    std::string getResponse() const;



private:
    Result status;
    std::string response;

};


#endif //GOOGLE_ASSISTANT_FOR_VLC_MESSAGE_H