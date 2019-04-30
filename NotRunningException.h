//
// Created by kalos on 25/04/19.
//

#ifndef GOOGLE_ASSISTANT_FOR_VLC_NOTRUNNINGEXCEPTION_H
#define GOOGLE_ASSISTANT_FOR_VLC_NOTRUNNINGEXCEPTION_H


#include <exception>
class NotRunningException: public std::exception {

    const char * what () const noexcept override {
        return "Synch Queue was stopped";
    }


};


#endif //GOOGLE_ASSISTANT_FOR_VLC_NOTRUNNINGEXCEPTION_H
