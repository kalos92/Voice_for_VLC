#include <utility>

//
// Created by kalos on 25/04/19.
//

#ifndef GOOGLE_ASSISTANT_FOR_VLC_COMMAND_H
#define GOOGLE_ASSISTANT_FOR_VLC_COMMAND_H

enum Command {
    PLAY,
    PAUSE,
    STOP,
    NEXT,
    PREVIOUS,
    DESTROY,
    TIME,
    PERCENTAGE,
    RESUME,
    RESTART

};

enum Result {

    ERROR,
    SUCCESS,
};

enum Status {
    S_PLAY,
    S_PAUSE,
    S_STOP,
    S_DESTROY,
    EXCEPTION
};

class Costants{

    public:
        Costants(std::string addr, std::string path):
            address(std::move(addr)), path(std::move(path)){};
        ~Costants()= default;
        const std::string &getPath() const {
            return path;
        }

        const std::string &getAddress() const {
            return address;
        }

    private:
        std::string path;
        std::string address;

};

class State_Machine{

private:
    static bool check_if_permitted(Status s, Command c) {

       if (s == S_PLAY){
           return c == TIME || c == PERCENTAGE || c == NEXT || c == PREVIOUS || c == STOP || c == PLAY || c == DESTROY
                    || c == PAUSE;
       }
       else if (s == S_STOP){
           return   c == PLAY || c == DESTROY || c == RESTART;
       }
       else if (s == S_PAUSE){
           return c == TIME || c == PERCENTAGE || c == NEXT || c == PREVIOUS || c == STOP || c == PLAY || c == DESTROY || c == RESUME;

       }
       else if (s == S_DESTROY){
           return false;
       }

    }

    static Status from_commad_to_status(Status s, Command c){

        if(c == TIME || c == PERCENTAGE || c == NEXT || c == PREVIOUS )
            return s;

        if(c == PLAY)
            return S_PLAY;
        if(c == STOP)
            return S_STOP;
        if(c == DESTROY)
            return S_DESTROY;
        if(c == PAUSE)
            return S_PAUSE;
        if(c == RESUME)
            return S_PLAY;
        if(c == RESTART)
            return S_PLAY;
    }

public:
    static Status change_status(Status s, Command c){

       if(check_if_permitted(s,c))
           return from_commad_to_status(s,c);
       else
           return EXCEPTION;
    }

    static std::string status_to_string(Status s){

        switch (s){
            case S_PLAY:
                return "PLAY";
            case S_PAUSE:
                return "PAUSE";
            case S_STOP:
                return "STOP";
            case S_DESTROY:
                return "DESTROY";
            case EXCEPTION:
                return "EXCEPTION";
        }

    }
    static std::string command_to_string(Command c){

        switch (c){

            case PLAY: return "PLAY";
            case PAUSE: return "PAUSE";
            case STOP: return "STOP";
            case NEXT: return "NEXT";
            case PREVIOUS: return "PREVIOUS";
            case DESTROY: return "DESTROY";
            case TIME: return "FAST FORWARD";
            case PERCENTAGE: return "REWIND";
            case RESUME: return "RESUME";
            case RESTART: return "RESTART";
        }

    }
};



#endif //GOOGLE_ASSISTANT_FOR_VLC_COMMAND_H
