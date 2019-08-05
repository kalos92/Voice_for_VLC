//
// Created by kalos on 05/08/19.
//

#include "StateMachine.h"

StateMachine::State StateMachine::changeState(StateMachine::State state, StateMachine::Command command){

    if(checkStateChange(state, command))
        return fromCommandToState(state, command);
    else
        return StateMachine::EXCEPTION;
}

bool StateMachine::checkStateChange (StateMachine::State state, StateMachine::Command command) {

    if (state == STATE_PLAY){
        return command == TIME || command == PERCENTAGE || command == NEXT || command == PREVIOUS || command == STOP
               || command == PLAY || command == DESTROY|| command == PAUSE;
    }
    else if (state == STATE_STOP){
        return   command == PLAY || command == DESTROY || command == RESTART;
    }
    else if (state == STATE_PAUSE){
        return command == TIME || command == PERCENTAGE || command == NEXT || command == PREVIOUS ||
               command == STOP || command == PLAY || command == DESTROY || command == RESUME;
    }
    else if (state == STATE_DESTROY){
        return false;
    }

}

StateMachine::State StateMachine::fromCommandToState(StateMachine::State state, StateMachine::Command command){

    if(command == StateMachine::TIME || command == StateMachine::PERCENTAGE || command == StateMachine::NEXT ||
    command == StateMachine::PREVIOUS)
        return state;

    if(command == StateMachine::PLAY)
        return StateMachine::STATE_PLAY;

    if(command == StateMachine::STOP)
        return StateMachine::STATE_STOP;

    if(command == StateMachine::DESTROY)
        return StateMachine::STATE_DESTROY;

    if(command == StateMachine::PAUSE)
        return StateMachine::STATE_PAUSE;

    if(command == StateMachine::RESUME)
        return StateMachine::STATE_PLAY;

    if(command == StateMachine::RESTART)
        return StateMachine::STATE_PLAY;
}

std::string StateMachine::fromStateToString(StateMachine::State state){

    switch (state){
        case StateMachine::STATE_PLAY:
            return "PLAY";
        case StateMachine::STATE_PAUSE:
            return "PAUSE";
        case StateMachine::STATE_STOP:
            return "STOP";
        case StateMachine::STATE_DESTROY:
            return "DESTROY";
        case StateMachine::EXCEPTION:
            return "EXCEPTION";
    }

}
std::string StateMachine::fromCommandToString(StateMachine::Command command){

    switch (command){

        case StateMachine::PLAY: return "PLAY";
        case StateMachine::PAUSE: return "PAUSE";
        case StateMachine::STOP: return "STOP";
        case StateMachine::NEXT: return "NEXT";
        case StateMachine::PREVIOUS: return "PREVIOUS";
        case StateMachine::DESTROY: return "DESTROY";
        case StateMachine::TIME: return "TIME";
        case StateMachine::PERCENTAGE: return "PERCENTAGE";
        case StateMachine::RESUME: return "RESUME";
        case StateMachine::RESTART: return "RESTART";
    }

}

StateMachine::Command StateMachine::fromStringToCommand(const std::string& command) {

    if (command == "PLAY")
        return StateMachine::PLAY;

    if (command == "PAUSE")
        return StateMachine::PAUSE;

    if (command == "STOP")
        return StateMachine::STOP;

    if (command == "NEXT")
        return StateMachine::NEXT;

    if (command == "PREVIOUS")
        return StateMachine::PREVIOUS;

    if (command == "DESTROY")
        return StateMachine::DESTROY;

    if (command == "TIME")
        return StateMachine::TIME;

    if (command == "PERCENTAGE")
        return StateMachine::PERCENTAGE;

    if (command == "RESUME")
        return StateMachine::RESUME;

    if (command == "RESTART")
        return StateMachine::RESTART;
}
