//
// Created by kalos on 27/04/19.
//

#ifndef VOICE_FOR_VLC_VLC_NOTFOUNDEXCEPTION_H
#define VOICE_FOR_VLC_VLC_NOTFOUNDEXCEPTION_H


#include <exception>
class NotFoundException: public std::exception {
public:

    const char * what () const throw (){
        return "Requested media cannot be found";
    }


};

#endif //GOOGLE_ASSISTANT_FOR_VLC_NOTFOUNDEXCEPTION_H
