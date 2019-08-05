#include <utility>
#include <algorithm>
#include "TextOperation.h"

//
// Created by kalos on 25/04/19.
//

#ifndef VOICE_FOR_VLC_STATEMACHINE_H
#define VOICE_FOR_VLC_STATEMACHINE_H

class StateMachine{

public:

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
        STATE_PLAY,
        STATE_PAUSE,
        STATE_STOP,
        STATE_DESTROY,
        EXCEPTION
    };

private:

    static bool checkStateChange(State, Command);
    static State fromCommandToState(State, Command);

public:

    static State changeState(State, Command);
    static std::string fromStateToString(State);
    static std::string fromCommandToString(Command);
    static Command fromStringToCommand(const std::string&);



};
#endif //GOOGLE_ASSISTANT_FOR_VLC_COMMAND_H