//
// Created by kalos on 09/05/19.
//

#ifndef VOICE_FOR_VLC_TEXTOPERATION_H
#define VOICE_FOR_VLC_TEXTOPERATION_H



#include <string.h>
#include <boost/algorithm/string.hpp>

class TextOperation {
public:
    static std::string convert_space(std::basic_string<char> &basicString);

    static void vfv_toupper(std::string *string);
};


#endif //VOICE_FOR_VLC_TEXTOPERATION_H
