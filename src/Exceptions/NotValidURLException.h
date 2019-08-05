//
// Created by kalos on 09/05/19.
//

#ifndef VOICE_FOR_VLC_NOTVALIDURL_H
#define VOICE_FOR_VLC_NOTVALIDURL_H


#include "NotFoundException.h"

class NotValidURL : public std::exception{
public:
    const char * what () const throw (){
        return "Fake URL";
    }
};


#endif //VOICE_FOR_VLC_NOTVALIDURL_H
