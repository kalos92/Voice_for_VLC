//
// Created by kalos on 27/04/19.
//

#ifndef GOOGLE_ASSISTANT_FOR_VLC_NOTFOUNDEXCEPTION_H
#define GOOGLE_ASSISTANT_FOR_VLC_NOTFOUNDEXCEPTION_H


#include <exception>
class NotFoundException: public std::exception {

    const char * what () const noexcept override {
        return "Requested media cannot be found";
    }


};

#endif //GOOGLE_ASSISTANT_FOR_VLC_NOTFOUNDEXCEPTION_H
