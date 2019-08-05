//
// Created by kalos on 25/04/19.
//

#ifndef VOICE_FOR_VLC_NOTRUNNINGEXCEPTION_H
#define VOICE_FOR_VLC_NOTRUNNINGEXCEPTION_H

#include <exception>
class NotRunningException: public std::exception {
public:
    const char * what () const throw (){
        return "Synch Queue was stopped";
    }


};


#endif //GOOGLE_ASSISTANT_FOR_VLC_NOTRUNNINGEXCEPTION_H
