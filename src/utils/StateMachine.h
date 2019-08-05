#include <utility>
#include <algorithm>
#include "TextOperation.h"

//
// Created by kalos on 25/04/19.
//

#ifndef GOOGLE_ASSISTANT_FOR_VLC_COMMAND_H
#define GOOGLE_ASSISTANT_FOR_VLC_COMMAND_H

class StateMachine{

private:
    static bool changeStatus(State state, Command command) {

       if (state == S_PLAY){
           return command == TIME || command == PERCENTAGE || command == NEXT || command == PREVIOUS || command == STOP
           || command == PLAY || command == DESTROY|| command == PAUSE;
       }
       else if (state == S_STOP){
           return   command == PLAY || command == DESTROY || command == RESTART;
       }
       else if (state == S_PAUSE){
           return command == TIME || command == PERCENTAGE || command == NEXT || command == PREVIOUS ||
                   command == STOP || command == PLAY || command == DESTROY || command == RESUME;
       }
       else if (state == S_DESTROY){
           return false;
       }

    }

    static State fromCommandToState(Status state, Command command){

        if(command == TIME || command == PERCENTAGE || command == NEXT || command == PREVIOUS )
            return s;

        if(command == PLAY)
            return S_PLAY;
        if(command == STOP)
            return S_STOP;
        if(command == DESTROY)
            return S_DESTROY;
        if(command == PAUSE)
            return S_PAUSE;
        if(command == RESUME)
            return S_PLAY;
        if(command == RESTART)
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
            case TIME: return "TIME";
            case PERCENTAGE: return "PERCENTAGE";
            case RESUME: return "RESUME";
            case RESTART: return "RESTART";
        }

    }

    static Command string_to_command(const std::string& command) {

        if (command == "PLAY")
            return PLAY;

        if (command == "PAUSE")
            return PAUSE;

        if (command == "STOP")
            return STOP;

        if (command == "NEXT")
            return NEXT;

        if (command == "PREVIOUS")
            return PREVIOUS;

        if (command == "DESTROY")
            return DESTROY;

        if (command == "TIME")
            return TIME;

        if (command == "PERCENTAGE")
            return PERCENTAGE;

        if (command == "RESUME")
            return RESUME;

        if (command == "RESTART")
            return RESTART;
    }

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

    enum State {
        S_PLAY,
        S_PAUSE,
        S_STOP,
        S_DESTROY,
        EXCEPTION
    };

};
#endif //GOOGLE_ASSISTANT_FOR_VLC_COMMAND_H