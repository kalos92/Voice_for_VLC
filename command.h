//
// Created by kalos on 25/04/19.
//

#ifndef GOOGLE_ASSISTANT_FOR_VLC_COMMAND_H
#define GOOGLE_ASSISTANT_FOR_VLC_COMMAND_H

static std::string path_series = std::string("/home/") + getenv("USER");

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

enum Status {

    ERROR,
    SUCCESS,
};



#endif //GOOGLE_ASSISTANT_FOR_VLC_COMMAND_H
