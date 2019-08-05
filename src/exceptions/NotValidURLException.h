//
// Created by kalos on 09/05/19.
//

#ifndef VOICE_FOR_VLC_NOTVALIDURLEXCEPTION_H
#define VOICE_FOR_VLC_NOTVALIDURLEXCEPTION_H


#include "NotFoundException.h"

class NotValidURLException : public std::exception{
public:
    const char * what () const throw (){
        return "Fake URL";
    }
};


#endif //VOICE_FOR_VLC_NOTVALIDURL_H
