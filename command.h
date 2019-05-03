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
    FF,
    REW

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
           return c == FF || c == REW || c == NEXT || c == PREVIOUS || c == STOP || c == PLAY || c == DESTROY
                    || c == PAUSE;
       }
       else if (s == S_STOP){
           return   c == PLAY || c == DESTROY;
       }
       else if (s == S_PAUSE){
           return c == FF || c == REW || c == NEXT || c == PREVIOUS || c == STOP || c == PLAY || c == DESTROY;

       }
       else if (s == S_DESTROY){
           return false;
       }

    }

    static Status from_commad_to_status(Status s, Command c){

        if(c == FF || c == REW || c == NEXT || c == PREVIOUS )
            return s;

        if(c == PLAY)
            return S_PLAY;
        if(c == STOP)
            return S_STOP;
        if(c == DESTROY)
            return S_DESTROY;
        if(c == PAUSE)
            return S_PAUSE;
    }

public:
    static Status change_status(Status s, Command c){

       if(check_if_permitted(s,c))
           return from_commad_to_status(s,c);
       else
           return EXCEPTION;
    }
};



#endif //GOOGLE_ASSISTANT_FOR_VLC_COMMAND_H
