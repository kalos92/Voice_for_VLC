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

        Message(Command command, std::string path, std::string title, int season, int episode, double time) :
            command(command), path(std::move(path)), title(std::move(title)), season(season), episode(episode), time(time){};

        ~Message()= default;

        Message& operator=(const Message& other);

        const Command &getCommand() const; //& return a const reference

        std::string getPath() const;

        const std::string &getTitle() const;

        int getSeason() const;

        int getEpisode() const;

        double getTime() const;


    private:
        Command command;
        std::string path;
        std::string title;
        int season;
        int episode;
        double time;

};

class Response {

public:
    Response()= default;

    Response(Status status, std::string response):
             status(status), response(std::move(response)){};
    ~Response()= default;

    Response& operator=(const Response& other);

    const Status &getStatus() const; //& return a const reference

    std::string getResponse() const;



private:
    Status status;
    std::string response;

};


#endif //GOOGLE_ASSISTANT_FOR_VLC_MESSAGE_H
